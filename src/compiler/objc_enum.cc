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
#include <set>

#include <google/protobuf/io/printer.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/strutil.h>

#include "objc_helpers.h"

namespace google { namespace protobuf { namespace compiler { namespace objectivec {

EnumGenerator::EnumGenerator(const EnumDescriptor *pDescriptor)
    : mpDescriptor(pDescriptor)
    , mClassname(ClassName(pDescriptor))
{
}

EnumGenerator::~EnumGenerator()
{
}

void EnumGenerator::GenerateDefinition(io::Printer *pPrinter)
{
    map<string, string> vars;
    vars["classname"] = mClassname;

    pPrinter->Print(vars, "typedef enum _$classname${\n");
    pPrinter->Indent();

    for (size_t i = 0; i < mpDescriptor->value_count(); ++i)
    {
        const EnumValueDescriptor *pValue = mpDescriptor->value(i);
        pPrinter->Print("$name$ = $value$,\n",
                        "name", EnumValueName(pValue),
                        "value", SimpleItoa(pValue->number()));
    }

    pPrinter->Outdent();
    pPrinter->Print(vars,
        "} $classname$;\n"
        "\n"
        "BOOL IsValid$classname$Value(int value);\n"
        "\n");
}

void EnumGenerator::GenerateValidationFunction(io::Printer *pPrinter)
{
    pPrinter->Print(
        "BOOL IsValid$classname$Value(int value) {\n"
        "  switch (value) {\n",
        "classname", mClassname);

    // Collapse all of the enums values into a single set.  It's possible
    // for multiple values to have the same number, and we can't have
    // duplicate case statements.
    set<int> numbers;
    for (size_t i = 0; i < mpDescriptor->value_count(); ++i)
    {
        const EnumValueDescriptor *pValue = mpDescriptor->value(i);
        numbers.insert(pValue->number());
    }

    for (set<int>::iterator it(numbers.begin()); it != numbers.end(); ++it)
    {
        pPrinter->Print("    case $name$:\n", "name", SimpleItoa(*it));
    }

    pPrinter->Print(
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
