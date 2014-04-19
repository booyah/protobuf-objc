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
NSInteger convertFloat32ToInt32(Float32 f);
Float64 convertInt64ToFloat64(int64_t f);
Float32 convertInt32ToFloat32(NSInteger f);

uint64_t convertInt64ToUInt64(int64_t i);
int64_t  convertUInt64ToInt64(uint64_t u);
NSUInteger convertInt32ToUInt32(NSInteger i);
int64_t  convertUInt32ToInt32(NSUInteger u);

NSInteger logicalRightShift32(NSInteger value, NSInteger spaces);
int64_t logicalRightShift64(int64_t value, NSInteger spaces);


/**
 * Decode a ZigZag-encoded 32-bit value.  ZigZag encodes signed integers
 * into values that can be efficiently encoded with varint.  (Otherwise,
 * negative values must be sign-extended to 64 bits to be varint encoded,
 * thus always taking 10 bytes on the wire.)
 *
 * @param n An unsigned 32-bit integer, stored in a signed int.
 * @return A signed 32-bit integer.
 */
NSInteger decodeZigZag32(NSInteger n);

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
NSInteger encodeZigZag32(NSInteger n);

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
NSInteger computeDoubleSize(NSInteger fieldNumber, Float64 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code float} field, including tag.
 */
NSInteger computeFloatSize(NSInteger fieldNumber, Float32 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint64} field, including tag.
 */
NSInteger computeUInt64Size(NSInteger fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int64} field, including tag.
 */
NSInteger computeInt64Size(NSInteger fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int32} field, including tag.
 */
NSInteger computeInt32Size(NSInteger fieldNumber, NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed64} field, including tag.
 */
NSInteger computeFixed64Size(NSInteger fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed32} field, including tag.
 */
NSInteger computeFixed32Size(NSInteger fieldNumber, NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bool} field, including tag.
 */
NSInteger computeBoolSize(NSInteger fieldNumber, BOOL value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code string} field, including tag.
 */
NSInteger computeStringSize(NSInteger fieldNumber, const NSString* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field, including tag.
 */
NSInteger computeGroupSize(NSInteger fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field represented by an {@code PBUnknownFieldSet}, including
 * tag.
 */
NSInteger computeUnknownGroupSize(NSInteger fieldNumber, const PBUnknownFieldSet* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * embedded message field, including tag.
 */
NSInteger computeMessageSize(NSInteger fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bytes} field, including tag.
 */
NSInteger computeDataSize(NSInteger fieldNumber, const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint32} field, including tag.
 */
NSInteger computeUInt32Size(NSInteger fieldNumber, NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed32} field, including tag.
 */
NSInteger computeSFixed32Size(NSInteger fieldNumber, NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed64} field, including tag.
 */
NSInteger computeSFixed64Size(NSInteger fieldNumber, int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint32} field, including tag.
 */
NSInteger computeSInt32Size(NSInteger fieldNumber, NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint64} field, including tag.
 */
NSInteger computeSInt64Size(NSInteger fieldNumber, int64_t value);

/** Compute the number of bytes that would be needed to encode a tag. */
NSInteger computeTagSize(NSInteger fieldNumber);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code double} field, including tag.
 */
NSInteger computeDoubleSizeNoTag(Float64 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code float} field, including tag.
 */
NSInteger computeFloatSizeNoTag(Float32 value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint64} field, including tag.
 */
NSInteger computeUInt64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int64} field, including tag.
 */
NSInteger computeInt64SizeNoTag(int64_t value);
/**
 * Compute the number of bytes that would be needed to encode an
 * {@code int32} field, including tag.
 */
NSInteger computeInt32SizeNoTag(NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed64} field, including tag.
 */
NSInteger computeFixed64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code fixed32} field, including tag.
 */
NSInteger computeFixed32SizeNoTag(NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bool} field, including tag.
 */
NSInteger computeBoolSizeNoTag(BOOL value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code string} field, including tag.
 */
NSInteger computeStringSizeNoTag(const NSString* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field, including tag.
 */
NSInteger computeGroupSizeNoTag(const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code group} field represented by an {@code PBUnknownFieldSet}, including
 * tag.
 */
NSInteger computeUnknownGroupSizeNoTag(const PBUnknownFieldSet* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * embedded message field, including tag.
 */
NSInteger computeMessageSizeNoTag(const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code bytes} field, including tag.
 */
NSInteger computeDataSizeNoTag(const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode a
 * {@code uint32} field, including tag.
 */
NSInteger computeUInt32SizeNoTag(NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode an
 * enum field, including tag.  Caller is responsible for converting the
 * enum value to its numeric value.
 */
NSInteger computeEnumSizeNoTag(NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed32} field, including tag.
 */
NSInteger computeSFixed32SizeNoTag(NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sfixed64} field, including tag.
 */
NSInteger computeSFixed64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint32} field, including tag.
 */
NSInteger computeSInt32SizeNoTag(NSInteger value);

/**
 * Compute the number of bytes that would be needed to encode an
 * {@code sint64} field, including tag.
 */
NSInteger computeSInt64SizeNoTag(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a varint.
 * {@code value} is treated as unsigned, so it won't be sign-extended if
 * negative.
 */
NSInteger computeRawVarint32Size(NSInteger value);

/** Compute the number of bytes that would be needed to encode a varint. */
NSInteger computeRawVarint64Size(int64_t value);

/**
 * Compute the number of bytes that would be needed to encode a
 * MessageSet extension to the stream.  For historical reasons,
 * the wire format differs from normal fields.
 */
NSInteger computeMessageSetExtensionSize(NSInteger fieldNumber, const id<PBMessage> value);

/**
 * Compute the number of bytes that would be needed to encode an
 * unparsed MessageSet extension field to the stream.  For
 * historical reasons, the wire format differs from normal fields.
 */
NSInteger computeRawMessageSetExtensionSize(NSInteger fieldNumber, const NSData* value);

/**
 * Compute the number of bytes that would be needed to encode an
 * enum field, including tag.  Caller is responsible for converting the
 * enum value to its numeric value.
 */
NSInteger computeEnumSize(NSInteger fieldNumber, NSInteger value);
