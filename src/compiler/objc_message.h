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

#ifndef OBJC_MESSAGE_H
#define OBJC_MESSAGE_H

#include <string>
#include <set>
#include <google/protobuf/stubs/common.h>

#include "objc_field.h"

namespace google {
namespace protobuf {
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace objectivec {

class MessageGenerator {
 public:
  explicit MessageGenerator(const Descriptor* descriptor);
  ~MessageGenerator();

  void GenerateStaticVariablesHeader(io::Printer* printer);
  void GenerateStaticVariablesInitialization(io::Printer* printer);
  void GenerateStaticVariablesSource(io::Printer* printer);
  void GenerateEnumHeader(io::Printer* printer);
  void GenerateMessageHeader(io::Printer* printer);
  void GenerateSource(io::Printer* printer);
  void GenerateExtensionRegistrationSource(io::Printer* printer);
  void DetermineDependencies(set<string>* dependencies);

 private:
  void GenerateMessageSerializationMethodsHeader(io::Printer* printer);
  void GenerateParseFromMethodsHeader(io::Printer* printer);
  void GenerateSerializeOneFieldHeader(io::Printer* printer,
                                 const FieldDescriptor* field);
  void GenerateSerializeOneExtensionRangeHeader(
      io::Printer* printer, const Descriptor::ExtensionRange* range);

  void GenerateBuilderHeader(io::Printer* printer);
  void GenerateCommonBuilderMethodsHeader(io::Printer* printer);
  void GenerateBuilderParsingMethodsHeader(io::Printer* printer);
  void GenerateIsInitializedHeader(io::Printer* printer);


  void GenerateMessageSerializationMethodsSource(io::Printer* printer);
  void GenerateParseFromMethodsSource(io::Printer* printer);
  void GenerateSerializeOneFieldSource(io::Printer* printer,
                                 const FieldDescriptor* field);
  void GenerateSerializeOneExtensionRangeSource(
      io::Printer* printer, const Descriptor::ExtensionRange* range);

  void GenerateMessageDescriptionSource(io::Printer* printer);
  void GenerateDescriptionOneFieldSource(io::Printer* printer,
                                 const FieldDescriptor* field);
  void GenerateDescriptionOneExtensionRangeSource(
      io::Printer* printer, const Descriptor::ExtensionRange* range);

  void GenerateMessageIsEqualSource(io::Printer* printer);
  void GenerateIsEqualOneFieldSource(io::Printer* printer,
                                 const FieldDescriptor* field);
  void GenerateIsEqualOneExtensionRangeSource(
      io::Printer* printer, const Descriptor::ExtensionRange* range);

  void GenerateMessageHashSource(io::Printer* printer);
  void GenerateHashOneFieldSource(io::Printer* printer,
                                 const FieldDescriptor* field);
  void GenerateHashOneExtensionRangeSource(
      io::Printer* printer, const Descriptor::ExtensionRange* range);

  void GenerateBuilderSource(io::Printer* printer);
  void GenerateCommonBuilderMethodsSource(io::Printer* printer);
  void GenerateBuilderParsingMethodsSource(io::Printer* printer);
  void GenerateIsInitializedSource(io::Printer* printer);

  const Descriptor* descriptor_;
  FieldGeneratorMap field_generators_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageGenerator);
};
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif // OBJC_MESSAGE_H
