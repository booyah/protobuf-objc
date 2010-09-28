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

#include "objc_field.h"

#include <google/protobuf/stubs/common.h>

#include "objc_field.h"
#include "objc_helpers.h"
#include "objc_primitive_field.h"
#include "objc_enum_field.h"
#include "objc_message_field.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

  FieldGenerator::~FieldGenerator() {
  }


  FieldGeneratorMap::FieldGeneratorMap(const Descriptor* descriptor)
    : descriptor_(descriptor),
    field_generators_(new scoped_ptr<FieldGenerator>[descriptor->field_count()]),
    extension_generators_(new scoped_ptr<FieldGenerator>[descriptor->extension_count()]) {

      // Construct all the FieldGenerators.
      for (int i = 0; i < descriptor->field_count(); i++) {
        field_generators_[i].reset(MakeGenerator(descriptor->field(i)));
      }
      for (int i = 0; i < descriptor->extension_count(); i++) {
        extension_generators_[i].reset(MakeGenerator(descriptor->extension(i)));
      }
  }


  FieldGenerator* FieldGeneratorMap::MakeGenerator(const FieldDescriptor* field) {
    if (field->is_repeated()) {
      switch (GetObjectiveCType(field)) {
      case OBJECTIVECTYPE_MESSAGE:
        return new RepeatedMessageFieldGenerator(field);
      case OBJECTIVECTYPE_ENUM:
        return new RepeatedEnumFieldGenerator(field);
      default:
        return new RepeatedPrimitiveFieldGenerator(field);
      }
    } else {
      switch (GetObjectiveCType(field)) {
      case OBJECTIVECTYPE_MESSAGE:
        return new MessageFieldGenerator(field);
      case OBJECTIVECTYPE_ENUM:
        return new EnumFieldGenerator(field);
      default:
        return new PrimitiveFieldGenerator(field);
      }
    }
  }


  FieldGeneratorMap::~FieldGeneratorMap() {
  }


  const FieldGenerator& FieldGeneratorMap::get(
    const FieldDescriptor* field) const {
      GOOGLE_CHECK_EQ(field->containing_type(), descriptor_);
      return *field_generators_[field->index()];
  }


  const FieldGenerator& FieldGeneratorMap::get_extension(int index) const {
    return *extension_generators_[index];
  }
}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
