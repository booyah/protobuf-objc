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

#import "Message.h"

long long convertFloat64ToInt64(Float64 f);
long convertFloat32ToInt32(Float32 f);
Float64 convertInt64ToFloat64(long long f);
Float32 convertInt32ToFloat32(long f);

unsigned long long convertInt64ToUInt64(long long i);
long long  convertUInt64ToInt64(unsigned long long u);
unsigned long convertInt32ToUInt32(long i);
long  convertUInt32ToInt32(unsigned long u);

long logicalRightShift32(long value, long spaces);
long long logicalRightShift64(long long value, long spaces);


/**
 * Decode a ZigZag-encoded 32-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n An unsigned 32-bit integer, stored in a signed int.
 * @return A signed 32-bit integer.
 */
long decodeZigZag32(long n);

/**
 * Decode a ZigZag-encoded 64-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n An unsigned 64-bit integer, stored in a signed int.
 * @return A signed 64-bit integer.
 */
long long decodeZigZag64(long long n);


/**
 * Encode a ZigZag-encoded 32-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n A signed 32-bit integer.
 * @return An unsigned 32-bit integer, stored in a signed int.
 */
long encodeZigZag32(long n);

/**
 * Encode a ZigZag-encoded 64-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n A signed 64-bit integer.
 * @return An unsigned 64-bit integer, stored in a signed int.
 */
long long encodeZigZag64(long long n);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code double} field, including tag.
 */
long computeDoubleSize(long fieldNumber, Float64 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code float} field, including tag.
 */
long computeFloatSize(long fieldNumber, Float32 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint64} field, including tag.
 */
long computeUInt64Size(long fieldNumber, long long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int64} field, including tag.
 */
long computeInt64Size(long fieldNumber, long long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int32} field, including tag.
 */
long computeInt32Size(long fieldNumber, long value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed64} field, including tag.
 */
long computeFixed64Size(long fieldNumber, long long value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed32} field, including tag.
 */
long computeFixed32Size(long fieldNumber, long value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bool} field, including tag.
 */
long computeBoolSize(long fieldNumber, BOOL value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code string} field, including tag.
 */
long computeStringSize(long fieldNumber, const NSString* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field, including tag.
 */
long computeGroupSize(long fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field represented by an {@code PBUnknownFieldSet}, including
 * tag.
 */
long computeUnknownGroupSize(long fieldNumber, const PBUnknownFieldSet* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * embedded message field, including tag.
 */
long computeMessageSize(long fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bytes} field, including tag.
 */
long computeDataSize(long fieldNumber, const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint32} field, including tag.
 */
long computeUInt32Size(long fieldNumber, long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed32} field, including tag.
 */
long computeSFixed32Size(long fieldNumber, long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed64} field, including tag.
 */
long computeSFixed64Size(long fieldNumber, long long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint32} field, including tag.
 */
long computeSInt32Size(long fieldNumber, long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint64} field, including tag.
 */
long computeSInt64Size(long fieldNumber, long long value);

/** Compute the number of bytes that would be needed to encode a tag. */
long computeTagSize(long fieldNumber);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code double} field, including tag.
 */
long computeDoubleSizeNoTag(Float64 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code float} field, including tag.
 */
long computeFloatSizeNoTag(Float32 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint64} field, including tag.
 */
long computeUInt64SizeNoTag(long long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int64} field, including tag.
 */
long computeInt64SizeNoTag(long long value);
/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int32} field, including tag.
 */
long computeInt32SizeNoTag(long value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed64} field, including tag.
 */
long computeFixed64SizeNoTag(long long value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed32} field, including tag.
 */
long computeFixed32SizeNoTag(long value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bool} field, including tag.
 */
long computeBoolSizeNoTag(BOOL value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code string} field, including tag.
 */
long computeStringSizeNoTag(const NSString* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field, including tag.
 */
long computeGroupSizeNoTag(const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field represented by an {@code PBUnknownFieldSet}, including
 * tag.
 */
long computeUnknownGroupSizeNoTag(const PBUnknownFieldSet* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * embedded message field, including tag.
 */
long computeMessageSizeNoTag(const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bytes} field, including tag.
 */
long computeDataSizeNoTag(const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint32} field, including tag.
 */
long computeUInt32SizeNoTag(long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * enum field, including tag.  Caller is responsible for converting the
 * enum value to its numeric value.
 */
long computeEnumSizeNoTag(long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed32} field, including tag.
 */
long computeSFixed32SizeNoTag(long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed64} field, including tag.
 */
long computeSFixed64SizeNoTag(long long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint32} field, including tag.
 */
long computeSInt32SizeNoTag(long value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint64} field, including tag.
 */
long computeSInt64SizeNoTag(long long value);

/**
 * Compute the number of bytes that would be needed to encode a varint.
 * {@code value} is treated as unsigned, so it won't be sign-extended if
 * negative.
 */
long computeRawVarint32Size(long value);

/** Compute the number of bytes that would be needed to encode a varint. */
long computeRawVarint64Size(long long value);

/**
 * Compute the number of bytes that would be needed to encode a
 * MessageSet extension to the stream.  For historical reasons,
 * the wire format differs from normal fields.
 */
long computeMessageSetExtensionSize(long fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode an
 * unparsed MessageSet extension field to the stream.  For
 * historical reasons, the wire format differs from normal fields.
 */
long computeRawMessageSetExtensionSize(long fieldNumber, const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * enum field, including tag.  Caller is responsible for converting the
 * enum value to its numeric value.
 */
long computeEnumSize(long fieldNumber, long value);
