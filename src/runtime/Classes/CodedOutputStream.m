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

#import "CodedOutputStream.h"
#import "RingBuffer.h"
#import "Message.h"
#import "Utilities.h"
#import "WireFormat.h"


@implementation PBCodedOutputStream

const long DEFAULT_BUFFER_SIZE = 4 * 1024;


- (id)initWithOutputStream:(NSOutputStream*)_output data:(NSMutableData*)data {
	if ( (self = [super init]) ) {
		output = [_output retain];
		buffer = [[RingBuffer alloc] initWithData:data];
	}
	return self;
}


- (void)dealloc {
	[output release];
	[buffer release];
	[super dealloc];
}


+ (PBCodedOutputStream*)streamWithOutputStream:(NSOutputStream*)output bufferSize:(long)bufferSize {
	NSMutableData *data = [NSMutableData dataWithLength:bufferSize];
	return [[[PBCodedOutputStream alloc] initWithOutputStream:output data:data] autorelease];
}


+ (PBCodedOutputStream*)streamWithOutputStream:(NSOutputStream*)output {
	return [PBCodedOutputStream streamWithOutputStream:output bufferSize:DEFAULT_BUFFER_SIZE];
}


+ (PBCodedOutputStream*)streamWithData:(NSMutableData*)data {
	return [[[PBCodedOutputStream alloc] initWithOutputStream:nil data:data] autorelease];
}


- (void)flush {
	if (output == nil) {
		// We're writing to a single buffer.
		@throw [NSException exceptionWithName:@"OutOfSpace" reason:@"" userInfo:nil];
	}
	
	[buffer flushToOutputStream:output];
}


- (void)writeRawByte:(uint8_t)value {
	while (![buffer appendByte:value]) {
        [self flush];
	}
}


- (void)writeRawData:(const NSData*)data {
	[self writeRawData:data offset:0 length:data.length];
}


- (void)writeRawData:(const NSData*)value offset:(long)offset length:(long)length {
	while (length > 0) {
		long written = [buffer appendData:value offset:offset length:length];
		offset += written;
		length -= written;
		if (!written || length > 0) {
            [self flush];
		}
	}
}


- (void)writeDoubleNoTag:(Float64)value {
	[self writeRawLittleEndian64:convertFloat64ToInt64(value)];
}


/** Write a {@code double} field, including tag, to the stream. */
- (void)writeDouble:(long)fieldNumber value:(Float64)value {
	[self writeTag:fieldNumber format:PBWireFormatFixed64];
	[self writeDoubleNoTag:value];
}


- (void)writeFloatNoTag:(Float32)value {
	[self writeRawLittleEndian32:convertFloat32ToInt32(value)];
}


/** Write a {@code float} field, including tag, to the stream. */
- (void)writeFloat:(long)fieldNumber value:(Float32)value {
	[self writeTag:fieldNumber format:PBWireFormatFixed32];
	[self writeFloatNoTag:value];
}


- (void)writeUInt64NoTag:(long long)value {
	[self writeRawVarint64:value];
}


/** Write a {@code uint64} field, including tag, to the stream. */
- (void)writeUInt64:(long)fieldNumber value:(long long)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeUInt64NoTag:value];
}


- (void)writeInt64NoTag:(long long)value {
	[self writeRawVarint64:value];
}


/** Write an {@code int64} field, including tag, to the stream. */
- (void)writeInt64:(long)fieldNumber value:(long long)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeInt64NoTag:value];
}


- (void)writeInt32NoTag:(long)value {
	if (value >= 0) {
		[self writeRawVarint32:value];
	} else {
		// Must sign-extend
		[self writeRawVarint64:value];
	}
}


/** Write an {@code int32} field, including tag, to the stream. */
- (void)writeInt32:(long)fieldNumber value:(long)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeInt32NoTag:value];
}


- (void)writeFixed64NoTag:(long long)value {
	[self writeRawLittleEndian64:value];
}


