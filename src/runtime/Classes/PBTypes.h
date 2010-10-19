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

#include <objc/objc.h>

typedef enum _PBType
{
	PBTypeDouble,		// double, exactly eight bytes on the wire.
	PBTypeFloat,		// float, exactly four bytes on the wire.
	PBTypeInt64,		// int64, varint on the wire.
	PBTypeUInt64,		// uint64, varint on the wire.
	PBTypeInt32,		// int32, varint on the wire.
	PBTypeFixed64,		// uint64, exactly eight bytes on the wire.
	PBTypeFixed32,		// uint32, exactly four bytes on the wire.
	PBTypeBool,			// bool, varint on the wire.
	PBTypeString,		// UTF-8 text.
	PBTypeGroup,		// Tag-delimited message.  Deprecated.
	PBTypeMessage,		// Length-delimited message.
	PBTypeBytes,		// Arbitrary byte array.
	PBTypeUInt32,		// uint32, varint on the wire
	PBTypeEnum,			// Enum, varint on the wire
	PBTypeSFixed32,		// int32, exactly four bytes on the wire
	PBTypeSFixed64,		// int64, exactly eight bytes on the wire
	PBTypeSInt32,		// int32, ZigZag-encoded varint on the wire
	PBTypeSInt64,		// int64, ZigZag-encoded varint on the wire
	PBType_Count
} PBType;

typedef enum _PBObjCType
{
	PBObjCTypeInt32,	// PBTypeInt32, PBTypeSInt32, PBTypeSFixed32
	PBObjCTypeInt64,	// PBTypeInt64, PBTypeSInt64, PBTypeSFixed64
	PBObjCTypeUInt32,	// PBTypeUInt32, PBTypeFixed32
	PBObjCTypeUInt64,	// PBTypeUInt64, PBTypeFixed64
	PBObjCTypeDouble,	// PBTypeDouble
	PBObjCTypeFloat,	// PBTypeFloat
	PBObjCTypeBool,		// PBTypeBool
	PBObjCTypeEnum,		// PBTypeEnum
	PBObjCTypeString,	// PBTypeString
	PBObjCTypeData,		// PBTypeBytes
	PBObjCTypeMessage,	// PBTypeMessage, PBTypeGroup
} PBObjCType;

PBObjCType PBTypeToObjCType(PBType type);
NSObject * PBDefaultValue(PBObjCType type);
BOOL PBIsTypePackable(PBType type);