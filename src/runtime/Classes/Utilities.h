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

int64_t convertFloat64ToInt64(Float64 f);
int32_t convertFloat32ToInt32(Float32 f);
Float64 convertInt64ToFloat64(int64_t f);
Float32 convertInt32ToFloat32(int32_t f);

uint64_t convertInt64ToUInt64(int64_t i);
int64_t  convertUInt64ToInt64(uint64_t u);
uint32_t convertInt32ToUInt32(int32_t i);
int64_t  convertUInt32ToInt32(uint32_t u);

int32_t logicalRightShift32(int32_t value, int32_t spaces);
int64_t logicalRightShift64(int64_t value, int32_t spaces);


/**
 * Decode a ZigZag-encoded 32-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n An unsigned 32-bit integer, stored in a signed int.
 * @return A signed 32-bit integer.
 */
int32_t decodeZigZag32(int32_t n);

/**
 * Decode a ZigZag-encoded 64-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n An unsigned 64-bit integer, stored in a signed int.
 * @return A signed 64-bit integer.
 */
int64_t decodeZigZag64(int64_t n);


/**
 * Encode a ZigZag-encoded 32-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n A signed 32-bit integer.
 * @return An unsigned 32-bit integer, stored in a signed int.
 */
int32_t encodeZigZag32(int32_t n);

/**
 * Encode a ZigZag-encoded 64-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n A signed 64-bit integer.
 * @return An unsigned 64-bit integer, stored in a signed int.
 */
int64_t encodeZigZag64(int64_t n);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code double} field, including tag.
 */
int32_t computeDoubleSize(int32_t fieldNumber, Float64 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code float} field, including tag.
 */
int32_t computeFloatSize(int32_t fieldNumber, Float32 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint64} field, including tag.
 */
int32_t computeUInt64Size(int32_t fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int64} field, including tag.
 */
int32_t computeInt64Size(int32_t fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int32} field, including tag.
 */
int32_t computeInt32Size(int32_t fieldNumber, int32_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed64} field, including tag.
 */
int32_t computeFixed64Size(int32_t fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed32} field, including tag.
 */
int32_t computeFixed32Size(int32_t fieldNumber, int32_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bool} field, including tag.
 */
int32_t computeBoolSize(int32_t fieldNumber, BOOL value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code string} field, including tag.
 */
int32_t computeStringSize(int32_t fieldNumber, const NSString* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field, including tag.
 */
int32_t computeGroupSize(int32_t fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field represented by an {@code PBUnknownFieldSet}, including
 * tag.
 */
int32_t computeUnknownGroupSize(int32_t fieldNumber, const PBUnknownFieldSet* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * embedded message field, including tag.
 */
int32_t computeMessageSize(int32_t fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bytes} field, including tag.
 */
int32_t computeDataSize(int32_t fieldNumber, const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint32} field, including tag.
 */
int32_t computeUInt32Size(int32_t fieldNumber, int32_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed32} field, including tag.
 */
int32_t computeSFixed32Size(int32_t fieldNumber, int32_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed64} field, including tag.
 */
int32_t computeSFixed64Size(int32_t fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint32} field, including tag.
 */
int32_t computeSInt32Size(int32_t fieldNumber, int32_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint64} field, including tag.
 */
int32_t computeSInt64Size(int32_t fieldNumber, int64_t value);

/** Compute the number of bytes that would be needed to encode a tag. */
int32_t computeTagSize(int32_t fieldNumber);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code double} field, including tag.
 */
int32_t computeDoubleSizeNoTag(Float64 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code float} field, including tag.
 */
int32_t computeFloatSizeNoTag(Float32 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint64} field, including tag.
 */
int32_t computeUInt64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int64} field, including tag.
 */
int32_t computeInt64SizeNoTag(int64_t value);
/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int32} field, including tag.
 */
int32_t computeInt32SizeNoTag(int32_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed64} field, including tag.
 */
int32_t computeFixed64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed32} field, including tag.
 */
int32_t computeFixed32SizeNoTag(int32_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bool} field, including tag.
 */
int32_t computeBoolSizeNoTag(BOOL value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code string} field, including tag.
 */
int32_t computeStringSizeNoTag(const NSString* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field, including tag.
 */
int32_t computeGroupSizeNoTag(const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field represented by an {@code PBUnknownFieldSet}, including
 * tag.
 */
int32_t computeUnknownGroupSizeNoTag(const PBUnknownFieldSet* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * embedded message field, including tag.
 */
int32_t computeMessageSizeNoTag(const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bytes} field, including tag.
 */
int32_t computeDataSizeNoTag(const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint32} field, including tag.
 */
int32_t computeUInt32SizeNoTag(int32_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * enum field, including tag.  Caller is responsible for converting the
 * enum value to its numeric value.
 */
int32_t computeEnumSizeNoTag(int32_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed32} field, including tag.
 */
int32_t computeSFixed32SizeNoTag(int32_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed64} field, including tag.
 */
int32_t computeSFixed64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint32} field, including tag.
 */
int32_t computeSInt32SizeNoTag(int32_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint64} field, including tag.
 */
int32_t computeSInt64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a varint.
 * {@code value} is treated as unsigned, so it won't be sign-extended if
 * negative.
 */
int32_t computeRawVarint32Size(int32_t value);

/** Compute the number of bytes that would be needed to encode a varint. */
int32_t computeRawVarint64Size(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * MessageSet extension to the stream.  For historical reasons,
 * the wire format differs from normal fields.
 */
int32_t computeMessageSetExtensionSize(int32_t fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode an
 * unparsed MessageSet extension field to the stream.  For
 * historical reasons, the wire format differs from normal fields.
 */
int32_t computeRawMessageSetExtensionSize(int32_t fieldNumber, const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * enum field, including tag.  Caller is responsible for converting the
 * enum value to its numeric value.
 */
int32_t computeEnumSize(int32_t fieldNumber, int32_t value);
