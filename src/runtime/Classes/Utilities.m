// Protocol Buffers for Objective C
//
// Copyright 2010 Booyah Inc.
// Copyright 2008 Cyrus Najmabadi
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

#import "Utilities.h"

#import "UnknownFieldSet.h"
#import "WireFormat.h"

const int32_t LITTLE_ENDIAN_32_SIZE = 4;
const int32_t LITTLE_ENDIAN_64_SIZE = 8;


int64_t convertFloat64ToInt64(Float64 v) {
  union { Float64 f; int64_t i; } u;
  u.f = v;
  return u.i;
}


int32_t convertFloat32ToInt32(Float32 v) {
  union { Float32 f; int32_t i; } u;
  u.f = v;
  return u.i;
}


Float64 convertInt64ToFloat64(int64_t v) {
  union { Float64 f; int64_t i; } u;
  u.i = v;
  return u.f;
}


Float32 convertInt32ToFloat32(int32_t v) {
  union { Float32 f; int32_t i; } u;
  u.i = v;
  return u.f;
}


uint64_t convertInt64ToUInt64(int64_t v) {
  union { int64_t i; uint64_t u; } u;
  u.i = v;
  return u.u;
}


int64_t convertUInt64ToInt64(uint64_t v) {
  union { int64_t i; uint64_t u; } u;
  u.u = v;
  return u.i;
}

uint32_t convertInt32ToUInt32(int32_t v) {
  union { int32_t i; uint32_t u; } u;
  u.i = v;
  return u.u;
}


int64_t convertUInt32ToInt32(uint32_t v) {
  union { int32_t i; uint32_t u; } u;
  u.u = v;
  return u.i;
}


int32_t logicalRightShift32(int32_t value, int32_t spaces) {
  return convertUInt32ToInt32((convertInt32ToUInt32(value) >> spaces));
}


int64_t logicalRightShift64(int64_t value, int32_t spaces) {
  return convertUInt64ToInt64((convertInt64ToUInt64(value) >> spaces));
}


int32_t decodeZigZag32(int32_t n) {
	return logicalRightShift32(n, 1) ^ -(n & 1);
}


int64_t decodeZigZag64(int64_t n) {
	return logicalRightShift64(n, 1) ^ -(n & 1);
}


int32_t encodeZigZag32(int32_t n) {
	// Note:  the right-shift must be arithmetic
	return (n << 1) ^ (n >> 31);
}


int64_t encodeZigZag64(int64_t n) {
	// Note:  the right-shift must be arithmetic
	return (n << 1) ^ (n >> 63);
}


int32_t computeDoubleSizeNoTag(Float64 value) {
	return LITTLE_ENDIAN_64_SIZE;
}


int32_t computeFloatSizeNoTag(Float32 value) {
	return LITTLE_ENDIAN_32_SIZE;
}


int32_t computeUInt64SizeNoTag(int64_t value) {
	return computeRawVarint64Size(value);
}


int32_t computeInt64SizeNoTag(int64_t value) {
	return computeRawVarint64Size(value);
}


int32_t computeInt32SizeNoTag(int32_t value) {
	if (value >= 0) {
		return computeRawVarint32Size(value);
	} else {
		// Must sign-extend.
		return 10;
	}
}


int32_t computeFixed64SizeNoTag(int64_t value) {
	return LITTLE_ENDIAN_64_SIZE;
}


int32_t computeFixed32SizeNoTag(int32_t value) {
	return LITTLE_ENDIAN_32_SIZE;
}


int32_t computeBoolSizeNoTag(BOOL value) {
	return 1;
}


