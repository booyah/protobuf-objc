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

#ifndef OBJC_EXTENSION_H
#define OBJC_EXTENSION_H

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
  class FieldDescriptor;       // descriptor.h
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace objectivec {

class ExtensionGenerator {
 public:
  explicit ExtensionGenerator(string classname, const FieldDescriptor* descriptor);
  ~ExtensionGenerator();

  void GenerateMembersHeader(io::Printer* printer);
  void GenerateMembersSource(io::Printer* printer);
  void GenerateFieldsSource(io::Printer* printer);
  void GenerateInitializationSource(io::Printer* printer);
  void GenerateRegistrationSource(io::Printer* printer);

 private:
  string classname_;
  const FieldDescriptor* descriptor_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ExtensionGenerator);
};
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif // OBJC_MESSAGE_H
