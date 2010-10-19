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
	PBTypeDouble	= 1,	// double, exactly eight bytes on the wire.
	PBTypeFloat		= 2,	// float, exactly four bytes on the wire.
	PBTypeInt64		= 3,	// int64, varint on the wire.
	PBTypeUInt64	= 4,	// uint64, varint on the wire.
	PBTypeInt32		= 5,	// int32, varint on the wire.
	PBTypeFixed64	= 6,	// uint64, exactly eight bytes on the wire.
	PBTypeFixed32	= 7,	// uint32, exactly four bytes on the wire.
	PBTypeBool		= 8,	// bool, varint on the wire.
	PBTypeString	= 9,	// UTF-8 text.
	PBTypeGroup		= 10,	// Tag-delimited message.  Deprecated.
	PBTypeMessage	= 11,	// Length-delimited message.
	PBTypeBytes		= 12,	// Arbitrary byte array.
	PBTypeUInt32	= 13,	// uint32, varint on the wire
	PBTypeEnum		= 14,	// Enum, varint on the wire
	PBTypeSFixed32	= 15,	// int32, exactly four bytes on the wire
	PBTypeSFixed64	= 16,	// int64, exactly eight bytes on the wire
	PBTypeSInt32	= 17,	// int32, ZigZag-encoded varint on the wire
	PBTypeSInt64	= 18,	// int64, ZigZag-encoded varint on the wire
	PBType_Count	= 18
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