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

@class PBExtensionRegistry;
@class PBUnknownFieldSetBuilder;
@protocol PBMessageBuilder;

/**
 * Reads and decodes protocol message fields.
 *
 * This class contains two kinds of methods:  methods that read specific
 * protocol message constructs and field types (e.g. {@link #readTag()} and
 * {@link #readInt32()}) and methods that read low-level values (e.g.
 * {@link #readRawVarint32()} and {@link #readRawBytes}).  If you are reading
 * encoded protocol messages, you should use the former methods, but if you are
 * reading some other format of your own design, use the latter.
 *
 * @author Cyrus Najmabadi
 */
@interface PBCodedInputStream : NSObject {
@private
  NSMutableData* buffer;
  long bufferSize;
  long bufferSizeAfterLimit;
  long bufferPos;
  NSInputStream* input;
  long lastTag;

  /**
   * The total number of bytes read before the current buffer.  The total
   * bytes read up to the current position can be computed as
   * {@code totalBytesRetired + bufferPos}.
   */
  long totalBytesRetired;

  /** The absolute position of the end of the current message. */
  long currentLimit;

  /** See setRecursionLimit() */
  long recursionDepth;
  long recursionLimit;

  /** See setSizeLimit() */
  long sizeLimit;
}

+ (PBCodedInputStream*) streamWithData:(NSData*) data;
+ (PBCodedInputStream*) streamWithInputStream:(NSInputStream*) input;

/**
 * Attempt to read a field tag, returning zero if we have reached EOF.
 * Protocol message parsers use this to read tags, since a protocol message
 * may legally end wherever a tag occurs, and zero is not a valid tag number.
 */
- (long) readTag;
- (BOOL) refillBuffer:(BOOL) mustSucceed;

- (Float64) readDouble;
- (Float32) readFloat;
- (long long) readUInt64;
- (long) readUInt32;
- (long long) readInt64;
- (long) readInt32;
- (long long) readFixed64;
- (long) readFixed32;
- (long) readEnum;
- (long) readSFixed32;
- (long long) readSFixed64;
- (long) readSInt32;
- (long long) readSInt64;

/**
 * Read one byte from the input.
 *
 * @throws InvalidProtocolBuffer The end of the stream or the current
 *                                        limit was reached.
 */
- (int8_t) readRawByte;

/**
 * Read a raw Varint from the stream.  If larger than 32 bits, discard the
 * upper bits.
 */
- (long) readRawVarint32;
- (long long) readRawVarint64;
- (long) readRawLittleEndian32;
- (long long) readRawLittleEndian64;

/**
 * Read a fixed size of bytes from the input.
 *
 * @throws InvalidProtocolBuffer The end of the stream or the current
 *                                        limit was reached.
 */
- (NSData*) readRawData:(long) size;

/**
 * Reads and discards a single field, given its tag value.
 *
 * @return {@code false} if the tag is an endgroup tag, in which case
 *         nothing is skipped.  Otherwise, returns {@code true}.
 */
- (BOOL) skipField:(long) tag;


/**
 * Reads and discards {@code size} bytes.
 *
 * @throws InvalidProtocolBuffer The end of the stream or the current
 *                                        limit was reached.
 */
- (void) skipRawData:(long) size;

/**
 * Reads and discards an entire message.  This will read either until EOF
 * or until an endgroup tag, whichever comes first.
 */
- (void) skipMessage;

- (BOOL) isAtEnd;
- (long) pushLimit:(long) byteLimit;
- (void) recomputeBufferSizeAfterLimit;
- (void) popLimit:(long) oldLimit;
- (long) bytesUntilLimit;


/** Read an embedded message field value from the stream. */
- (void) readMessage:(id<PBMessageBuilder>) builder extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) readBool;
- (NSString*) readString;
- (NSData*) readData;

- (void) readGroup:(long) fieldNumber builder:(id<PBMessageBuilder>) builder extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

/**
 * Reads a {@code group} field value from the stream and merges it into the
 * given {@link UnknownFieldSet}.
 */
- (void) readUnknownGroup:(long) fieldNumber builder:(PBUnknownFieldSetBuilder*) builder;

/**
 * Verifies that the last call to readTag() returned the given tag value.
 * This is used to verify that a nested group ended with the correct
 * end tag.
 *
 * @throws InvalidProtocolBuffer {@code value} does not match the
 *                                        last tag.
 */
- (void) checkLastTagWas:(long) value;

@end
