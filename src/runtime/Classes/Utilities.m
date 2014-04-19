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

const NSInteger LITTLE_ENDIAN_32_SIZE = 4;
const NSInteger LITTLE_ENDIAN_64_SIZE = 8;


int64_t convertFloat64ToInt64(Float64 v) {
  union { Float64 f; int64_t i; } u;
  u.f = v;
  return u.i;
}


NSInteger convertFloat32ToInt32(Float32 v) {
  union { Float32 f; NSInteger i; } u;
  u.f = v;
  return u.i;
}


Float64 convertInt64ToFloat64(int64_t v) {
  union { Float64 f; int64_t i; } u;
  u.i = v;
  return u.f;
}


Float32 convertInt32ToFloat32(NSInteger v) {
  union { Float32 f; NSInteger i; } u;
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

NSUInteger convertInt32ToUInt32(NSInteger v) {
  union { NSInteger i; NSUInteger u; } u;
  u.i = v;
  return u.u;
}


int64_t convertUInt32ToInt32(NSUInteger v) {
  union { NSInteger i; NSUInteger u; } u;
  u.u = v;
  return u.i;
}


NSInteger logicalRightShift32(NSInteger value, NSInteger spaces) {
  return convertUInt32ToInt32((convertInt32ToUInt32(value) >> spaces));
}


int64_t logicalRightShift64(int64_t value, NSInteger spaces) {
  return convertUInt64ToInt64((convertInt64ToUInt64(value) >> spaces));
}


NSInteger decodeZigZag32(NSInteger n) {
	return logicalRightShift32(n, 1) ^ -(n & 1);
}


int64_t decodeZigZag64(int64_t n) {
	return logicalRightShift64(n, 1) ^ -(n & 1);
}


NSInteger encodeZigZag32(NSInteger n) {
	// Note:  the right-shift must be arithmetic
	return (n << 1) ^ (n >> 31);
}


int64_t encodeZigZag64(int64_t n) {
	// Note:  the right-shift must be arithmetic
	return (n << 1) ^ (n >> 63);
}


NSInteger computeDoubleSizeNoTag(Float64 value) {
	return LITTLE_ENDIAN_64_SIZE;
}


NSInteger computeFloatSizeNoTag(Float32 value) {
	return LITTLE_ENDIAN_32_SIZE;
}


NSInteger computeUInt64SizeNoTag(int64_t value) {
	return computeRawVarint64Size(value);
}


NSInteger computeInt64SizeNoTag(int64_t value) {
	return computeRawVarint64Size(value);
}


NSInteger computeInt32SizeNoTag(NSInteger value) {
	if (value >= 0) {
		return computeRawVarint32Size(value);
	} else {
		// Must sign-extend.
		return 10;
	}
}


NSInteger computeFixed64SizeNoTag(int64_t value) {
	return LITTLE_ENDIAN_64_SIZE;
}


NSInteger computeFixed32SizeNoTag(NSInteger value) {
	return LITTLE_ENDIAN_32_SIZE;
}


NSInteger computeBoolSizeNoTag(BOOL value) {
	return 1;
}


NSInteger computeStringSizeNoTag(const NSString* value) {
	const NSUInteger length = [value lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
	return computeRawVarint32Size(length) + length;
}


NSInteger computeGroupSizeNoTag(const id<PBMessage> value) {
	return [value serializedSize];
}


NSInteger computeUnknownGroupSizeNoTag(const PBUnknownFieldSet* value) {
	return value.serializedSize;
}


NSInteger computeMessageSizeNoTag(const id<PBMessage> value) {
	NSInteger size = [value serializedSize];
	return computeRawVarint32Size(size) + size;
}


NSInteger computeDataSizeNoTag(const NSData* value) {
	return computeRawVarint32Size(value.length) + value.length;
}


NSInteger computeUInt32SizeNoTag(NSInteger value) {
	return computeRawVarint32Size(value);
}


NSInteger computeEnumSizeNoTag(NSInteger value) {
	return computeRawVarint32Size(value);
}


NSInteger computeSFixed32SizeNoTag(NSInteger value) {
	return LITTLE_ENDIAN_32_SIZE;
}


NSInteger computeSFixed64SizeNoTag(int64_t value) {
	return LITTLE_ENDIAN_64_SIZE;
}


NSInteger computeSInt32SizeNoTag(NSInteger value) {
	return computeRawVarint32Size(encodeZigZag32(value));
}


NSInteger computeSInt64SizeNoTag(int64_t value) {
	return computeRawVarint64Size(encodeZigZag64(value));
}


NSInteger computeDoubleSize(NSInteger fieldNumber, Float64 value) {
	return computeTagSize(fieldNumber) + computeDoubleSizeNoTag(value);
}


NSInteger computeFloatSize(NSInteger fieldNumber, Float32 value) {
	return computeTagSize(fieldNumber) + computeFloatSizeNoTag(value);
}


NSInteger computeUInt64Size(NSInteger fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeUInt64SizeNoTag(value);
}


NSInteger computeInt64Size(NSInteger fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeInt64SizeNoTag(value);
}


NSInteger computeInt32Size(NSInteger fieldNumber, NSInteger value) {
	return computeTagSize(fieldNumber) + computeInt32SizeNoTag(value);
}


NSInteger computeFixed64Size(NSInteger fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeFixed64SizeNoTag(value);
}


NSInteger computeFixed32Size(NSInteger fieldNumber, NSInteger value) {
	return computeTagSize(fieldNumber) + computeFixed32SizeNoTag(value);
}


NSInteger computeBoolSize(NSInteger fieldNumber, BOOL value) {
	return computeTagSize(fieldNumber) + computeBoolSizeNoTag(value);
}


NSInteger computeStringSize(NSInteger fieldNumber, const NSString* value) {
	return computeTagSize(fieldNumber) + computeStringSizeNoTag(value);
}


NSInteger computeGroupSize(NSInteger fieldNumber, const id<PBMessage> value) {
	return computeTagSize(fieldNumber) * 2 + computeGroupSizeNoTag(value);
}


NSInteger computeUnknownGroupSize(NSInteger fieldNumber, const PBUnknownFieldSet* value) {
	return computeTagSize(fieldNumber) * 2 + computeUnknownGroupSizeNoTag(value);
}


NSInteger computeMessageSize(NSInteger fieldNumber, const id<PBMessage> value) {
	return computeTagSize(fieldNumber) + computeMessageSizeNoTag(value);
}


NSInteger computeDataSize(NSInteger fieldNumber, const NSData* value) {
	return computeTagSize(fieldNumber) + computeDataSizeNoTag(value);
}


NSInteger computeUInt32Size(NSInteger fieldNumber, NSInteger value) {
	return computeTagSize(fieldNumber) + computeUInt32SizeNoTag(value);
}


NSInteger computeEnumSize(NSInteger fieldNumber, NSInteger value) {
	return computeTagSize(fieldNumber) + computeEnumSizeNoTag(value);
}


NSInteger computeSFixed32Size(NSInteger fieldNumber, NSInteger value) {
	return computeTagSize(fieldNumber) + computeSFixed32SizeNoTag(value);
}


NSInteger computeSFixed64Size(NSInteger fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) + computeSFixed64SizeNoTag(value);
}


NSInteger computeSInt32Size(NSInteger fieldNumber, NSInteger value) {
	return computeTagSize(fieldNumber) + computeSInt32SizeNoTag(value);
}


NSInteger computeTagSize(NSInteger fieldNumber) {
	return computeRawVarint32Size(PBWireFormatMakeTag(fieldNumber, 0));
}


NSInteger computeSInt64Size(NSInteger fieldNumber, int64_t value) {
	return computeTagSize(fieldNumber) +
	computeRawVarint64Size(encodeZigZag64(value));
}


NSInteger computeRawVarint32Size(NSInteger value) {
	if ((value & (0xffffffff <<  7)) == 0) return 1;
	if ((value & (0xffffffff << 14)) == 0) return 2;
	if ((value & (0xffffffff << 21)) == 0) return 3;
	if ((value & (0xffffffff << 28)) == 0) return 4;
	return 5;
}


NSInteger computeRawVarint64Size(int64_t value) {
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


NSInteger computeMessageSetExtensionSize(NSInteger fieldNumber, const id<PBMessage> value) {
	return computeTagSize(PBWireFormatMessageSetItem) * 2 +
	computeUInt32Size(PBWireFormatMessageSetTypeId, fieldNumber) +
	computeMessageSize(PBWireFormatMessageSetMessage, value);
}


NSInteger computeRawMessageSetExtensionSize(NSInteger fieldNumber, const NSData* value) {
	return computeTagSize(PBWireFormatMessageSetItem) * 2 +
	computeUInt32Size(PBWireFormatMessageSetTypeId, fieldNumber) +
	computeDataSize(PBWireFormatMessageSetMessage, value);
}
