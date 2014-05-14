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

const long LITTLE_ENDIAN_32_SIZE = 4;
const long LITTLE_ENDIAN_64_SIZE = 8;


long long convertFloat64ToInt64(Float64 v) {
  union { Float64 f; long long i; } u;
  u.f = v;
  return u.i;
}


long convertFloat32ToInt32(Float32 v) {
  union { Float32 f; long i; } u;
  u.f = v;
  return u.i;
}


Float64 convertInt64ToFloat64(long long v) {
  union { Float64 f; long long i; } u;
  u.i = v;
  return u.f;
}


Float32 convertInt32ToFloat32(long v) {
  union { Float32 f; long i; } u;
  u.i = v;
  return u.f;
}


unsigned long long convertInt64ToUInt64(long long v) {
  union { long long i; unsigned long long u; } u;
  u.i = v;
  return u.u;
}


long long convertUInt64ToInt64(unsigned long long v) {
  union { long long i; unsigned long long u; } u;
  u.u = v;
  return u.i;
}

unsigned long convertInt32ToUInt32(long v) {
  union { long i; unsigned long u; } u;
  u.i = v;
  return u.u;
}


long convertUInt32ToInt32(unsigned long v) {
  union { long i; unsigned long u; } u;
  u.u = v;
  return u.i;
}


long logicalRightShift32(long value, long spaces) {
  return convertUInt32ToInt32((convertInt32ToUInt32(value) >> spaces));
}


long long logicalRightShift64(long long value, long spaces) {
  return convertUInt64ToInt64((convertInt64ToUInt64(value) >> spaces));
}


long decodeZigZag32(long n) {
	return logicalRightShift32(n, 1) ^ -(n & 1);
}


long long decodeZigZag64(long long n) {
	return logicalRightShift64(n, 1) ^ -(n & 1);
}


long encodeZigZag32(long n) {
	// Note:  the right-shift must be arithmetic
	return (n << 1) ^ (n >> 31);
}


long long encodeZigZag64(long long n) {
	// Note:  the right-shift must be arithmetic
	return (n << 1) ^ (n >> 63);
}


long computeDoubleSizeNoTag(Float64 value) {
	return LITTLE_ENDIAN_64_SIZE;
}


long computeFloatSizeNoTag(Float32 value) {
	return LITTLE_ENDIAN_32_SIZE;
}


long computeUInt64SizeNoTag(long long value) {
	return computeRawVarint64Size(value);
}


long computeInt64SizeNoTag(long long value) {
	return computeRawVarint64Size(value);
}


long computeInt32SizeNoTag(long value) {
	if (value >= 0) {
		return computeRawVarint32Size(value);
	} else {
		// Must sign-extend.
		return 10;
	}
}


long computeFixed64SizeNoTag(long long value) {
	return LITTLE_ENDIAN_64_SIZE;
}


long computeFixed32SizeNoTag(long value) {
	return LITTLE_ENDIAN_32_SIZE;
}


long computeBoolSizeNoTag(BOOL value) {
	return 1;
}