/** Write a {@code fixed64} field, including tag, to the stream. */
- (void)writeFixed64:(long)fieldNumber value:(long long)value {
	[self writeTag:fieldNumber format:PBWireFormatFixed64];
	[self writeFixed64NoTag:value];
}


- (void)writeFixed32NoTag:(long)value {
	[self writeRawLittleEndian32:value];
}


/** Write a {@code fixed32} field, including tag, to the stream. */
- (void)writeFixed32:(long)fieldNumber value:(long)value {
	[self writeTag:fieldNumber format:PBWireFormatFixed32];
	[self writeFixed32NoTag:value];
}


- (void)writeBoolNoTag:(BOOL)value {
	[self writeRawByte:(value ? 1 : 0)];
}


/** Write a {@code bool} field, including tag, to the stream. */
- (void)writeBool:(long)fieldNumber value:(BOOL)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeBoolNoTag:value];
}


- (void)writeStringNoTag:(const NSString*)value {
	NSData* data = [value dataUsingEncoding:NSUTF8StringEncoding];
	[self writeRawVarint32:data.length];
	[self writeRawData:data];
}


/** Write a {@code string} field, including tag, to the stream. */
- (void)writeString:(long)fieldNumber value:(const NSString*)value {
	[self writeTag:fieldNumber format:PBWireFormatLengthDelimited];
	[self writeStringNoTag:value];
}


- (void)writeGroupNoTag:(long)fieldNumber value:(const id<PBMessage>)value {
	[value writeToCodedOutputStream:self];
	[self writeTag:fieldNumber format:PBWireFormatEndGroup];
}


/** Write a {@code group} field, including tag, to the stream. */
- (void)writeGroup:(long)fieldNumber value:(const id<PBMessage>)value {
	[self writeTag:fieldNumber format:PBWireFormatStartGroup];
	[self writeGroupNoTag:fieldNumber value:value];
}


- (void)writeUnknownGroupNoTag:(long)fieldNumber value:(const PBUnknownFieldSet*)value {
	[value writeToCodedOutputStream:self];
	[self writeTag:fieldNumber format:PBWireFormatEndGroup];
}


/** Write a group represented by an {@link PBUnknownFieldSet}. */
- (void)writeUnknownGroup:(long)fieldNumber value:(const PBUnknownFieldSet*)value {
	[self writeTag:fieldNumber format:PBWireFormatStartGroup];
	[self writeUnknownGroupNoTag:fieldNumber value:value];
}


- (void)writeMessageNoTag:(const id<PBMessage>)value {
	[self writeRawVarint32:[value serializedSize]];
	[value writeToCodedOutputStream:self];
}


/** Write an embedded message field, including tag, to the stream. */
- (void)writeMessage:(long)fieldNumber value:(const id<PBMessage>)value {
	[self writeTag:fieldNumber format:PBWireFormatLengthDelimited];
	[self writeMessageNoTag:value];
}


- (void)writeDataNoTag:(const NSData*)value {
	[self writeRawVarint32:value.length];
	[self writeRawData:value];
}


/** Write a {@code bytes} field, including tag, to the stream. */
- (void)writeData:(long)fieldNumber value:(const NSData*)value {
	[self writeTag:fieldNumber format:PBWireFormatLengthDelimited];
	[self writeDataNoTag:value];
}


- (void)writeUInt32NoTag:(long)value {
	[self writeRawVarint32:value];
}


/** Write a {@code uint32} field, including tag, to the stream. */
- (void)writeUInt32:(long)fieldNumber value:(long)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeUInt32NoTag:value];
}


- (void)writeEnumNoTag:(long)value {
	[self writeRawVarint32:value];
}


- (void)writeEnum:(long)fieldNumber value:(long)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeEnumNoTag:value];
}


- (void)writeSFixed32NoTag:(long)value {
	[self writeRawLittleEndian32:value];
}


/** Write an {@code sfixed32} field, including tag, to the stream. */
- (void)writeSFixed32:(long)fieldNumber value:(long)value {
	[self writeTag:fieldNumber format:PBWireFormatFixed32];
	[self writeSFixed32NoTag:value];
}


