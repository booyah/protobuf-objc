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

#include "objc_enum_field.h"

#include <map>
#include <string>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>

#include "objc_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

  namespace {
    void SetEnumVariables(const FieldDescriptor* descriptor,
      map<string, string>* variables) {
        const EnumValueDescriptor* default_value;
        default_value = descriptor->default_value_enum();

        string type = ClassName(descriptor->enum_type());

        (*variables)["classname"]             = ClassName(descriptor->containing_type());
        (*variables)["name"]                  = UnderscoresToCamelCase(descriptor);
        (*variables)["capitalized_name"]      = UnderscoresToCapitalizedCamelCase(descriptor);
        (*variables)["list_name"]             = UnderscoresToCamelCase(descriptor) + "List";
        (*variables)["mutable_list_name"] = "mutable" + UnderscoresToCapitalizedCamelCase(descriptor) + "List";
        (*variables)["number"] = SimpleItoa(descriptor->number());
        (*variables)["type"] = type;
        (*variables)["default"] = EnumValueName(default_value);
        (*variables)["boxed_value"] = "[NSNumber numberWithInt:value]";
        (*variables)["unboxed_value"] = "[value intValue]";
        (*variables)["tag"] = SimpleItoa(internal::WireFormat::MakeTag(descriptor));
        (*variables)["tag_size"] = SimpleItoa(
          internal::WireFormat::TagSize(descriptor->number(), descriptor->type()));
    }
  }  // namespace

  EnumFieldGenerator::EnumFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetEnumVariables(descriptor, &variables_);
  }


  EnumFieldGenerator::~EnumFieldGenerator() {
  }


  void EnumFieldGenerator::GenerateHasFieldHeader(io::Printer* printer) const {
    printer->Print(variables_, "BOOL has$capitalized_name$_:1;\n");
  }


  void EnumFieldGenerator::GenerateFieldHeader(io::Printer* printer) const {
    printer->Print(variables_, "$type$ $name$;\n");
  }


  void EnumFieldGenerator::GenerateHasPropertyHeader(io::Printer* printer) const {
    printer->Print(variables_, "- (BOOL) has$capitalized_name$;\n");
  }


  void EnumFieldGenerator::GeneratePropertyHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "@property (readonly) $type$ $name$;\n");
  }


  void EnumFieldGenerator::GenerateExtensionSource(io::Printer* printer) const {
    printer->Print(variables_,
      "@property $type$ $name$;\n");
  }


  void EnumFieldGenerator::GenerateMembersHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$ {\n"
      "  return !!has$capitalized_name$_;\n"
      "}\n"
      "- (void) setHas$capitalized_name$:(BOOL) value {\n"
      "  has$capitalized_name$_ = !!value;\n"
      "}\n"
      "@synthesize $name$;\n");
  }


  void EnumFieldGenerator::GenerateDeallocSource(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
    printer->Print(variables_, "self.$name$ = $default$;\n");
  }


  void EnumFieldGenerator::GenerateBuilderMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$;\n"
      "- ($type$) $name$;\n"\
      "- ($classname$_Builder*) set$capitalized_name$:($type$) value;\n"
      "- ($classname$_Builder*) clear$capitalized_name$;\n");
  }


  void EnumFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$ {\n"
      "  return result.has$capitalized_name$;\n"
      "}\n"
      "- ($type$) $name$ {\n"
      "  return result.$name$;\n"
      "}\n"
      "- ($classname$_Builder*) set$capitalized_name$:($type$) value {\n"
      "  result.has$capitalized_name$ = YES;\n"
      "  result.$name$ = value;\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder*) clear$capitalized_name$ {\n"
      "  result.has$capitalized_name$ = NO;\n"
      "  result.$name$ = $default$;\n"
      "  return self;\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateMergingCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (other.has$capitalized_name$) {\n"
      "  [self set$capitalized_name$:other.$name$];\n"
      "}\n");
  }

  void EnumFieldGenerator::GenerateBuildingCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateParsingCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "int32_t value = [input readEnum];\n"
      "if ($type$IsValidValue(value)) {\n"
      "  [self set$capitalized_name$:value];\n"
      "} else {\n"
      "  [unknownFields mergeVarintField:$number$ value:value];\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateSerializationCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (self.has$capitalized_name$) {\n"
      "  [output writeEnum:$number$ value:self.$name$];\n"
      "}\n");
  }


  void EnumFieldGenerator::GenerateSerializedSizeCodeHeader(io::Printer* printer) const {
  }


  void EnumFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (self.has$capitalized_name$) {\n"
      "  size += computeEnumSize($number$, self.$name$);\n"
      "}\n");
  }


  string EnumFieldGenerator::GetBoxedType() const {
    return ClassName(descriptor_->enum_type());
  }


  RepeatedEnumFieldGenerator::RepeatedEnumFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetEnumVariables(descriptor, &variables_);
  }


  RepeatedEnumFieldGenerator::~RepeatedEnumFieldGenerator() {
  }


  void RepeatedEnumFieldGenerator::GenerateHasFieldHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateFieldHeader(io::Printer* printer) const {
    printer->Print(variables_, "NSMutableArray* $mutable_list_name$;\n");
    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "int32_t $name$MemoizedSerializedSize;\n");
    }
  }


  void RepeatedEnumFieldGenerator::GenerateHasPropertyHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GeneratePropertyHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateExtensionSource(io::Printer* printer) const {
    printer->Print(variables_,
      "@property (retain) NSMutableArray* $mutable_list_name$;\n");
  }

  void RepeatedEnumFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "@synthesize $mutable_list_name$;\n");
  }

  void RepeatedEnumFieldGenerator::GenerateDeallocSource(io::Printer* printer) const {
    printer->Print(variables_,
      "self.$mutable_list_name$ = nil;\n");
  }


  void RepeatedEnumFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$;\n"
      "- ($type$) $name$AtIndex:(int32_t) index;\n");
  }

  void RepeatedEnumFieldGenerator::GenerateBuilderMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$;\n"
      "- ($type$) $name$AtIndex:(int32_t) index;\n"
      "- ($classname$_Builder*) replace$capitalized_name$AtIndex:(int32_t) index with:($type$) value;\n"
      "- ($classname$_Builder*) add$capitalized_name$:($type$) value;\n"
      "- ($classname$_Builder*) addAll$capitalized_name$:(NSArray*) values;\n"
      "- ($classname$_Builder*) clear$capitalized_name$List;\n");
  }


  void RepeatedEnumFieldGenerator::GenerateMergingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateBuildingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateParsingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateSerializationCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateSerializedSizeCodeHeader(io::Printer* printer) const {
  }


  void RepeatedEnumFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$ {\n"
      "  return $mutable_list_name$;\n"
      "}\n"
      "- ($type$) $name$AtIndex:(int32_t) index {\n"
      "  NSNumber* value = [$mutable_list_name$ objectAtIndex:index];\n"
      "  return [value intValue];\n"
      "}\n");
  }

  void RepeatedEnumFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$ {\n"
      "  return result.$mutable_list_name$;\n"
      "}\n"
      "- ($type$) $name$AtIndex:(int32_t) index {\n"
      "  return [result $name$AtIndex:index];\n"
      "}\n"
      "- ($classname$_Builder*) replace$capitalized_name$AtIndex:(int32_t) index with:($type$) value {\n"
      "  [result.$mutable_list_name$ replaceObjectAtIndex:index withObject:[NSNumber numberWithInt:value]];\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder*) add$capitalized_name$:($type$) value {\n"
      "  if (result.$mutable_list_name$ == nil) {\n"
      "    result.$mutable_list_name$ = [NSMutableArray array];\n"
      "  }\n"
      "  [result.$mutable_list_name$ addObject:[NSNumber numberWithInt:value]];\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder*) addAll$capitalized_name$:(NSArray*) values {\n"
      "  if (result.$mutable_list_name$ == nil) {\n"
      "    result.$mutable_list_name$ = [NSMutableArray array];\n"
      "  }\n"
      "  [result.$mutable_list_name$ addObjectsFromArray:values];\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder*) clear$capitalized_name$List {\n"
      "  result.$mutable_list_name$ = nil;\n"
      "  return self;\n"
      "}\n");
  }

  void RepeatedEnumFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (other.$mutable_list_name$.count > 0) {\n"
      "  if (result.$mutable_list_name$ == nil) {\n"
      "    result.$mutable_list_name$ = [NSMutableArray array];\n"
      "  }\n"
      "  [result.$mutable_list_name$ addObjectsFromArray:other.$mutable_list_name$];\n"
      "}\n");
  }

  void RepeatedEnumFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }

  void RepeatedEnumFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    // If packed, set up the while loop
    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "int32_t length = [input readRawVarint32];\n"
        "int32_t oldLimit = [input pushLimit:length];\n"
        "while (input.bytesUntilLimit > 0) {\n");
      printer->Indent();
    }

    printer->Print(variables_,
      "int32_t value = [input readEnum];\n"
      "if ($type$IsValidValue(value)) {\n"
      "  [self add$capitalized_name$:value];\n"
      "} else {\n"
      "  [unknownFields mergeVarintField:$number$ value:value];\n"
      "}\n");

    if (descriptor_->options().packed()) {
      printer->Outdent();
      printer->Print(variables_,
        "}\n"
        "[input popLimit:oldLimit];\n");
    }
  }

  void RepeatedEnumFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {
    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "if (self.$list_name$.count > 0) {\n"
        "  [output writeRawVarint32:$tag$];\n"
        "  [output writeRawVarint32:$name$MemoizedSerializedSize];\n"
        "}\n"
        "for (NSNumber* element in self.$list_name$) {\n"
        "  [output writeEnumNoTag:element.intValue];\n"
        "}\n");
    } else {
      printer->Print(variables_,
        "for (NSNumber* element in self.$list_name$) {\n"
        "  [output writeEnum:$number$ value:element.intValue];\n"
        "}\n");
    }
  }


  void RepeatedEnumFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "{\n"
      "  int32_t dataSize = 0;\n");
    printer->Indent();

    printer->Print(variables_,
      "for (NSNumber* element in self.$list_name$) {\n"
      "  dataSize += computeEnumSizeNoTag(element.intValue);\n"
      "}\n");

    printer->Print(
      "size += dataSize;\n");

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "if (self.$list_name$.count > 0) {\n"
        "  size += $tag_size$;\n"
        "  size += computeRawVarint32Size(dataSize);\n"
        "}\n");
    } else {
      printer->Print(variables_,
        "size += $tag_size$ * self.$list_name$.count;\n");
    }

    if (descriptor_->options().packed()) {
      printer->Print(variables_,
        "$name$MemoizedSerializedSize = dataSize;\n");
    }

    printer->Outdent();
    printer->Print("}\n");
  }


  string RepeatedEnumFieldGenerator::GetBoxedType() const {
    return ClassName(descriptor_->enum_type());
  }
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
