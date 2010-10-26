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

#include "objc_extension.h"

#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/io/printer.h>

#include "objc_extension.h"
#include "objc_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

  ExtensionGenerator::ExtensionGenerator(string classname, const FieldDescriptor* descriptor)
    : classname_(classname),
    descriptor_(descriptor) {
  }


  ExtensionGenerator::~ExtensionGenerator() {
  }


  void ExtensionGenerator::GenerateMembersHeader(io::Printer* printer) {
    map<string, string> vars;
    vars["name"] = UnderscoresToCamelCase(descriptor_);

    printer->Print(vars,
      "+ (id<PBExtensionField>) $name$;\n");
  }


  void ExtensionGenerator::GenerateFieldsSource(io::Printer* printer) {
    map<string, string> vars;
    vars["name"] = UnderscoresToCamelCase(descriptor_);
    vars["containing_type"] = classname_;

    printer->Print(vars,
      "static id<PBExtensionField> $containing_type$_$name$ = nil;\n");
  }


  void ExtensionGenerator::GenerateMembersSource(io::Printer* printer) {
    map<string, string> vars;
    vars["name"] = UnderscoresToCamelCase(descriptor_);
    vars["containing_type"] = classname_;

    printer->Print(vars,
      "+ (id<PBExtensionField>) $name$ {\n"
      "  return $containing_type$_$name$;\n"
      "}\n");
  }

  void ExtensionGenerator::GenerateInitializationSource(io::Printer* printer) {
    map<string, string> vars;
    vars["name"] = UnderscoresToCamelCase(descriptor_);
    vars["containing_type"] = classname_;
    vars["extended_type"] = ClassName(descriptor_->containing_type());
    vars["number"] = SimpleItoa(descriptor_->number());

    const bool isPacked = descriptor_->options().packed();
    vars["is_repeated"] = descriptor_->is_repeated() ? "YES" : "NO";
    vars["is_packed"] = isPacked ? "YES" : "NO";
    vars["is_wire_format"] = descriptor_->containing_type()->options().message_set_wire_format() ? "YES" : "NO";

    ObjectiveCType java_type = GetObjectiveCType(descriptor_);
    string singular_type;
    switch (java_type) {
    case OBJECTIVECTYPE_MESSAGE:
      vars["type"] = ClassName(descriptor_->message_type());
      break;
    default:
      vars["type"] = BoxedPrimitiveTypeName(java_type);
      break;
    }

    switch (descriptor_->type()) {
      case FieldDescriptor::TYPE_INT32:
        vars["extension_type"] = "PBExtensionTypeInt32";
        break;
      case FieldDescriptor::TYPE_UINT32:
        vars["extension_type"] = "PBExtensionTypeUInt32";
        break;
      case FieldDescriptor::TYPE_SINT32:
        vars["extension_type"] = "PBExtensionTypeSInt32";
        break;
      case FieldDescriptor::TYPE_FIXED32:
        vars["extension_type"] = "PBExtensionTypeFixed32";
        break;
      case FieldDescriptor::TYPE_SFIXED32:
        vars["extension_type"] = "PBExtensionTypeSFixed32";
        break;
      case FieldDescriptor::TYPE_INT64:
        vars["extension_type"] = "PBExtensionTypeInt64";
        break;
      case FieldDescriptor::TYPE_UINT64:
        vars["extension_type"] = "PBExtensionTypeUInt64";
        break;
      case FieldDescriptor::TYPE_SINT64:
        vars["extension_type"] = "PBExtensionTypeSInt64";
        break;
      case FieldDescriptor::TYPE_FIXED64:
        vars["extension_type"] = "PBExtensionTypeFixed64";
        break;
      case FieldDescriptor::TYPE_SFIXED64:
        vars["extension_type"] = "PBExtensionTypeSFixed64";
        break;
      case FieldDescriptor::TYPE_FLOAT:
        vars["extension_type"] = "PBExtensionTypeFloat";
        break;
      case FieldDescriptor::TYPE_DOUBLE:
        vars["extension_type"] = "PBExtensionTypeDouble";
        break;
      case FieldDescriptor::TYPE_BOOL: 
        vars["extension_type"] = "PBExtensionTypeBool";
        break;
      case FieldDescriptor::TYPE_STRING:
        vars["extension_type"] = "PBExtensionTypeString";
        break;
      case FieldDescriptor::TYPE_BYTES:
        vars["extension_type"] = "PBExtensionTypeBytes";
        break;
      case FieldDescriptor::TYPE_MESSAGE:
        vars["extension_type"] = "PBExtensionTypeMessage";
        break;
      case FieldDescriptor::TYPE_ENUM:
        vars["extension_type"] = "PBExtensionTypeEnum";
        break;
      case FieldDescriptor::TYPE_GROUP:
        vars["extension_type"] = "PBExtensionTypeGroup";
        break;
    }

    vars["default"] = descriptor_->is_repeated() 
      ? string("[PBArray arrayWithValueType:") + GetArrayValueType(descriptor_) + "]"
      : BoxValue(descriptor_, DefaultValue(descriptor_));

    printer->Print(vars,
      "$containing_type$_$name$ =\n");

    printer->Print(
      vars,
      "  [[PBConcreteExtensionField extensionWithType:$extension_type$\n"
      "                                 extendedClass:[$extended_type$ class]\n"
      "                                   fieldNumber:$number$\n"
      "                                  defaultValue:$default$\n"
      "                           messageOrGroupClass:[$type$ class]\n"
      "                                    isRepeated:$is_repeated$\n"
      "                                      isPacked:$is_packed$\n"
      "                        isMessageSetWireFormat:$is_wire_format$] retain];\n");
  }

  void ExtensionGenerator::GenerateRegistrationSource(io::Printer* printer) {
    printer->Print(
      "[registry addExtension:$scope$_$name$];\n",
      "scope", classname_,
      "name", UnderscoresToCamelCase(descriptor_));
  }
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