long computeStringSizeNoTag(const NSString* value) {
	const unsigned long length = [value lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
	return computeRawVarint32Size(length) + length;
}


long computeGroupSizeNoTag(const id<PBMessage> value) {
	return [value serializedSize];
}


long computeUnknownGroupSizeNoTag(const PBUnknownFieldSet* value) {
	return value.serializedSize;
}


long computeMessageSizeNoTag(const id<PBMessage> value) {
	long size = [value serializedSize];
	return computeRawVarint32Size(size) + size;
}


long computeDataSizeNoTag(const NSData* value) {
	return computeRawVarint32Size(value.length) + value.length;
}


long computeUInt32SizeNoTag(long value) {
	return computeRawVarint32Size(value);
}


long computeEnumSizeNoTag(long value) {
	return computeRawVarint32Size(value);
}


long computeSFixed32SizeNoTag(long value) {
	return LITTLE_ENDIAN_32_SIZE;
}


long computeSFixed64SizeNoTag(long long value) {
	return LITTLE_ENDIAN_64_SIZE;
}


long computeSInt32SizeNoTag(long value) {
	return computeRawVarint32Size(encodeZigZag32(value));
}


long computeSInt64SizeNoTag(long long value) {
	return computeRawVarint64Size(encodeZigZag64(value));
}


long computeDoubleSize(long fieldNumber, Float64 value) {
	return computeTagSize(fieldNumber) + computeDoubleSizeNoTag(value);
}


long computeFloatSize(long fieldNumber, Float32 value) {
	return computeTagSize(fieldNumber) + computeFloatSizeNoTag(value);
}


long computeUInt64Size(long fieldNumber, long long value) {
	return computeTagSize(fieldNumber) + computeUInt64SizeNoTag(value);
}


long computeInt64Size(long fieldNumber, long long value) {
	return computeTagSize(fieldNumber) + computeInt64SizeNoTag(value);
}


long computeInt32Size(long fieldNumber, long value) {
	return computeTagSize(fieldNumber) + computeInt32SizeNoTag(value);
}


long computeFixed64Size(long fieldNumber, long long value) {
	return computeTagSize(fieldNumber) + computeFixed64SizeNoTag(value);
}


long computeFixed32Size(long fieldNumber, long value) {
	return computeTagSize(fieldNumber) + computeFixed32SizeNoTag(value);
}


long computeBoolSize(long fieldNumber, BOOL value) {
	return computeTagSize(fieldNumber) + computeBoolSizeNoTag(value);
}


long computeStringSize(long fieldNumber, const NSString* value) {
	return computeTagSize(fieldNumber) + computeStringSizeNoTag(value);
}


long computeGroupSize(long fieldNumber, const id<PBMessage> value) {
	return computeTagSize(fieldNumber) * 2 + computeGroupSizeNoTag(value);
}


long computeUnknownGroupSize(long fieldNumber, const PBUnknownFieldSet* value) {
	return computeTagSize(fieldNumber) * 2 + computeUnknownGroupSizeNoTag(value);
}


long computeMessageSize(long fieldNumber, const id<PBMessage> value) {
	return computeTagSize(fieldNumber) + computeMessageSizeNoTag(value);
}


long computeDataSize(long fieldNumber, const NSData* value) {
	return computeTagSize(fieldNumber) + computeDataSizeNoTag(value);
}


long computeUInt32Size(long fieldNumber, long value) {
	return computeTagSize(fieldNumber) + computeUInt32SizeNoTag(value);
}


long computeEnumSize(long fieldNumber, long value) {
	return computeTagSize(fieldNumber) + computeEnumSizeNoTag(value);
}


long computeSFixed32Size(long fieldNumber, long value) {
	return computeTagSize(fieldNumber) + computeSFixed32SizeNoTag(value);
}


long computeSFixed64Size(long fieldNumber, long long value) {
	return computeTagSize(fieldNumber) + computeSFixed64SizeNoTag(value);
}


long computeSInt32Size(long fieldNumber, long value) {
	return computeTagSize(fieldNumber) + computeSInt32SizeNoTag(value);
}


long computeTagSize(long fieldNumber) {
	return computeRawVarint32Size(PBWireFormatMakeTag(fieldNumber, 0));
}


long computeSInt64Size(long fieldNumber, long long value) {
	return computeTagSize(fieldNumber) +
	computeRawVarint64Size(encodeZigZag64(value));
}


long computeRawVarint32Size(long value) {
	if ((value & (0xffffffff <<  7)) == 0) return 1;
	if ((value & (0xffffffff << 14)) == 0) return 2;
	if ((value & (0xffffffff << 21)) == 0) return 3;
	if ((value & (0xffffffff << 28)) == 0) return 4;
	return 5;
}


long computeRawVarint64Size(long long value) {
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


long computeMessageSetExtensionSize(long fieldNumber, const id<PBMessage> value) {
	return computeTagSize(PBWireFormatMessageSetItem) * 2 +
	computeUInt32Size(PBWireFormatMessageSetTypeId, fieldNumber) +
	computeMessageSize(PBWireFormatMessageSetMessage, value);
}


long computeRawMessageSetExtensionSize(long fieldNumber, const NSData* value) {
	return computeTagSize(PBWireFormatMessageSetItem) * 2 +
	computeUInt32Size(PBWireFormatMessageSetTypeId, fieldNumber) +
	computeDataSize(PBWireFormatMessageSetMessage, value);
}
