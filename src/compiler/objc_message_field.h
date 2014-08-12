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

#ifndef OBJC_MESSAGE_FIELD_H
#define OBJC_MESSAGE_FIELD_H

#include <map>
#include <string>

#include "objc_field.h"

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

class MessageFieldGenerator : public FieldGenerator {
 public:
  explicit MessageFieldGenerator(const FieldDescriptor* descriptor);
  ~MessageFieldGenerator();

  void GenerateHasFieldHeader(io::Printer* printer) const;
  void GenerateFieldHeader(io::Printer* printer) const;
  void GenerateHasPropertyHeader(io::Printer* printer) const;
  void GeneratePropertyHeader(io::Printer* printer) const;
  void GenerateMembersHeader(io::Printer* printer) const;
  void GenerateBuilderMembersHeader(io::Printer* printer) const;
  void GenerateMergingCodeHeader(io::Printer* printer) const;
  void GenerateBuildingCodeHeader(io::Printer* printer) const;
  void GenerateParsingCodeHeader(io::Printer* printer) const;
  void GenerateSerializationCodeHeader(io::Printer* printer) const;
  void GenerateSerializedSizeCodeHeader(io::Printer* printer) const;

  void GenerateExtensionSource(io::Printer* printer) const;
  void GenerateSynthesizeSource(io::Printer* printer) const;
  void GenerateInitializationSource(io::Printer* printer) const;
  void GenerateMembersSource(io::Printer* printer) const;
  void GenerateBuilderMembersSource(io::Printer* printer) const;
  void GenerateMergingCodeSource(io::Printer* printer) const;
  void GenerateBuildingCodeSource(io::Printer* printer) const;
  void GenerateParsingCodeSource(io::Printer* printer) const;
  void GenerateSerializationCodeSource(io::Printer* printer) const;
  void GenerateSerializedSizeCodeSource(io::Printer* printer) const;
  void GenerateDescriptionCodeSource(io::Printer* printer) const;
  void GenerateIsEqualCodeSource(io::Printer* printer) const;
  void GenerateHashCodeSource(io::Printer* printer) const;

  string GetBoxedType() const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageFieldGenerator);
};

class RepeatedMessageFieldGenerator : public FieldGenerator {
 public:
  explicit RepeatedMessageFieldGenerator(const FieldDescriptor* descriptor);
  ~RepeatedMessageFieldGenerator();

  void GenerateHasFieldHeader(io::Printer* printer) const;
  void GenerateFieldHeader(io::Printer* printer) const;
  void GenerateHasPropertyHeader(io::Printer* printer) const;
  void GeneratePropertyHeader(io::Printer* printer) const;
  void GenerateMembersHeader(io::Printer* printer) const;
  void GenerateBuilderMembersHeader(io::Printer* printer) const;
  void GenerateMergingCodeHeader(io::Printer* printer) const;
  void GenerateBuildingCodeHeader(io::Printer* printer) const;
  void GenerateParsingCodeHeader(io::Printer* printer) const;
  void GenerateSerializationCodeHeader(io::Printer* printer) const;
  void GenerateSerializedSizeCodeHeader(io::Printer* printer) const;

  void GenerateExtensionSource(io::Printer* printer) const;
  void GenerateSynthesizeSource(io::Printer* printer) const;
  void GenerateInitializationSource(io::Printer* printer) const;
  void GenerateMembersSource(io::Printer* printer) const;
  void GenerateBuilderMembersSource(io::Printer* printer) const;
  void GenerateMergingCodeSource(io::Printer* printer) const;
  void GenerateBuildingCodeSource(io::Printer* printer) const;
  void GenerateParsingCodeSource(io::Printer* printer) const;
  void GenerateSerializationCodeSource(io::Printer* printer) const;
  void GenerateSerializedSizeCodeSource(io::Printer* printer) const;
  void GenerateDescriptionCodeSource(io::Printer* printer) const;
  void GenerateIsEqualCodeSource(io::Printer* printer) const;
  void GenerateHashCodeSource(io::Printer* printer) const;

  string GetBoxedType() const;

 private:
  const FieldDescriptor* descriptor_;
  map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedMessageFieldGenerator);
};
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif // OBJC_MESSAGE_FIELD_H