int32_t computeStringSizeNoTag(const NSString* value) {
	const NSUInteger length = [value lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
	return computeRawVarint32Size(length) + length;
}


int32_t computeGroupSizeNoTag(const id<PBMessage> value) {
	return [value serializedSize];
}


int32_t computeUnknownGroupSizeNoTag(const PBUnknownFieldSet* value) {
	return value.serializedSize;
}


int32_t computeMessageSizeNoTag(const id<PBMessage> value) {
	int32_t size = [value serializedSize];
	return computeRawVarint32Size(size) + size;
}


int32_t computeDataSizeNoTag(const NSData* value) {
	return computeRawVarint32Size(value.length) + value.length;
}


int32_t computeUInt32SizeNoTag(int32_t value) {
	return computeRawVarint32Size(value);
}


int32_t computeEnumSizeNoTag(int32_t value) {
	return computeRawVarint32Size(value);
}


int32_t computeSFixed32SizeNoTag(int32_t value) {
	return LITTLE_ENDIAN_32_SIZE;
}


int32_t computeSFixed64SizeNoTag(int64_t value) {
	return LITTLE_ENDIAN_64_SIZE;
}


int32_t computeSInt32SizeNoTag(int32_t value) {
	return computeRawVarint32Size(encodeZigZag32(value));
}


int32_t computeSInt64SizeNoTag(int64_t value) {
	return computeRawVarint64Size(encodeZigZag64(value));
}


int32_t computeDoubleSize(int32_t fieldNumber, Float64 value) {
	return computeTagSize(fieldNumber) + computeDoubleSizeNoTag(value);
}


int32_t computeFloatSize(int32_t fieldNumber, Float32 value) {
	return computeTagSize(fieldNumber) + computeFloatSizeNoTag(value);
}


int32_t computeUInt64Size(int32_t fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeUInt64SizeNoTag(value);
}


int32_t computeInt64Size(int32_t fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeInt64SizeNoTag(value);
}


int32_t computeInt32Size(int32_t fieldNumber, int32_t value) {
	return computeTagSize(fieldNumber) + computeInt32SizeNoTag(value);
}


int32_t computeFixed64Size(int32_t fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeFixed64SizeNoTag(value);
}


int32_t computeFixed32Size(int32_t fieldNumber, int32_t value) {
	return computeTagSize(fieldNumber) + computeFixed32SizeNoTag(value);
}


int32_t computeBoolSize(int32_t fieldNumber, BOOL value) {
	return computeTagSize(fieldNumber) + computeBoolSizeNoTag(value);
}


int32_t computeStringSize(int32_t fieldNumber, const NSString* value) {
	return computeTagSize(fieldNumber) + computeStringSizeNoTag(value);
}


int32_t computeGroupSize(int32_t fieldNumber, const id<PBMessage> value) {
	return computeTagSize(fieldNumber) * 2 + computeGroupSizeNoTag(value);
}


int32_t computeUnknownGroupSize(int32_t fieldNumber, const PBUnknownFieldSet* value) {
	return computeTagSize(fieldNumber) * 2 + computeUnknownGroupSizeNoTag(value);
}


int32_t computeMessageSize(int32_t fieldNumber, const id<PBMessage> value) {
	return computeTagSize(fieldNumber) + computeMessageSizeNoTag(value);
}


int32_t computeDataSize(int32_t fieldNumber, const NSData* value) {
	return computeTagSize(fieldNumber) + computeDataSizeNoTag(value);
}


int32_t computeUInt32Size(int32_t fieldNumber, int32_t value) {
	return computeTagSize(fieldNumber) + computeUInt32SizeNoTag(value);
}


int32_t computeEnumSize(int32_t fieldNumber, int32_t value) {
	return computeTagSize(fieldNumber) + computeEnumSizeNoTag(value);
}


int32_t computeSFixed32Size(int32_t fieldNumber, int32_t value) {
	return computeTagSize(fieldNumber) + computeSFixed32SizeNoTag(value);
}


int32_t computeSFixed64Size(int32_t fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeSFixed64SizeNoTag(value);
}


int32_t computeSInt32Size(int32_t fieldNumber, int32_t value) {
	return computeTagSize(fieldNumber) + computeSInt32SizeNoTag(value);
}


int32_t computeTagSize(int32_t fieldNumber) {
	return computeRawVarint32Size(PBWireFormatMakeTag(fieldNumber, 0));
}


int32_t computeSInt64Size(int32_t fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) +
	computeRawVarint64Size(encodeZigZag64(value));
}


int32_t computeRawVarint32Size(int32_t value) {
	if ((value & (0xffffffff <<  7)) == 0) return 1;
	if ((value & (0xffffffff << 14)) == 0) return 2;
	if ((value & (0xffffffff << 21)) == 0) return 3;
	if ((value & (0xffffffff << 28)) == 0) return 4;
	return 5;
}


int32_t computeRawVarint64Size(int64_t value) {
	if ((value & (0xffffffffffffffffL <<  7)) == 0) return 1;
	if ((value & (0xffffffffffffffffL << 14)) == 0) return 2;
	if ((value & (0xffffffffffffffffL << 21)) == 0) return 3;
	if ((value & (0xffffffffffffffffL << 28)) == 0) return 4;
	if ((value & (0xffffffffffffffffL << 35)) == 0) return 5;
	if ((value & (0xffffffffffffffffL << 42)) == 0) return 6;
	if ((value & (0xffffffffffffffffL << 49)) == 0) return 7;
	if ((value & (0xffffffffffffffffL << 56)) == 0) return 8;
	if ((value & (0xffffffffffffffffL << 63)) == 0) return 9;
	return 10;
}


int32_t computeMessageSetExtensionSize(int32_t fieldNumber, const id<PBMessage> value) {
	return computeTagSize(PBWireFormatMessageSetItem) * 2 +
	computeUInt32Size(PBWireFormatMessageSetTypeId, fieldNumber) +
	computeMessageSize(PBWireFormatMessageSetMessage, value);
}


int32_t computeRawMessageSetExtensionSize(int32_t fieldNumber, const NSData* value) {
	return computeTagSize(PBWireFormatMessageSetItem) * 2 +
	computeUInt32Size(PBWireFormatMessageSetTypeId, fieldNumber) +
	computeDataSize(PBWireFormatMessageSetMessage, value);
}
