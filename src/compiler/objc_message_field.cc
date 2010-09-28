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

#include "objc_message_field.h"

#include <map>
#include <string>

#include <google/protobuf/io/printer.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/stubs/strutil.h>

#include "objc_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

  namespace {
    void SetMessageVariables(const FieldDescriptor* descriptor,
      map<string, string>* variables) {
        (*variables)["classname"] = ClassName(descriptor->containing_type());
        (*variables)["name"] = UnderscoresToCamelCase(descriptor);
        (*variables)["capitalized_name"] = UnderscoresToCapitalizedCamelCase(descriptor);
        (*variables)["list_name"] = UnderscoresToCamelCase(descriptor) + "List";
        (*variables)["mutable_list_name"] = "mutable" + UnderscoresToCapitalizedCamelCase(descriptor) + "List";
        (*variables)["number"] = SimpleItoa(descriptor->number());
        (*variables)["type"] = ClassName(descriptor->message_type());
        if (IsPrimitiveType(GetObjectiveCType(descriptor))) {
          (*variables)["storage_type"] = ClassName(descriptor->message_type());
        } else {
          (*variables)["storage_type"] = string(ClassName(descriptor->message_type())) + "*";
        }
        (*variables)["group_or_message"] =
          (descriptor->type() == FieldDescriptor::TYPE_GROUP) ?
          "Group" : "Message";

        (*variables)["boxed_value"] = BoxValue(descriptor, "value");

        string unboxed_value = "value";
        switch (GetObjectiveCType(descriptor)) {
          case OBJECTIVECTYPE_INT:
            unboxed_value = "[value intValue]";
            break;
          case OBJECTIVECTYPE_LONG:
            unboxed_value = "[value longLongValue]";
            break;
          case OBJECTIVECTYPE_FLOAT:
            unboxed_value = "[value floatValue]";
            break;
          case OBJECTIVECTYPE_DOUBLE:
            unboxed_value = "[value doubleValue]";
            break;
          case OBJECTIVECTYPE_BOOLEAN:
            unboxed_value = "[value boolValue]";
            break;
        } 

        (*variables)["unboxed_value"] = unboxed_value;
    }
  }  // namespace


  MessageFieldGenerator::MessageFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetMessageVariables(descriptor, &variables_);
  }


  MessageFieldGenerator::~MessageFieldGenerator() {
  }


  void MessageFieldGenerator::GenerateHasFieldHeader(io::Printer* printer) const {
    printer->Print(variables_, "BOOL has$capitalized_name$_:1;\n");
  }


  void MessageFieldGenerator::GenerateFieldHeader(io::Printer* printer) const {
    printer->Print(variables_, "$storage_type$ $name$;\n");
  }


  void MessageFieldGenerator::GenerateHasPropertyHeader(io::Printer* printer) const {
    printer->Print(variables_, "- (BOOL) has$capitalized_name$;\n");
}


  void MessageFieldGenerator::GeneratePropertyHeader(io::Printer* printer) const {
    printer->Print(variables_, "@property (readonly, retain) $storage_type$ $name$;\n");
  }


  void MessageFieldGenerator::GenerateExtensionSource(io::Printer* printer) const {
    printer->Print(variables_,
      "@property (retain) $storage_type$ $name$;\n");
  }


  void MessageFieldGenerator::GenerateMembersHeader(io::Printer* printer) const {
  }


  void MessageFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$ {\n"
      "  return !!has$capitalized_name$_;\n"
      "}\n"
      "- (void) setHas$capitalized_name$:(BOOL) value {\n"
      "  has$capitalized_name$_ = !!value;\n"
      "}\n"
      "@synthesize $name$;\n");
  }


  void MessageFieldGenerator::GenerateDeallocSource(io::Printer* printer) const {
    printer->Print(variables_, "self.$name$ = nil;\n");
  }


  void MessageFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
    printer->Print(variables_, "self.$name$ = [$type$ defaultInstance];\n");
  }


  void MessageFieldGenerator::GenerateBuilderMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$;\n"
      "- ($storage_type$) $name$;\n"
      "- ($classname$_Builder*) set$capitalized_name$:($storage_type$) value;\n"
      "- ($classname$_Builder*) set$capitalized_name$Builder:($type$_Builder*) builderForValue;\n"
      "- ($classname$_Builder*) merge$capitalized_name$:($storage_type$) value;\n"
      "- ($classname$_Builder*) clear$capitalized_name$;\n");
  }

  void MessageFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (BOOL) has$capitalized_name$ {\n"
      "  return result.has$capitalized_name$;\n"
      "}\n"
      "- ($storage_type$) $name$ {\n"
      "  return result.$name$;\n"
      "}\n"
      "- ($classname$_Builder*) set$capitalized_name$:($storage_type$) value {\n"
      "  result.has$capitalized_name$ = YES;\n"
      "  result.$name$ = value;\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder*) set$capitalized_name$Builder:($type$_Builder*) builderForValue {\n"
      "  return [self set$capitalized_name$:[builderForValue build]];\n"
      "}\n"
      "- ($classname$_Builder*) merge$capitalized_name$:($storage_type$) value {\n"
      "  if (result.has$capitalized_name$ &&\n"
      "      result.$name$ != [$type$ defaultInstance]) {\n"
      "    result.$name$ =\n"
      "      [[[$type$ builderWithPrototype:result.$name$] mergeFrom:value] buildPartial];\n"
      "  } else {\n"
      "    result.$name$ = value;\n"
      "  }\n"
      "  result.has$capitalized_name$ = YES;\n"
      "  return self;\n"
      "}\n"
      "- ($classname$_Builder*) clear$capitalized_name$ {\n"
      "  result.has$capitalized_name$ = NO;\n"
      "  result.$name$ = [$type$ defaultInstance];\n"
      "  return self;\n"
      "}\n");
  }


  void MessageFieldGenerator::GenerateMergingCodeHeader(io::Printer* printer) const {
  }


  void MessageFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (other.has$capitalized_name$) {\n"
      "  [self merge$capitalized_name$:other.$name$];\n"
      "}\n");
  }


  void MessageFieldGenerator::GenerateBuildingCodeHeader(io::Printer* printer) const {
  }


  void MessageFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }


  void MessageFieldGenerator::GenerateParsingCodeHeader(io::Printer* printer) const {
  }


  void MessageFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "$type$_Builder* subBuilder = [$type$ builder];\n"
      "if (self.has$capitalized_name$) {\n"
      "  [subBuilder mergeFrom:self.$name$];\n"
      "}\n");

    if (descriptor_->type() == FieldDescriptor::TYPE_GROUP) {
      printer->Print(variables_,
        "[input readGroup:$number$ builder:subBuilder extensionRegistry:extensionRegistry];\n");
    } else {
      printer->Print(variables_,
        "[input readMessage:subBuilder extensionRegistry:extensionRegistry];\n");
    }

    printer->Print(variables_,
      "[self set$capitalized_name$:[subBuilder buildPartial]];\n");
  }


  void MessageFieldGenerator::GenerateSerializationCodeHeader(io::Printer* printer) const {
  }


  void MessageFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (self.has$capitalized_name$) {\n"
      "  [output write$group_or_message$:$number$ value:self.$name$];\n"
      "}\n");
  }


  void MessageFieldGenerator::GenerateSerializedSizeCodeHeader(io::Printer* printer) const {
  }


  void MessageFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (self.has$capitalized_name$) {\n"
      "  size += compute$group_or_message$Size($number$, self.$name$);\n"
      "}\n");
  }

  void MessageFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
  }


  string MessageFieldGenerator::GetBoxedType() const {
    return ClassName(descriptor_->message_type());
  }


  RepeatedMessageFieldGenerator::RepeatedMessageFieldGenerator(const FieldDescriptor* descriptor)
    : descriptor_(descriptor) {
      SetMessageVariables(descriptor, &variables_);
  }


  RepeatedMessageFieldGenerator::~RepeatedMessageFieldGenerator() {
  }


  void RepeatedMessageFieldGenerator::GenerateHasFieldHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateFieldHeader(io::Printer* printer) const {
    printer->Print(variables_, "NSMutableArray* $mutable_list_name$;\n");
  }


  void RepeatedMessageFieldGenerator::GenerateHasPropertyHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GeneratePropertyHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateExtensionSource(io::Printer* printer) const {
    printer->Print(variables_,
      "@property (retain) NSMutableArray* $mutable_list_name$;\n");
  }


  void RepeatedMessageFieldGenerator::GenerateSynthesizeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "@synthesize $mutable_list_name$;\n");
  }


  void RepeatedMessageFieldGenerator::GenerateDeallocSource(io::Printer* printer) const {
    printer->Print(variables_,
      "self.$mutable_list_name$ = nil;\n");
  }


  void RepeatedMessageFieldGenerator::GenerateInitializationSource(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$;\n"
      "- ($storage_type$) $name$AtIndex:(int32_t) index;\n");
  }

  void RepeatedMessageFieldGenerator::GenerateMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$ {\n"
      "  return $mutable_list_name$;\n"
      "}\n"
      "- ($storage_type$) $name$AtIndex:(int32_t) index {\n"
      "  id value = [$mutable_list_name$ objectAtIndex:index];\n"
      "  return $unboxed_value$;\n"
      "}\n");
  }


  void RepeatedMessageFieldGenerator::GenerateBuilderMembersHeader(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$;\n"
      "- ($storage_type$) $name$AtIndex:(int32_t) index;\n"
      "- ($classname$_Builder*) replace$capitalized_name$AtIndex:(int32_t) index with:($storage_type$) value;\n"
      "- ($classname$_Builder*) add$capitalized_name$:($storage_type$) value;\n"
      "- ($classname$_Builder*) addAll$capitalized_name$:(NSArray*) values;\n"
      "- ($classname$_Builder*) clear$capitalized_name$List;\n");
  }

  void RepeatedMessageFieldGenerator::GenerateBuilderMembersSource(io::Printer* printer) const {
    printer->Print(variables_,
      "- (NSArray*) $list_name$ {\n"
      "  if (result.$mutable_list_name$ == nil) { return [NSArray array]; }\n"
      "  return result.$mutable_list_name$;\n"
      "}\n"
      "- ($storage_type$) $name$AtIndex:(int32_t) index {\n"
      "  return [result $name$AtIndex:index];\n"
      "}\n"
      "- ($classname$_Builder*) replace$capitalized_name$AtIndex:(int32_t) index with:($storage_type$) value {\n"
      "  [result.$mutable_list_name$ replaceObjectAtIndex:index withObject:$boxed_value$];\n"
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

    printer->Print(
      variables_,
      "- ($classname$_Builder*) add$capitalized_name$:($storage_type$) value {\n"
      "  if (result.$mutable_list_name$ == nil) {\n"
      "    result.$mutable_list_name$ = [NSMutableArray array];\n"
      "  }\n"
      "  [result.$mutable_list_name$ addObject:$boxed_value$];\n"
      "  return self;\n"
      "}\n");
  }


  void RepeatedMessageFieldGenerator::GenerateMergingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateBuildingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateParsingCodeHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateSerializationCodeHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateSerializedSizeCodeHeader(io::Printer* printer) const {
  }


  void RepeatedMessageFieldGenerator::GenerateMergingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "if (other.$mutable_list_name$.count > 0) {\n"
      "  if (result.$mutable_list_name$ == nil) {\n"
      "    result.$mutable_list_name$ = [NSMutableArray array];\n"
      "  }\n"
      "  [result.$mutable_list_name$ addObjectsFromArray:other.$mutable_list_name$];\n"
      "}\n");
  }


  void RepeatedMessageFieldGenerator::GenerateBuildingCodeSource(io::Printer* printer) const {
  }

  void RepeatedMessageFieldGenerator::GenerateParsingCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "$type$_Builder* subBuilder = [$type$ builder];\n");

    if (descriptor_->type() == FieldDescriptor::TYPE_GROUP) {
      printer->Print(variables_,
        "[input readGroup:$number$ builder:subBuilder extensionRegistry:extensionRegistry];\n");
    } else {
      printer->Print(variables_,
        "[input readMessage:subBuilder extensionRegistry:extensionRegistry];\n");
    }

    printer->Print(variables_,
      "[self add$capitalized_name$:[subBuilder buildPartial]];\n");
  }

  void RepeatedMessageFieldGenerator::GenerateSerializationCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "for ($type$* element in self.$list_name$) {\n"
      "  [output write$group_or_message$:$number$ value:element];\n"
      "}\n");
  }

  void RepeatedMessageFieldGenerator::GenerateSerializedSizeCodeSource(io::Printer* printer) const {
    printer->Print(variables_,
      "for ($type$* element in self.$list_name$) {\n"
      "  size += compute$group_or_message$Size($number$, element);\n"
      "}\n");
  }

  string RepeatedMessageFieldGenerator::GetBoxedType() const {
    return ClassName(descriptor_->message_type());
  }
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
