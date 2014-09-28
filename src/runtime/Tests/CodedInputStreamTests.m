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

#import "CodedInputStreamTests.h"

#import "SmallBlockInputStream.h"
#import "TestUtilities.h"
#import "Unittest.pb.h"

@implementation CodedInputStreamTests

- (NSData*) bytes_with_sentinel:(SInt32) unused, ... {
  va_list list;
  va_start(list, unused);

  NSMutableData* values = [NSMutableData dataWithCapacity:0];
  SInt32 i;

  while ((i = va_arg(list, SInt32)) != 256) {
    NSAssert(i >= 0 && i < 256, @"");
    uint8_t u = (uint8_t)i;
    [values appendBytes:&u length:1];
  }

  va_end(list);

  return values;
}

#define bytes(...) [self bytes_with_sentinel:0, __VA_ARGS__, 256]

- (void) testDecodeZigZag {
  XCTAssertEqual((SInt32) 0, decodeZigZag32(0));
  XCTAssertEqual((SInt32)-1, decodeZigZag32(1));
  XCTAssertEqual((SInt32)1, decodeZigZag32(2));
  XCTAssertEqual((SInt32)-2, decodeZigZag32(3));

    //    014-06-24 16:03:45.345 xctest[2274:30b] 1073741823 - 1073741823
//    2014-06-24 16:03:45.346 xctest[2274:30b] -1073741824 - 3221225472
    
  XCTAssertTrue((SInt32)0x3FFFFFFF == decodeZigZag32(0x7FFFFFFE));

  XCTAssertEqual((NSInteger)0xFFFFFFFFC0000000, decodeZigZag32(0x7FFFFFFF));

//  XCTAssertEqual((SInt32)0x7FFFFFFF, decodeZigZag32(0xFFFFFFFE));
//  XCTAssertEqual((SInt32)0x80000000, decodeZigZag32(0xFFFFFFFF));

  XCTAssertEqual((SInt64) 0, decodeZigZag64(0));
  XCTAssertEqual((SInt64)-1, decodeZigZag64(1));
  XCTAssertEqual((SInt64) 1, decodeZigZag64(2));
  XCTAssertEqual((SInt64)-2, decodeZigZag64(3));
  XCTAssertEqual((SInt64)0x000000003FFFFFFFL, decodeZigZag64(0x000000007FFFFFFEL));
  XCTAssertEqual((SInt64)0xFFFFFFFFC0000000L, decodeZigZag64(0x000000007FFFFFFFL));
  XCTAssertEqual((SInt64)0x000000007FFFFFFFL, decodeZigZag64(0x00000000FFFFFFFEL));
  XCTAssertEqual((SInt64)0xFFFFFFFF80000000L, decodeZigZag64(0x00000000FFFFFFFFL));
  XCTAssertEqual((SInt64)0x7FFFFFFFFFFFFFFFL, decodeZigZag64(0xFFFFFFFFFFFFFFFEL));
  XCTAssertEqual((SInt64)0x8000000000000000L, decodeZigZag64(0xFFFFFFFFFFFFFFFFL));
}

/** Tests readRawVarint32() and readRawVarint64(). */
- (void) testReadVarint {
    [self assertReadVarint:bytes(0x00) value:0];
    [self assertReadVarint:bytes(0x01) value:1];
    [self assertReadVarint:bytes(0x7f) value:127];
    // 14882
    [self assertReadVarint:bytes(0xa2, 0x74) value:(0x22 << 0) | (0x74 << 7)];
    // 2961488830
    [self assertReadVarint:bytes(0xbe, 0xf7, 0x92, 0x84, 0x0b) value:
     (0x3e << 0) | (0x77 << 7) | (0x12 << 14) | (0x04 << 21) |
     (0x0bLL << 28)];
    
    // 64-bit
    // 7256456126
    [self assertReadVarint:bytes(0xbe, 0xf7, 0x92, 0x84, 0x1b) value:
     (0x3e << 0) | (0x77 << 7) | (0x12 << 14) | (0x04 << 21) |
     (0x1bLL << 28)];
    // 41256202580718336
    [self assertReadVarint:
     bytes(0x80, 0xe6, 0xeb, 0x9c, 0xc3, 0xc9, 0xa4, 0x49) value:
     (0x00 << 0) | (0x66 << 7) | (0x6b << 14) | (0x1c << 21) |
     (0x43LL << 28) | (0x49LL << 35) | (0x24LL << 42) | (0x49LL << 49)];
    // 11964378330978735131
    [self assertReadVarint:
     bytes(0x9b, 0xa8, 0xf9, 0xc2, 0xbb, 0xd6, 0x80, 0x85, 0xa6, 0x01) value:
     (0x1b << 0) | (0x28 << 7) | (0x79 << 14) | (0x42 << 21) |
     (0x3bLL << 28) | (0x56LL << 35) | (0x00LL << 42) |
     (0x05LL << 49) | (0x26LL << 56) | (0x01LL << 63)];
    
    // Failures
    [self assertReadVarintFailure:bytes(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00)];
    [self assertReadVarintFailure:bytes(0x80)];
}


