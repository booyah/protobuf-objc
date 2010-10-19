// Protocol Buffers for Objective C
//
// Copyright 2010 Booyah Inc.
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

#include "PBTypes.h"

static PBObjCType kTypeToObjCTypeMap[PBType_Count] =
{
	PBObjCTypeDouble,		// PBTypeDouble
	PBObjCTypeFloat,		// PBTypeFloat
	PBObjCTypeInt64,		// PBTypeInt64
	PBObjCTypeUInt64,		// PBTypeUInt64
	PBObjCTypeInt32,		// PBTypeInt32
	PBObjCTypeUInt64,		// PBTypeFixed64
	PBObjCTypeUInt32,		// PBTypeFixed32
	PBObjCTypeBool,			// PBTypeBool
	PBObjCTypeString,		// PBTypeString
	PBObjCTypeMessage,		// PBTypeGroup
	PBObjCTypeMessage,		// PBTypeMessage
	PBObjCTypeData,			// PBTypeBytes
	PBObjCTypeUInt32,		// PBTypeUInt32
	PBObjCTypeEnum,			// PBTypeEnum
	PBObjCTypeInt32,		// PBTypeSFixed32
	PBObjCTypeInt64,		// PBTypeSFixed64
	PBObjCTypeInt32,		// PBTypeSInt32
	PBObjCTypeInt64,		// PBTypeSInt64
};

PBObjCType PBTypeToObjCType(PBType type)
{
	return kTypeToObjCTypeMap[type];
}

NSObject * PBDefaultValue(PBObjCType type)
{
	switch (type)
	{
		case PBObjCTypeInt32:
			return [NSNumber numberWithLong:0];

		case PBObjCTypeInt64:
			return [NSNumber numberWithLongLong:0];

		case PBObjCTypeUInt32:
			return [NSNumber numberWithUnsignedLong:0];

		case PBObjCTypeUInt64:
			return [NSNumber numberWithUnsignedLongLong:0];

		case PBObjCTypeDouble:
			return [NSNumber numberWithDouble:0];

		case PBObjCTypeFloat:
			return [NSNumber numberWithFloat:0.f];

		case PBObjCTypeBool:
			return [NSNumber numberWithChar:FALSE];

		case PBObjCTypeString:
			return @"";
	}

	return nil;
}

BOOL PBIsTypePackable(PBType type)
{
	return (type != PBTypeString &&
			type != PBTypeGroup &&
			type != PBTypeMessage &&
			type != PBTypeBytes);
}