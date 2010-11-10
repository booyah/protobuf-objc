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

/**
 * Encodes and writes protocol message fields.
 *
 * <p>This class contains two kinds of methods:  methods that write specific
 * protocol message constructs and field types (e.g. {@link #writeTag} and
 * {@link #writeInt32}) and methods that write low-level values (e.g.
 * {@link #writeRawVarint32} and {@link #writeRawBytes}).  If you are
 * writing encoded protocol messages, you should use the former methods, but if
 * you are writing some other format of your own design, use the latter.
 *
 * <p>This class is totally unsynchronized.
 *
 * @author Cyrus Najmabadi
 */

@class PBUnknownFieldSet;
@class RingBuffer;
@protocol PBMessage;

@interface PBCodedOutputStream : NSObject {
    NSOutputStream *output;
    RingBuffer *buffer;
}

+ (PBCodedOutputStream*) streamWithData:(NSMutableData*) data;
+ (PBCodedOutputStream*) streamWithOutputStream:(NSOutputStream*) output;
+ (PBCodedOutputStream*) streamWithOutputStream:(NSOutputStream*) output bufferSize:(int32_t) bufferSize;

/**
 * Flushes the stream and forces any buffered bytes to be written.  This
 * does not flush the underlying NSOutputStream. Returns free space in buffer.
 */
- (void) flush;

/** Write a single byte. */
- (void) writeRawByte:(uint8_t) value;

/** Encode and write a tag. */
- (void) writeTag:(int32_t) fieldNumber format:(int32_t) format;

/** Write a little-endian 32-bit integer. */
- (void) writeRawLittleEndian32:(int32_t) value;
/** Write a little-endian 64-bit integer. */
- (void) writeRawLittleEndian64:(int64_t) value;

/**
 * Encode and write a varint.  {@code value} is treated as
 * unsigned, so it won't be sign-extended if negative.
 */
- (void) writeRawVarint32:(int32_t) value;
/** Encode and write a varint. */
- (void) writeRawVarint64:(int64_t) value;

- (void) writeRawLittleEndian32:(int32_t) value;
- (void) writeRawLittleEndian64:(int64_t) value;

/** Write an array of bytes. */
- (void) writeRawData:(const NSData*) data;
- (void) writeRawData:(const NSData*) data offset:(int32_t) offset length:(int32_t) length;

- (void) writeData:(int32_t) fieldNumber value:(const NSData*) value;

- (void) writeDouble:(int32_t) fieldNumber value:(Float64) value;
- (void) writeFloat:(int32_t) fieldNumber value:(Float32) value;
- (void) writeUInt64:(int32_t) fieldNumber value:(int64_t) value;
- (void) writeInt64:(int32_t) fieldNumber value:(int64_t) value;
- (void) writeInt32:(int32_t) fieldNumber value:(int32_t) value;
- (void) writeFixed64:(int32_t) fieldNumber value:(int64_t) value;
- (void) writeFixed32:(int32_t) fieldNumber value:(int32_t) value;
- (void) writeBool:(int32_t) fieldNumber value:(BOOL) value;
- (void) writeString:(int32_t) fieldNumber value:(const NSString*) value;
- (void) writeGroup:(int32_t) fieldNumber value:(const id<PBMessage>) value;
- (void) writeUnknownGroup:(int32_t) fieldNumber value:(const PBUnknownFieldSet*) value;
- (void) writeMessage:(int32_t) fieldNumber value:(const id<PBMessage>) value;
- (void) writeUInt32:(int32_t) fieldNumber value:(int32_t) value;
- (void) writeSFixed32:(int32_t) fieldNumber value:(int32_t) value;
- (void) writeSFixed64:(int32_t) fieldNumber value:(int64_t) value;
- (void) writeSInt32:(int32_t) fieldNumber value:(int32_t) value;
- (void) writeSInt64:(int32_t) fieldNumber value:(int64_t) value;

- (void) writeDoubleNoTag:(Float64) value;
- (void) writeFloatNoTag:(Float32) value;
- (void) writeUInt64NoTag:(int64_t) value;
- (void) writeInt64NoTag:(int64_t) value;
- (void) writeInt32NoTag:(int32_t) value;
- (void) writeFixed64NoTag:(int64_t) value;
- (void) writeFixed32NoTag:(int32_t) value;
- (void) writeBoolNoTag:(BOOL) value;
- (void) writeStringNoTag:(const NSString*) value;
- (void) writeGroupNoTag:(int32_t) fieldNumber value:(const id<PBMessage>) value;
- (void) writeUnknownGroupNoTag:(int32_t) fieldNumber value:(const PBUnknownFieldSet*) value;
- (void) writeMessageNoTag:(const id<PBMessage>) value;
- (void) writeDataNoTag:(const NSData*) value;
- (void) writeUInt32NoTag:(int32_t) value;
- (void) writeEnumNoTag:(int32_t) value;
- (void) writeSFixed32NoTag:(int32_t) value;
- (void) writeSFixed64NoTag:(int64_t) value;
- (void) writeSInt32NoTag:(int32_t) value;
- (void) writeSInt64NoTag:(int64_t) value;


/**
 * Write a MessageSet extension field to the stream.  For historical reasons,
 * the wire format differs from normal fields.
 */
- (void) writeMessageSetExtension:(int32_t) fieldNumber value:(const id<PBMessage>) value;

/**
 * Write an unparsed MessageSet extension field to the stream.  For
 * historical reasons, the wire format differs from normal fields.
 */
- (void) writeRawMessageSetExtension:(int32_t) fieldNumber value:(const NSData*) value;

/**
 * Write an enum field, including tag, to the stream.  Caller is responsible
 * for converting the enum value to its numeric value.
 */
- (void) writeEnum:(int32_t) fieldNumber value:(int32_t) value;

@end