- (void)writeSFixed64NoTag:(long long)value {
	[self writeRawLittleEndian64:value];
}


/** Write an {@code sfixed64} field, including tag, to the stream. */
- (void)writeSFixed64:(long)fieldNumber value:(long long)value {
	[self writeTag:fieldNumber format:PBWireFormatFixed64];
	[self writeSFixed64NoTag:value];
}


- (void)writeSInt32NoTag:(long)value {
	[self writeRawVarint32:encodeZigZag32(value)];
}


/** Write an {@code sint32} field, including tag, to the stream. */
- (void)writeSInt32:(long)fieldNumber value:(long)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeSInt32NoTag:value];
}


- (void)writeSInt64NoTag:(long long)value {
	[self writeRawVarint64:encodeZigZag64(value)];
}


/** Write an {@code sint64} field, including tag, to the stream. */
- (void)writeSInt64:(long)fieldNumber value:(long long)value {
	[self writeTag:fieldNumber format:PBWireFormatVarint];
	[self writeSInt64NoTag:value];
}


/**
 * Write a MessageSet extension field to the stream.  For historical reasons,
 * the wire format differs from normal fields.
 */
- (void)writeMessageSetExtension:(long)fieldNumber value:(const id<PBMessage>)value {
	[self writeTag:PBWireFormatMessageSetItem format:PBWireFormatStartGroup];
	[self writeUInt32:PBWireFormatMessageSetTypeId value:fieldNumber];
	[self writeMessage:PBWireFormatMessageSetMessage value:value];
	[self writeTag:PBWireFormatMessageSetItem format:PBWireFormatEndGroup];
}


/**
 * Write an unparsed MessageSet extension field to the stream.  For
 * historical reasons, the wire format differs from normal fields.
 */
- (void)writeRawMessageSetExtension:(long)fieldNumber value:(const NSData*)value {
	[self writeTag:PBWireFormatMessageSetItem format:PBWireFormatStartGroup];
	[self writeUInt32:PBWireFormatMessageSetTypeId value:fieldNumber];
	[self writeData:PBWireFormatMessageSetMessage value:value];
	[self writeTag:PBWireFormatMessageSetItem format:PBWireFormatEndGroup];
}


- (void)writeTag:(long)fieldNumber format:(long)format {
	[self writeRawVarint32:PBWireFormatMakeTag(fieldNumber, format)];
}


- (void)writeRawVarint32:(long)value {
	while (YES) {
		if ((value & ~0x7F) == 0) {
			[self writeRawByte:value];
			return;
		} else {
			[self writeRawByte:((value & 0x7F) | 0x80)];
			value = logicalRightShift32(value, 7);
		}
	}
}


- (void)writeRawVarint64:(long long)value {
	while (YES) {
		if ((value & ~0x7FL) == 0) {
			[self writeRawByte:((long)value)];
			return;
		} else {
			[self writeRawByte:(((long)value & 0x7F) | 0x80)];
			value = logicalRightShift64(value, 7);
		}
	}
}


- (void)writeRawLittleEndian32:(long)value {
	[self writeRawByte:((value      ) & 0xFF)];
	[self writeRawByte:((value >>  8) & 0xFF)];
	[self writeRawByte:((value >> 16) & 0xFF)];
	[self writeRawByte:((value >> 24) & 0xFF)];
}


- (void)writeRawLittleEndian64:(long long)value {
	[self writeRawByte:((long)(value      ) & 0xFF)];
	[self writeRawByte:((long)(value >>  8) & 0xFF)];
	[self writeRawByte:((long)(value >> 16) & 0xFF)];
	[self writeRawByte:((long)(value >> 24) & 0xFF)];
	[self writeRawByte:((long)(value >> 32) & 0xFF)];
	[self writeRawByte:((long)(value >> 40) & 0xFF)];
	[self writeRawByte:((long)(value >> 48) & 0xFF)];
	[self writeRawByte:((long)(value >> 56) & 0xFF)];
}

@end
