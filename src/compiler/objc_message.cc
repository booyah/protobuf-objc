// Protocol Buffers for Objective C
//
// Copyright 2010 Booyah Inc.
// Copyright 2008 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "objc_message.h"

#include <algorithm>
#include <google/protobuf/stubs/hash.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.pb.h>

#include "objc_enum.h"
#include "objc_extension.h"
#include "objc_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

  using internal::WireFormat;
  using internal::WireFormatLite;

  namespace {
    struct FieldOrderingByNumber {
      inline bool operator()(const FieldDescriptor* a,
        const FieldDescriptor* b) const {
          return a->number() < b->number();
      }
    };

    struct FieldOrderingByType {
      inline bool operator()(const FieldDescriptor* a, const FieldDescriptor* b) const {
        // place collections at the end
        if (a->is_repeated() != b->is_repeated()) {
          return b->is_repeated();
        }

        // we want BOOL fields to be placed first.  That way they will be packed
        // in with the 'BOOL hasFoo' fields.
        if (a->type() == FieldDescriptor::TYPE_BOOL &&
            b->type() != FieldDescriptor::TYPE_BOOL) {
          return true;
        }

        if (a->type() != FieldDescriptor::TYPE_BOOL &&
            b->type() == FieldDescriptor::TYPE_BOOL) {
          return false;
        }

        return a->type() < b->type();
      }
    };

    struct ExtensionRangeOrdering {
      bool operator()(const Descriptor::ExtensionRange* a,
        const Descriptor::ExtensionRange* b) const {
          return a->start < b->start;
      }
    };

    // Sort the fields of the given Descriptor by number into a new[]'d array
    // and return it.
    const FieldDescriptor** SortFieldsByNumber(const Descriptor* descriptor) {
      const FieldDescriptor** fields = new const FieldDescriptor*[descriptor->field_count()];
      for (int i = 0; i < descriptor->field_count(); i++) {
        fields[i] = descriptor->field(i);
      }
      sort(fields, fields + descriptor->field_count(), FieldOrderingByNumber());
      return fields;
    }

    // Sort the fields of the given Descriptor by type into a new[]'d array
    // and return it.
    const FieldDescriptor** SortFieldsByType(const Descriptor* descriptor) {
      const FieldDescriptor** fields = new const FieldDescriptor*[descriptor->field_count()];
      for (int i = 0; i < descriptor->field_count(); i++) {
        fields[i] = descriptor->field(i);
      }
      sort(fields, fields + descriptor->field_count(), FieldOrderingByType());
      return fields;
    }

    // Get an identifier that uniquely identifies this type within the file.
    // This is used to declare static variables related to this type at the
    // outermost file scope.
    string UniqueFileScopeIdentifier(const Descriptor* descriptor) {
      return "static_" + StringReplace(descriptor->full_name(), ".", "_", true);
    }

    // Returns true if the message type has any required fields.  If it doesn't,
    // we can optimize out calls to its isInitialized() method.
    //
    // already_seen is used to avoid checking the same type multiple times
    // (and also to protect against recursion).
    static bool HasRequiredFields(
      const Descriptor* type,
      hash_set<const Descriptor*>* already_seen) {
        if (already_seen->count(type) > 0) {
          // The type is already in cache.  This means that either:
          // a. The type has no required fields.
          // b. We are in the midst of checking if the type has required fields,
          //    somewhere up the stack.  In this case, we know that if the type
          //    has any required fields, they'll be found when we return to it,
          //    and the whole call to HasRequiredFields() will return true.
          //    Therefore, we don't have to check if this type has required fields
          //    here.
          return false;
        }
        already_seen->insert(type);

        // If the type has extensions, an extension with message type could contain
        // required fields, so we have to be conservative and assume such an
        // extension exists.
        if (type->extension_range_count() > 0) {
          return true;
        }

        for (int i = 0; i < type->field_count(); i++) {
          const FieldDescriptor* field = type->field(i);
          if (field->is_required()) {
            return true;
          }
          if (field->cpp_type() == FieldDescriptor::CPPTYPE_MESSAGE) {
            if (HasRequiredFields(field->message_type(), already_seen)) {
              return true;
            }
          }
        }

        return false;
    }

    static bool HasRequiredFields(const Descriptor* type) {
      hash_set<const Descriptor*> already_seen;
      return HasRequiredFields(type, &already_seen);
    }
  }  // namespace


  MessageGenerator::MessageGenerator(const Descriptor* descriptor)
    : descriptor_(descriptor),
    field_generators_(descriptor) {
  }


  MessageGenerator::~MessageGenerator() {
  }


  void MessageGenerator::GenerateStaticVariablesHeader(io::Printer* printer) {
    map<string, string> vars;
    vars["identifier"] = UniqueFileScopeIdentifier(descriptor_);
    vars["index"] = SimpleItoa(descriptor_->index());
    vars["classname"] = ClassName(descriptor_);
    if (descriptor_->containing_type() != NULL) {
      vars["parent"] = UniqueFileScopeIdentifier(descriptor_->containing_type());
    }

    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i)).GenerateStaticVariablesHeader(printer);
    }
  }


  void MessageGenerator::GenerateStaticVariablesInitialization(io::Printer* printer) {
    map<string, string> vars;
    vars["identifier"] = UniqueFileScopeIdentifier(descriptor_);
    vars["index"] = SimpleItoa(descriptor_->index());
    vars["classname"] = ClassName(descriptor_);
    if (descriptor_->containing_type() != NULL) {
      vars["parent"] = UniqueFileScopeIdentifier(descriptor_->containing_type());
    }

    for (int i = 0; i < descriptor_->extension_count(); i++) {
      ExtensionGenerator(ClassName(descriptor_), descriptor_->extension(i)).GenerateInitializationSource(printer);
    }
    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i)).GenerateStaticVariablesInitialization(printer);
    }
  }


  void MessageGenerator::GenerateStaticVariablesSource(io::Printer* printer) {
    map<string, string> vars;
    vars["identifier"] = UniqueFileScopeIdentifier(descriptor_);
    vars["index"] = SimpleItoa(descriptor_->index());
    vars["classname"] = ClassName(descriptor_);
    if (descriptor_->containing_type() != NULL) {
      vars["parent"] = UniqueFileScopeIdentifier(descriptor_->containing_type());
    }

    for (int i = 0; i < descriptor_->extension_count(); i++) {
      ExtensionGenerator(ClassName(descriptor_), descriptor_->extension(i))
        .GenerateFieldsSource(printer);
    }

    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i)).GenerateStaticVariablesSource(printer);
    }
  }


  void MessageGenerator::DetermineDependencies(set<string>* dependencies) {
    dependencies->insert("@class " + ClassName(descriptor_));
    dependencies->insert("@class " + ClassName(descriptor_) + "_Builder");

    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i)).DetermineDependencies(dependencies);
    }
  }

  void MessageGenerator::GenerateEnumHeader(io::Printer* printer) {
    for (int i = 0; i < descriptor_->enum_type_count(); i++) {
      EnumGenerator(descriptor_->enum_type(i)).GenerateHeader(printer);
    }

    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i)).GenerateEnumHeader(printer);
    }
  }

  void MessageGenerator::GenerateExtensionRegistrationSource(io::Printer* printer) {
    for (int i = 0; i < descriptor_->extension_count(); i++) {
      ExtensionGenerator(ClassName(descriptor_), descriptor_->extension(i))
        .GenerateRegistrationSource(printer);
    }

    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i))
        .GenerateExtensionRegistrationSource(printer);
    }
  }

  void MessageGenerator::GenerateMessageHeader(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(SortFieldsByType(descriptor_));

    if (descriptor_->extension_range_count() > 0) {
      printer->Print(
        "@interface $classname$ : PBExtendableMessage {\n"
        "@private\n",
        "classname", ClassName(descriptor_));
    } else {
      printer->Print(
        "@interface $classname$ : PBGeneratedMessage {\n"
        "@private\n",
        "classname", ClassName(descriptor_));
    }

    printer->Indent();
    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(sorted_fields[i]).GenerateHasFieldHeader(printer);
    }
    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(sorted_fields[i]).GenerateFieldHeader(printer);
    }
    printer->Outdent();

    printer->Print("}\n");

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateHasPropertyHeader(printer);
    }
    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GeneratePropertyHeader(printer);
    }
    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateMembersHeader(printer);
    }

    printer->Print(
      "\n"
      "+ ($classname$*) defaultInstance;\n"
      "- ($classname$*) defaultInstance;\n",
      "classname", ClassName(descriptor_));
    printer->Print(
      "\n",
      "fileclass", FileClassName(descriptor_->file()),
      "identifier", UniqueFileScopeIdentifier(descriptor_));

    for (int i = 0; i < descriptor_->extension_count(); i++) {
      ExtensionGenerator(ClassName(descriptor_), descriptor_->extension(i)).GenerateMembersHeader(printer);
    }

    GenerateIsInitializedHeader(printer);
    GenerateMessageSerializationMethodsHeader(printer);

    printer->Print(
      "- ($classname$_Builder*) builder;\n"
      "+ ($classname$_Builder*) builder;\n"
      "+ ($classname$_Builder*) builderWithPrototype:($classname$*) prototype;\n"
      "- ($classname$_Builder*) toBuilder;\n",
      "classname", ClassName(descriptor_));

    GenerateParseFromMethodsHeader(printer);

    printer->Print("@end\n\n");

    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i)).GenerateMessageHeader(printer);
    }

    GenerateBuilderHeader(printer);
  }


  void MessageGenerator::GenerateSource(io::Printer* printer) {
    printer->Print(
      "@interface $classname$ ()\n",
      "classname", ClassName(descriptor_));
    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateExtensionSource(printer);
    }
    printer->Print("@end\n\n");

    printer->Print("@implementation $classname$\n\n",
      "classname", ClassName(descriptor_));

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateSynthesizeSource(printer);
    }

    printer->Print("- (void) dealloc {\n");
    printer->Indent();
    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateDeallocSource(printer);
    }
    printer->Outdent();
    printer->Print(
      "  [super dealloc];\n"
      "}\n");

    printer->Print(
      "- (id) init {\n"
      "  if ((self = [super init])) {\n");
    printer->Indent();
    printer->Indent();
    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateInitializationSource(printer);
    }
    printer->Outdent();
    printer->Outdent();
    printer->Print(
      "  }\n"
      "  return self;\n"
      "}\n");

    for (int i = 0; i < descriptor_->extension_count(); i++) {
      ExtensionGenerator(ClassName(descriptor_), descriptor_->extension(i)).GenerateMembersSource(printer);
    }

    printer->Print(
      "static $classname$* default$classname$Instance = nil;\n"
      "+ (void) initialize {\n"
      "  if (self == [$classname$ class]) {\n"
      "    default$classname$Instance = [[$classname$ alloc] init];\n",
      "classname", ClassName(descriptor_));

    printer->Print(
      "  }\n"
      "}\n"
      "+ ($classname$*) defaultInstance {\n"
      "  return default$classname$Instance;\n"
      "}\n"
      "- ($classname$*) defaultInstance {\n"
      "  return default$classname$Instance;\n"
      "}\n",
      "classname", ClassName(descriptor_));

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateMembersSource(printer);
    }

    GenerateIsInitializedSource(printer);
    GenerateMessageSerializationMethodsSource(printer);

    GenerateParseFromMethodsSource(printer);

    printer->Print(
      "+ ($classname$_Builder*) builder {\n"
      "  return [[[$classname$_Builder alloc] init] autorelease];\n"
      "}\n"
      "+ ($classname$_Builder*) builderWithPrototype:($classname$*) prototype {\n"
      "  return [[$classname$ builder] mergeFrom:prototype];\n"
      "}\n"
      "- ($classname$_Builder*) builder {\n"
      "  return [$classname$ builder];\n"
      "}\n"
      "- ($classname$_Builder*) toBuilder {\n"
      "  return [$classname$ builderWithPrototype:self];\n"
      "}\n",
      "classname", ClassName(descriptor_));

    GenerateMessageDescriptionSource(printer);

    GenerateMessageIsEqualSource(printer);

    GenerateMessageHashSource(printer);

    printer->Print("@end\n\n");

    for (int i = 0; i < descriptor_->enum_type_count(); i++) {
      EnumGenerator(descriptor_->enum_type(i)).GenerateSource(printer);
    }

    for (int i = 0; i < descriptor_->nested_type_count(); i++) {
      MessageGenerator(descriptor_->nested_type(i)).GenerateSource(printer);
    }

    GenerateBuilderSource(printer);
  }


  void MessageGenerator::GenerateMessageSerializationMethodsHeader(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(SortFieldsByNumber(descriptor_));

    vector<const Descriptor::ExtensionRange*> sorted_extensions;
    for (int i = 0; i < descriptor_->extension_range_count(); ++i) {
      sorted_extensions.push_back(descriptor_->extension_range(i));
    }
    sort(sorted_extensions.begin(), sorted_extensions.end(),
      ExtensionRangeOrdering());

    printer->Print(
      "- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;\n");
  }

  void MessageGenerator::GenerateParseFromMethodsHeader(io::Printer* printer) {
    printer->Print(
      "\n"
      "+ ($classname$*) parseFromData:(NSData*) data;\n"
      "+ ($classname$*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;\n"
      "+ ($classname$*) parseFromInputStream:(NSInputStream*) input;\n"
      "+ ($classname$*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;\n"
      "+ ($classname$*) parseFromCodedInputStream:(PBCodedInputStream*) input;\n"
      "+ ($classname$*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;\n",
      "classname", ClassName(descriptor_));
  }


  void MessageGenerator::GenerateSerializeOneFieldHeader(
    io::Printer* printer, const FieldDescriptor* field) {
      field_generators_.get(field).GenerateSerializationCodeHeader(printer);
  }


  void MessageGenerator::GenerateSerializeOneExtensionRangeHeader(
    io::Printer* printer, const Descriptor::ExtensionRange* range) {
  }


  void MessageGenerator::GenerateBuilderHeader(io::Printer* printer) {
    if (descriptor_->extension_range_count() > 0) {
      printer->Print(
        "@interface $classname$_Builder : PBExtendableMessage_Builder {\n",
        "classname", ClassName(descriptor_));
    } else {
      printer->Print(
        "@interface $classname$_Builder : PBGeneratedMessage_Builder {\n",
        "classname", ClassName(descriptor_));
    }

    printer->Print(
      "@private\n"
      "  $classname$* result;\n"
      "}\n",
      "classname", ClassName(descriptor_));

    GenerateCommonBuilderMethodsHeader(printer);
    GenerateBuilderParsingMethodsHeader(printer);

    for (int i = 0; i < descriptor_->field_count(); i++) {
      printer->Print("\n");
      field_generators_.get(descriptor_->field(i)).GenerateBuilderMembersHeader(printer);
    }

    printer->Print("@end\n\n");
  }


  void MessageGenerator::GenerateCommonBuilderMethodsHeader(io::Printer* printer) {
    printer->Print(
      "\n"
      "- ($classname$*) defaultInstance;\n"
      "\n"
      "- ($classname$_Builder*) clear;\n"
      "- ($classname$_Builder*) clone;\n",
      "classname", ClassName(descriptor_));

    printer->Print(
      "\n"
      "- ($classname$*) build;\n"
      "- ($classname$*) buildPartial;\n",
      "classname", ClassName(descriptor_));
    printer->Indent();

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateBuildingCodeHeader(printer);
    }

    printer->Outdent();

    printer->Print(
      "\n"
      "- ($classname$_Builder*) mergeFrom:($classname$*) other;\n",
      "classname", ClassName(descriptor_));
    printer->Indent();

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateMergingCodeHeader(printer);
    }

    printer->Outdent();
  }


  void MessageGenerator::GenerateBuilderParsingMethodsHeader(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(SortFieldsByNumber(descriptor_));

    printer->Print(
      "- ($classname$_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;\n"
      "- ($classname$_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;\n",
      "classname", ClassName(descriptor_));
  }


  void MessageGenerator::GenerateIsInitializedHeader(io::Printer* printer) {
    printer->Print(
      "- (BOOL) isInitialized;\n");
  }


  void MessageGenerator::GenerateMessageSerializationMethodsSource(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(SortFieldsByNumber(descriptor_));

    vector<const Descriptor::ExtensionRange*> sorted_extensions;
    for (int i = 0; i < descriptor_->extension_range_count(); ++i) {
      sorted_extensions.push_back(descriptor_->extension_range(i));
    }
    sort(sorted_extensions.begin(), sorted_extensions.end(),
      ExtensionRangeOrdering());

    printer->Print(
      "- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output {\n");
    printer->Indent();

    // Merge the fields and the extension ranges, both sorted by field number.
    for (int i = 0, j = 0;
      i < descriptor_->field_count() || j < sorted_extensions.size(); ) {
        if (i == descriptor_->field_count()) {
          GenerateSerializeOneExtensionRangeSource(printer, sorted_extensions[j++]);
        } else if (j == sorted_extensions.size()) {
          GenerateSerializeOneFieldSource(printer, sorted_fields[i++]);
        } else if (sorted_fields[i]->number() < sorted_extensions[j]->start) {
          GenerateSerializeOneFieldSource(printer, sorted_fields[i++]);
        } else {
          GenerateSerializeOneExtensionRangeSource(printer, sorted_extensions[j++]);
        }
    }

    if (descriptor_->options().message_set_wire_format()) {
      printer->Print(
        "[self.unknownFields writeAsMessageSetTo:output];\n");
    } else {
      printer->Print(
        "[self.unknownFields writeToCodedOutputStream:output];\n");
    }

    printer->Outdent();
    printer->Print(
      "}\n"
      "- (int32_t) serializedSize {\n"
      "  int32_t size_ = memoizedSerializedSize;\n"
      "  if (size_ != -1) {\n"
      "    return size_;\n"
      "  }\n"
      "\n"
      "  size_ = 0;\n");
    printer->Indent();

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(sorted_fields[i]).GenerateSerializedSizeCodeSource(printer);
    }

    if (descriptor_->extension_range_count() > 0) {
      printer->Print(
        "size_ += [self extensionsSerializedSize];\n");
    }

    if (descriptor_->options().message_set_wire_format()) {
      printer->Print(
        "size_ += self.unknownFields.serializedSizeAsMessageSet;\n");
    } else {
      printer->Print(
        "size_ += self.unknownFields.serializedSize;\n");
    }

    printer->Outdent();
    printer->Print(
      "  memoizedSerializedSize = size_;\n"
      "  return size_;\n"
      "}\n");
  }

  void MessageGenerator::GenerateMessageDescriptionSource(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(SortFieldsByNumber(descriptor_));

    vector<const Descriptor::ExtensionRange*> sorted_extensions;
    for (int i = 0; i < descriptor_->extension_range_count(); ++i) {
      sorted_extensions.push_back(descriptor_->extension_range(i));
    }
    sort(sorted_extensions.begin(), sorted_extensions.end(),
      ExtensionRangeOrdering());

    printer->Print(
      "- (void) writeDescriptionTo:(NSMutableString*) output withIndent:(NSString*) indent {\n");
    printer->Indent();

    // Merge the fields and the extension ranges, both sorted by field number.
    for (int i = 0, j = 0;
      i < descriptor_->field_count() || j < sorted_extensions.size(); ) {
        if (i == descriptor_->field_count()) {
          GenerateDescriptionOneExtensionRangeSource(printer, sorted_extensions[j++]);
        } else if (j == sorted_extensions.size()) {
          GenerateDescriptionOneFieldSource(printer, sorted_fields[i++]);
        } else if (sorted_fields[i]->number() < sorted_extensions[j]->start) {
          GenerateDescriptionOneFieldSource(printer, sorted_fields[i++]);
        } else {
          GenerateDescriptionOneExtensionRangeSource(printer, sorted_extensions[j++]);
        }
    }

    printer->Print(
      "[self.unknownFields writeDescriptionTo:output withIndent:indent];\n");

    printer->Outdent();
    printer->Print(
      "}\n");
  }


  void MessageGenerator::GenerateMessageIsEqualSource(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(SortFieldsByNumber(descriptor_));

    vector<const Descriptor::ExtensionRange*> sorted_extensions;
    for (int i = 0; i < descriptor_->extension_range_count(); ++i) {
      sorted_extensions.push_back(descriptor_->extension_range(i));
    }
    sort(sorted_extensions.begin(), sorted_extensions.end(),
      ExtensionRangeOrdering());

    printer->Print(
      "- (BOOL) isEqual:(id)other {\n");
    printer->Indent();

    printer->Print(
      "if (other == self) {\n"
      "  return YES;\n"
      "}\n"
      "if (![other isKindOfClass:[$classname$ class]]) {\n"
      "  return NO;\n"
      "}\n"
      "$classname$ *otherMessage = other;\n",
      "classname", ClassName(descriptor_));

    printer->Print("return\n");
    printer->Indent();
    printer->Indent();

    // Merge the fields and the extension ranges, both sorted by field number.
    for (int i = 0, j = 0;
      i < descriptor_->field_count() || j < sorted_extensions.size(); ) {
        if (i == descriptor_->field_count()) {
          GenerateIsEqualOneExtensionRangeSource(printer, sorted_extensions[j++]);
        } else if (j == sorted_extensions.size()) {
          GenerateIsEqualOneFieldSource(printer, sorted_fields[i++]);
        } else if (sorted_fields[i]->number() < sorted_extensions[j]->start) {
          GenerateIsEqualOneFieldSource(printer, sorted_fields[i++]);
        } else {
          GenerateIsEqualOneExtensionRangeSource(printer, sorted_extensions[j++]);
        }
        printer->Print("\n");
    }

    printer->Print(
      "(self.unknownFields == otherMessage.unknownFields ||"
      " (self.unknownFields != nil &&"
      " [self.unknownFields isEqual:otherMessage.unknownFields]));\n");

    printer->Outdent();
    printer->Outdent();
    printer->Outdent();
    printer->Print("}\n");
  }


  void MessageGenerator::GenerateMessageHashSource(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(SortFieldsByNumber(descriptor_));

    vector<const Descriptor::ExtensionRange*> sorted_extensions;
    for (int i = 0; i < descriptor_->extension_range_count(); ++i) {
      sorted_extensions.push_back(descriptor_->extension_range(i));
    }
    sort(sorted_extensions.begin(), sorted_extensions.end(),
      ExtensionRangeOrdering());

    printer->Print(
      "- (NSUInteger) hash {\n");
    printer->Indent();

    printer->Print("NSUInteger hashCode = 7;\n");

    // Merge the fields and the extension ranges, both sorted by field number.
    for (int i = 0, j = 0;
      i < descriptor_->field_count() || j < sorted_extensions.size(); ) {
        if (i == descriptor_->field_count()) {
          GenerateHashOneExtensionRangeSource(printer, sorted_extensions[j++]);
        } else if (j == sorted_extensions.size()) {
          GenerateHashOneFieldSource(printer, sorted_fields[i++]);
        } else if (sorted_fields[i]->number() < sorted_extensions[j]->start) {
          GenerateHashOneFieldSource(printer, sorted_fields[i++]);
        } else {
          GenerateHashOneExtensionRangeSource(printer, sorted_extensions[j++]);
        }
    }

    printer->Print(
      "hashCode = hashCode * 31 + [self.unknownFields hash];\n"
      "return hashCode;\n");

    printer->Outdent();
    printer->Print(
      "}\n");
  }


  void MessageGenerator::GenerateParseFromMethodsSource(io::Printer* printer) {
    printer->Print(
      "+ ($classname$*) parseFromData:(NSData*) data {\n"
      "  return ($classname$*)[[[$classname$ builder] mergeFromData:data] build];\n"
      "}\n"
      "+ ($classname$*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry {\n"
      "  return ($classname$*)[[[$classname$ builder] mergeFromData:data extensionRegistry:extensionRegistry] build];\n"
      "}\n"
      "+ ($classname$*) parseFromInputStream:(NSInputStream*) input {\n"
      "  return ($classname$*)[[[$classname$ builder] mergeFromInputStream:input] build];\n"
      "}\n"
      "+ ($classname$*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry {\n"
      "  return ($classname$*)[[[$classname$ builder] mergeFromInputStream:input extensionRegistry:extensionRegistry] build];\n"
      "}\n"
      "+ ($classname$*) parseFromCodedInputStream:(PBCodedInputStream*) input {\n"
      "  return ($classname$*)[[[$classname$ builder] mergeFromCodedInputStream:input] build];\n"
      "}\n"
      "+ ($classname$*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry {\n"
      "  return ($classname$*)[[[$classname$ builder] mergeFromCodedInputStream:input extensionRegistry:extensionRegistry] build];\n"
      "}\n",
      "classname", ClassName(descriptor_));
  }


  void MessageGenerator::GenerateSerializeOneFieldSource(
    io::Printer* printer, const FieldDescriptor* field) {
      field_generators_.get(field).GenerateSerializationCodeSource(printer);
  }


  void MessageGenerator::GenerateSerializeOneExtensionRangeSource(
    io::Printer* printer, const Descriptor::ExtensionRange* range) {
      printer->Print(
        "[self writeExtensionsToCodedOutputStream:output\n"
        "                                    from:$from$\n"
        "                                      to:$to$];\n",
        "from", SimpleItoa(range->start),
        "to", SimpleItoa(range->end));
  }

  void MessageGenerator::GenerateDescriptionOneFieldSource(
    io::Printer* printer, const FieldDescriptor* field) {
      field_generators_.get(field).GenerateDescriptionCodeSource(printer);
  }


  void MessageGenerator::GenerateDescriptionOneExtensionRangeSource(
    io::Printer* printer, const Descriptor::ExtensionRange* range) {
      printer->Print(
        "[self writeExtensionDescriptionToMutableString:(NSMutableString*)output\n"
        "                                          from:$from$\n"
        "                                            to:$to$\n"
        "                                    withIndent:indent];\n",
        "from", SimpleItoa(range->start),
        "to", SimpleItoa(range->end));
  }


  void MessageGenerator::GenerateIsEqualOneFieldSource(
    io::Printer* printer, const FieldDescriptor* field) {
      field_generators_.get(field).GenerateIsEqualCodeSource(printer);
  }


  void MessageGenerator::GenerateIsEqualOneExtensionRangeSource(
    io::Printer* printer, const Descriptor::ExtensionRange* range) {
      printer->Print(
        "[self isEqualExtensionsInOther:otherMessage from:$from$ to:$to$] &&\n",
        "from", SimpleItoa(range->start), "to", SimpleItoa(range->end));
  }


  void MessageGenerator::GenerateHashOneFieldSource(
    io::Printer* printer, const FieldDescriptor* field) {
      field_generators_.get(field).GenerateHashCodeSource(printer);
  }


  void MessageGenerator::GenerateHashOneExtensionRangeSource(
    io::Printer* printer, const Descriptor::ExtensionRange* range) {
      printer->Print(
        "hashCode = hashCode * 31 + [self hashExtensionsFrom:$from$ to:$to$];\n",
        "from", SimpleItoa(range->start), "to", SimpleItoa(range->end));
  }


  void MessageGenerator::GenerateBuilderSource(io::Printer* printer) {
    printer->Print(
      "@interface $classname$_Builder()\n"
      "@property (retain) $classname$* result;\n"
      "@end\n"
      "\n"
      "@implementation $classname$_Builder\n"
      "@synthesize result;\n"
      "- (void) dealloc {\n"
      "  self.result = nil;\n"
      "  [super dealloc];\n"
      "}\n",
      "classname", ClassName(descriptor_));

    printer->Print(
      "- (id) init {\n"
      "  if ((self = [super init])) {\n"
      "    self.result = [[[$classname$ alloc] init] autorelease];\n"
      "  }\n"
      "  return self;\n"
      "}\n",
      "classname", ClassName(descriptor_));

    GenerateCommonBuilderMethodsSource(printer);
    GenerateBuilderParsingMethodsSource(printer);

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateBuilderMembersSource(printer);
    }

    printer->Print("@end\n\n");
  }


  void MessageGenerator::GenerateCommonBuilderMethodsSource(io::Printer* printer) {
    if (descriptor_->extension_range_count() > 0) {
      printer->Print(
      "- (PBExtendableMessage*) internalGetResult {\n"
      "  return result;\n"
      "}\n");
    } else {
      printer->Print(
      "- (PBGeneratedMessage*) internalGetResult {\n"
      "  return result;\n"
      "}\n");
    }

    printer->Print(
      "- ($classname$_Builder*) clear {\n"
      "  self.result = [[[$classname$ alloc] init] autorelease];\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder*) clone {\n"
      "  return [$classname$ builderWithPrototype:result];\n"
      "}\n"
      "- ($classname$*) defaultInstance {\n"
      "  return [$classname$ defaultInstance];\n"
      "}\n",
      "classname", ClassName(descriptor_));

    printer->Print(
      "- ($classname$*) build {\n"
      "  [self checkInitialized];\n"
      "  return [self buildPartial];\n"
      "}\n"
      "- ($classname$*) buildPartial {\n",
      "classname", ClassName(descriptor_));
    printer->Indent();

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateBuildingCodeSource(printer);
    }

    printer->Outdent();
    printer->Print(
      "  $classname$* returnMe = [[result retain] autorelease];\n"
      "  self.result = nil;\n"
      "  return returnMe;\n"
      "}\n",
      "classname", ClassName(descriptor_));

    printer->Print(
      "- ($classname$_Builder*) mergeFrom:($classname$*) other {\n"
      // Optimization:  If other is the default instance, we know none of its
      //   fields are set so we can skip the merge.
      "  if (other == [$classname$ defaultInstance]) {\n"
      "    return self;\n"
      "  }\n",
      "classname", ClassName(descriptor_));
    printer->Indent();

    for (int i = 0; i < descriptor_->field_count(); i++) {
      field_generators_.get(descriptor_->field(i)).GenerateMergingCodeSource(printer);
    }

    printer->Outdent();

    if (descriptor_->extension_range_count() > 0) {
      printer->Print(
        "  [self mergeExtensionFields:other];\n");
    }

    printer->Print(
      "  [self mergeUnknownFields:other.unknownFields];\n"
      "  return self;\n"
      "}\n");
  }


  void MessageGenerator::GenerateBuilderParsingMethodsSource(io::Printer* printer) {
    scoped_array<const FieldDescriptor*> sorted_fields(
      SortFieldsByNumber(descriptor_));

    printer->Print(
      "- ($classname$_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input {\n"
      "  return [self mergeFromCodedInputStream:input extensionRegistry:[PBExtensionRegistry emptyRegistry]];\n"
      "}\n"
      "- ($classname$_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry {\n",
      "classname", ClassName(descriptor_));
    printer->Indent();

    printer->Print(
      "PBUnknownFieldSet_Builder* unknownFields = [PBUnknownFieldSet builderWithUnknownFields:self.unknownFields];\n"
      "while (YES) {\n");
    printer->Indent();

    printer->Print(
      "int32_t tag = [input readTag];\n"
      "switch (tag) {\n");
    printer->Indent();

    printer->Print(
      "case 0:\n"          // zero signals EOF / limit reached
      "  [self setUnknownFields:[unknownFields build]];\n"
      "  return self;\n"
      "default: {\n"
      "  if (![self parseUnknownField:input unknownFields:unknownFields extensionRegistry:extensionRegistry tag:tag]) {\n"
      "    [self setUnknownFields:[unknownFields build]];\n"
      "    return self;\n"   // it's an endgroup tag
      "  }\n"
      "  break;\n"
      "}\n");

    for (int i = 0; i < descriptor_->field_count(); i++) {
      const FieldDescriptor* field = sorted_fields[i];
      uint32 tag = WireFormatLite::MakeTag(field->number(),
        WireFormat::WireTypeForField(field));

      printer->Print(
        "case $tag$: {\n",
        "tag", SimpleItoa(tag));
      printer->Indent();

      field_generators_.get(field).GenerateParsingCodeSource(printer);

      printer->Outdent();
      printer->Print(
        "  break;\n"
        "}\n");
    }

    printer->Outdent();
    printer->Outdent();
    printer->Outdent();
    printer->Print(
      "    }\n" // switch (tag)
      "  }\n"   // while (true)
      "}\n");
  }


  void MessageGenerator::GenerateIsInitializedSource(io::Printer* printer) {
    printer->Print(
      "- (BOOL) isInitialized {\n");
    printer->Indent();

    // Check that all required fields in this message are set.
    // TODO(kenton):  We can optimize this when we switch to putting all the
    //   "has" fields into a single bitfield.
    for (int i = 0; i < descriptor_->field_count(); i++) {
      const FieldDescriptor* field = descriptor_->field(i);

      if (field->is_required()) {
        printer->Print(
          "if (!self.has$capitalized_name$) {\n"
          "  return NO;\n"
          "}\n",
          "capitalized_name", UnderscoresToCapitalizedCamelCase(field));
      }
    }

    // Now check that all embedded messages are initialized.
    for (int i = 0; i < descriptor_->field_count(); i++) {
      const FieldDescriptor* field = descriptor_->field(i);
      if (field->cpp_type() == FieldDescriptor::CPPTYPE_MESSAGE &&
        HasRequiredFields(field->message_type())) {

          map<string,string> vars;
          vars["type"] = ClassName(field->message_type());
          vars["name"] = UnderscoresToCamelCase(field);
          vars["capitalized_name"] = UnderscoresToCapitalizedCamelCase(field);

          switch (field->label()) {
            case FieldDescriptor::LABEL_REQUIRED:
              printer->Print(vars,
                "if (!self.$name$.isInitialized) {\n"
                "  return NO;\n"
                "}\n");
              break;
            case FieldDescriptor::LABEL_OPTIONAL:
              printer->Print(vars,
                "if (self.has$capitalized_name$) {\n"
                "  if (!self.$name$.isInitialized) {\n"
                "    return NO;\n"
                "  }\n"
                "}\n");
              break;
            case FieldDescriptor::LABEL_REPEATED:
              printer->Print(vars,
                "for ($type$* element in self.$name$) {\n"
                "  if (!element.isInitialized) {\n"
                "    return NO;\n"
                "  }\n"
                "}\n");
              break;
          }
      }
    }

    if (descriptor_->extension_range_count() > 0) {
      printer->Print(
        "if (!self.extensionsAreInitialized) {\n"
        "  return NO;\n"
        "}\n");
    }

    printer->Outdent();
    printer->Print(
      "  return YES;\n"
      "}\n");
  }
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
