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

#ifndef OBJC_HELPERS_H
#define OBJC_HELPERS_H

#include <string>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

// Converts the field's name to camel-case, e.g. "foo_bar_baz" becomes
// "fooBarBaz" or "FooBarBaz", respectively.
string UnderscoresToCamelCase(const FieldDescriptor* field);
string UnderscoresToCapitalizedCamelCase(const FieldDescriptor* field);
string UnderscoresToCapitalizedCamelCase(const string& name);

// Similar, but for method names.  (Typically, this merely has the effect
// of lower-casing the first letter of the name.)
string UnderscoresToCamelCase(const MethodDescriptor* method);

// Apply CamelCase-formatting to the given filename string.  Existing
// capitalization is not modified, but non-alphanumeric characters are
// removed and the following legal character is capitalized.
string FilenameToCamelCase(const string& filename);

// Strips ".proto" or ".protodevel" from the end of a filename.
string StripProto(const string& filename);

// Returns true if the name requires a ns_returns_not_retained attribute applied
// to it.
bool IsRetainedName(const string& name);

bool IsBootstrapFile(const FileDescriptor* file);

// Gets the name of the file we're going to generate (sans the .pb.h
// extension).  This does not include the path to that file.
string FileName(const FileDescriptor* file);

// Gets the path of the file we're going to generate (sans the .pb.h
// extension).  The path will be dependent on the objectivec package
// declared in the proto package.
string FilePath(const FileDescriptor* file);

// Gets the name of the root class we'll generate in the file.  This class
// is not meant for external consumption, but instead contains helpers that
// the rest of the the classes need
string FileClassName(const FileDescriptor* file);

// These return the fully-qualified class name corresponding to the given
// descriptor.
string ClassName(const Descriptor* descriptor);
string ClassName(const EnumDescriptor* descriptor);
string ClassName(const ServiceDescriptor* descriptor);

string EnumValueName(const EnumValueDescriptor* descriptor);

string SafeName(const string& name);

enum ObjectiveCType {
  OBJECTIVECTYPE_INT,
  OBJECTIVECTYPE_LONG,
  OBJECTIVECTYPE_FLOAT,
  OBJECTIVECTYPE_DOUBLE,
  OBJECTIVECTYPE_BOOLEAN,
  OBJECTIVECTYPE_STRING,
  OBJECTIVECTYPE_DATA,
  OBJECTIVECTYPE_ENUM,
  OBJECTIVECTYPE_MESSAGE
};

ObjectiveCType GetObjectiveCType(FieldDescriptor::Type field_type);

inline ObjectiveCType GetObjectiveCType(const FieldDescriptor* field) {
  return GetObjectiveCType(field->type());
}

// Get the fully-qualified class name for a boxed primitive type, e.g.
// "NSNumber" for OBJECTIVECTYPE_INT.  Returns NULL for enum and message
// types.
const char* BoxedPrimitiveTypeName(ObjectiveCType type);

bool IsPrimitiveType(ObjectiveCType type);
bool IsReferenceType(ObjectiveCType type);

bool ReturnsPrimitiveType(const FieldDescriptor* field);
bool ReturnsReferenceType(const FieldDescriptor* field);

string DefaultValue(const FieldDescriptor* field);
string BoxValue(const FieldDescriptor* field, const string& value);

const char* GetArrayValueType(const FieldDescriptor* field);

// Escape C++ trigraphs by escaping question marks to \?
string EscapeTrigraphs(const string& to_escape);

// Do message classes in this file keep track of unknown fields?
inline bool HasUnknownFields(const FileDescriptor *file) {
  return file->options().optimize_for() != FileOptions::LITE_RUNTIME;
}

// Does this file have generated parsing, serialization, and other
// standard methods for which reflection-based fallback implementations exist?
inline bool HasGeneratedMethods(const FileDescriptor *file) {
  return file->options().optimize_for() != FileOptions::CODE_SIZE;
}

// Do message classes in this file have descriptor and refelction methods?
inline bool HasDescriptorMethods(const FileDescriptor *file) {
  return file->options().optimize_for() != FileOptions::LITE_RUNTIME;
}

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif // OBJC_HELPERS_H