/**
 * Parses the given bytes using readRawVarint32() and readRawVarint64() and
 * checks that the result matches the given value.
 */
- (void) assertReadVarint:(NSData*) data value:(SInt64) value {
  {
    PBCodedInputStream* input = [PBCodedInputStream streamWithData:data];
    XCTAssertTrue((SInt32)value == [input readRawVarint32], @"");
  }
  {
    PBCodedInputStream* input = [PBCodedInputStream streamWithData:data];
    XCTAssertTrue(value == [input readRawVarint64], @"");
  }

  {
    PBCodedInputStream* input = [PBCodedInputStream streamWithInputStream:[NSInputStream inputStreamWithData:data]];
    XCTAssertTrue((SInt32)value == [input readRawVarint32], @"");
  }
  {
    PBCodedInputStream* input = [PBCodedInputStream streamWithInputStream:[NSInputStream inputStreamWithData:data]];
    XCTAssertTrue(value == [input readRawVarint64], @"");
  }

  // Try different block sizes.
  for (SInt32 blockSize = 1; blockSize <= 16; blockSize *= 2) {
    {
      PBCodedInputStream* input = [PBCodedInputStream streamWithInputStream:[SmallBlockInputStream streamWithData:data blockSize:blockSize]];
      XCTAssertTrue((SInt32)value == [input readRawVarint32], @"");
    }
    {
      PBCodedInputStream* input = [PBCodedInputStream streamWithInputStream:[SmallBlockInputStream streamWithData:data blockSize:blockSize]];
      XCTAssertTrue(value == [input readRawVarint64], @"");
    }
  }
}


/**
 * Parses the given bytes using readRawLittleEndian32() and checks
 * that the result matches the given value.
 */
- (void) assertReadLittleEndian32:(NSData*) data value:(SInt32) value {
  PBCodedInputStream* input = [PBCodedInputStream streamWithData:data];
  XCTAssertTrue(value == [input readRawLittleEndian32], @"");

  // Try different block sizes.
  for (SInt32 blockSize = 1; blockSize <= 16; blockSize *= 2) {
    PBCodedInputStream* input =
    [PBCodedInputStream streamWithInputStream:
     [SmallBlockInputStream streamWithData:data blockSize:blockSize]];
    XCTAssertTrue(value == [input readRawLittleEndian32], @"");
  }
}


/**
 * Parses the given bytes using readRawLittleEndian64() and checks
 * that the result matches the given value.
 */
- (void) assertReadLittleEndian64:(NSData*) data value:(SInt64) value {
  PBCodedInputStream* input = [PBCodedInputStream streamWithData:data];
  XCTAssertTrue(value == [input readRawLittleEndian64], @"");

  // Try different block sizes.
  for (SInt32 blockSize = 1; blockSize <= 16; blockSize *= 2) {
    PBCodedInputStream* input =
    [PBCodedInputStream streamWithInputStream:
     [SmallBlockInputStream streamWithData:data blockSize:blockSize]];
    XCTAssertTrue(value == [input readRawLittleEndian64], @"");
  }
}


/**
 * Parses the given bytes using readRawVarint32() and readRawVarint64() and
 * expects them to fail with an InvalidProtocolBufferException whose
 * description matches the given one.
 */
- (void) assertReadVarintFailure:(NSData*) data {
  {
    PBCodedInputStream* input = [PBCodedInputStream streamWithData:data];
    XCTAssertThrows([input readRawVarint32], @"");
  }
  {
    PBCodedInputStream* input = [PBCodedInputStream streamWithData:data];
    XCTAssertThrows([input readRawVarint64], @"");
  }
}


