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

#include "objc_enum.h"

#include <map>
#include <string>

#include <google/protobuf/io/printer.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/stubs/strutil.h>

#include "objc_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

  EnumGenerator::EnumGenerator(const EnumDescriptor* descriptor)
    : descriptor_(descriptor) {
      for (int i = 0; i < descriptor_->value_count(); i++) {
        const EnumValueDescriptor* value = descriptor_->value(i);
        const EnumValueDescriptor* canonical_value =
          descriptor_->FindValueByNumber(value->number());

        if (value == canonical_value) {
          canonical_values_.push_back(value);
        } else {
          Alias alias;
          alias.value = value;
          alias.canonical_value = canonical_value;
          aliases_.push_back(alias);
        }
      }
  }


  EnumGenerator::~EnumGenerator() {
  }


  void EnumGenerator::GenerateHeader(io::Printer* printer) {
    printer->Print(
      "typedef enum {\n");
    printer->Indent();
    
    for (int i = 0; i < canonical_values_.size(); i++) {
      printer->Print(
        "$name$ = $value$,\n",
        "name", EnumValueName(canonical_values_[i]),
        "value", SimpleItoa(canonical_values_[i]->number()));
    }

    printer->Outdent();
    printer->Print(
      "} $classname$;\n"
      "\n"
      "BOOL $classname$IsValidValue($classname$ value);\n"
      "\n",
      "classname", ClassName(descriptor_));
  }


  void EnumGenerator::GenerateSource(io::Printer* printer) {
    printer->Print(
      "BOOL $classname$IsValidValue($classname$ value) {\n"
      "  switch (value) {\n",
      "classname", ClassName(descriptor_));

    for (int i = 0; i < canonical_values_.size(); i++) {
      printer->Print(
        "    case $name$:\n",
        "name", EnumValueName(canonical_values_[i]));
    }

    printer->Print(
      "      return YES;\n"
      "    default:\n"
      "      return NO;\n"
      "  }\n"
      "}\n");
  }
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