- (void) testBytes {
  NSData* data = bytes(0xa2, 0x74);
  XCTAssertTrue(data.length == 2, @"");
  XCTAssertTrue(((uint8_t*)data.bytes)[0] == 0xa2, @"");
  XCTAssertTrue(((uint8_t*)data.bytes)[1] == 0x74, @"");
}

- (void) testReadLittleEndian {
  [self assertReadLittleEndian32:bytes(0x78, 0x56, 0x34, 0x12) value:0x12345678];
  [self assertReadLittleEndian32:bytes(0xf0, 0xde, 0xbc, 0x9a) value:0x9abcdef0];

  [self assertReadLittleEndian64:
   bytes(0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12) value:
   0x123456789abcdef0LL];
  [self assertReadLittleEndian64:
   bytes(0x78, 0x56, 0x34, 0x12, 0xf0, 0xde, 0xbc, 0x9a) value:
   0x9abcdef012345678LL];
}


/** Tests reading and parsing a whole message with every field type. */
- (void) testReadWholeMessage {
  TestAllTypes* message = [TestUtilities allSet];

  NSData* rawBytes = message.data;
  XCTAssertTrue(rawBytes.length == message.serializedSize, @"");

  TestAllTypes* message2 = [TestAllTypes parseFromData:rawBytes];
  [TestUtilities assertAllFieldsSet:message2];

  // Try different block sizes.
  for (SInt32 blockSize = 1; blockSize < 256; blockSize *= 2) {
    message2 = [TestAllTypes parseFromInputStream:
                [SmallBlockInputStream streamWithData:rawBytes blockSize:blockSize]];
    [TestUtilities assertAllFieldsSet:message2];
  }
}


/** Tests skipField(). */
- (void) testSkipWholeMessage {
  TestAllTypes* message = [TestUtilities allSet];
  NSData* rawBytes = message.data;

  // Create two parallel inputs.  Parse one as unknown fields while using
  // skipField() to skip each field on the other.  Expect the same tags.
  PBCodedInputStream* input1 = [PBCodedInputStream streamWithData:rawBytes];
  PBCodedInputStream* input2 = [PBCodedInputStream streamWithData:rawBytes];
  PBUnknownFieldSetBuilder* unknownFields = [PBUnknownFieldSet builder];

  while (YES) {
    SInt32 tag = [input1 readTag];
    XCTAssertTrue(tag == [input2 readTag], @"");
    if (tag == 0) {
      break;
    }
    [unknownFields mergeFieldFrom:tag input:input1];
    [input2 skipField:tag];
  }
}


- (void) testReadHugeBlob {
  // Allocate and initialize a 1MB blob.
  NSMutableData* blob = [NSMutableData dataWithLength:1 << 20];
  for (SInt32 i = 0; i < blob.length; i++) {
    ((uint8_t*)blob.mutableBytes)[i] = (uint8_t)i;
  }

  // Make a message containing it.
  TestAllTypesBuilder* builder = [TestAllTypes builder];
  [TestUtilities setAllFields:builder];
  [builder setOptionalBytes:[NSData dataWithData:blob]];
  TestAllTypes* message = [builder build];

  // Serialize and parse it.  Make sure to parse from an InputStream, not
  // directly from a ByteString, so that CodedInputStream uses buffered
  // reading.
  TestAllTypes* message2 =
  [TestAllTypes parseFromInputStream:[NSInputStream inputStreamWithData:message.data]];

  XCTAssertEqualObjects(message.optionalBytes, message2.optionalBytes, @"");

  // Make sure all the other fields were parsed correctly.
  TestAllTypes* message3 = [[[TestAllTypes builderWithPrototype:message2]
                             setOptionalBytes:[[TestUtilities allSet] optionalBytes]] build];

  [TestUtilities assertAllFieldsSet:message3];
}


- (void) testReadMaliciouslyLargeBlob {
  NSOutputStream* rawOutput = [NSOutputStream outputStreamToMemory];
  [rawOutput open];
  PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput];

  SInt32 tag = PBWireFormatMakeTag(1, PBWireFormatLengthDelimited);
  [output writeRawVarint32:tag];
  [output writeRawVarint32:0x7FFFFFFF];
  uint8_t bytes[32] = { 0 };
  [output writeRawData:[NSData dataWithBytes:bytes length:32]];
  [output flush];

  NSData* data = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
  PBCodedInputStream* input = [PBCodedInputStream streamWithData:[NSMutableData dataWithData:data]];
  XCTAssertTrue(tag == [input readTag], @"");

  XCTAssertThrows([input readData], @"");
}

@end
