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

#import "CodedOuputStreamTests.h"

#import "TestUtilities.h"
#import "Unittest.pb.h"

@implementation CodedOutputStreamTests

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


- (void) failWithException:(NSException *) anException {
  @throw anException;
}


- (NSOutputStream*)openMemoryStream {
    NSOutputStream *stream = [NSOutputStream outputStreamToMemory];
    [stream open];
    return stream;
}

/**
 * Parses the given bytes using writeRawLittleEndian32() and checks
 * that the result matches the given value.
 */
- (void) assertWriteLittleEndian32:(NSData*) data value:(SInt32) value {
  NSOutputStream* rawOutput = [self openMemoryStream];
  PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput];
  [output writeRawLittleEndian32:(SInt32)value];
  [output flush];

  NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
  XCTAssertEqualObjects(data, actual, @"");

  // Try different block sizes.
  for (int blockSize = 1; blockSize <= 16; blockSize *= 2) {
    NSOutputStream* rawOutput = [self openMemoryStream];
    PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput bufferSize:blockSize];
    [output writeRawLittleEndian32:(SInt32)value];
    [output flush];

    NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
    XCTAssertEqualObjects(data, actual, @"");
  }
}


/**
 * Parses the given bytes using writeRawLittleEndian64() and checks
 * that the result matches the given value.
 */
- (void) assertWriteLittleEndian64:(NSData*) data value:(SInt64) value {
  NSOutputStream* rawOutput = [self openMemoryStream];
  PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput];
  [output writeRawLittleEndian64:value];
  [output flush];

  NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
  XCTAssertEqualObjects(data, actual, @"");

  // Try different block sizes.
  for (int blockSize = 1; blockSize <= 16; blockSize *= 2) {
    NSOutputStream* rawOutput = [self openMemoryStream];
    PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput bufferSize:blockSize];
    [output writeRawLittleEndian64:value];
    [output flush];

    NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
    XCTAssertEqualObjects(data, actual, @"");
  }
}



/**
 * Writes the given value using writeRawVarint32() and writeRawVarint64() and
 * checks that the result matches the given bytes.
 */
- (void) assertWriteVarint:(NSData*) data value:(SInt64) value {
  // Only do 32-bit write if the value fits in 32 bits.
  if (logicalRightShift64(value, 32) == 0) {
    NSOutputStream* rawOutput = [self openMemoryStream];
    PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput];
    [output writeRawVarint32:(SInt32)value];
    [output flush];

    NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
    XCTAssertEqualObjects(data, actual, @"");

    // Also try computing size.
    XCTAssertTrue(data.length == computeRawVarint32Size((SInt32)value), @"");
  }

  {
    NSOutputStream* rawOutput = [self openMemoryStream];
    PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput];
    [output writeRawVarint64:value];
    [output flush];

    NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
    XCTAssertEqualObjects(data, actual, @"");


    // Also try computing size.
    XCTAssertTrue(data.length == computeRawVarint64Size(value), @"");
  }

  // Try different block sizes.
  for (int blockSize = 1; blockSize <= 16; blockSize *= 2) {
    // Only do 32-bit write if the value fits in 32 bits.
    if (logicalRightShift64(value, 32) == 0) {
      NSOutputStream* rawOutput = [self openMemoryStream];
      PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput bufferSize:blockSize];

      [output writeRawVarint32:(SInt32)value];
      [output flush];

      NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
      XCTAssertEqualObjects(data, actual, @"");
    }

    {
      NSOutputStream* rawOutput = [self openMemoryStream];
      PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput bufferSize:blockSize];

      [output writeRawVarint64:value];
      [output flush];

      NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
      XCTAssertEqualObjects(data, actual, @"");
    }
  }
}


/** Tests writeRawVarint32() and writeRawVarint64(). */
- (void) testWriteVarint1 {
  [self assertWriteVarint:bytes(0x00) value:0];
}

- (void) testWriteVarint2 {
  [self assertWriteVarint:bytes(0x01) value:1];
}

- (void) testWriteVarint3 {
  [self assertWriteVarint:bytes(0x7f) value:127];
}

- (void) testWriteVarint4 {
  // 14882
  [self assertWriteVarint:bytes(0xa2, 0x74) value:(0x22 << 0) | (0x74 << 7)];
}

- (void) testWriteVarint5 {
  // 2961488830
  [self assertWriteVarint:bytes(0xbe, 0xf7, 0x92, 0x84, 0x0b) value:
   (0x3e << 0) | (0x77 << 7) | (0x12 << 14) | (0x04 << 21) |
   (0x0bLL << 28)];
}

- (void) testWriteVarint6 {
  // 64-bit
  // 7256456126
  [self assertWriteVarint:bytes(0xbe, 0xf7, 0x92, 0x84, 0x1b) value:
   (0x3e << 0) | (0x77 << 7) | (0x12 << 14) | (0x04 << 21) |
   (0x1bLL << 28)];
}

- (void) testWriteVarint7 {
  // 41256202580718336
  [self assertWriteVarint:
   bytes(0x80, 0xe6, 0xeb, 0x9c, 0xc3, 0xc9, 0xa4, 0x49) value:
   (0x00 << 0) | (0x66 << 7) | (0x6b << 14) | (0x1c << 21) |
   (0x43LL << 28) | (0x49LL << 35) | (0x24LL << 42) | (0x49LL << 49)];
}

- (void) testWriteVarint8 {
  // 11964378330978735131
  [self assertWriteVarint:
   bytes(0x9b, 0xa8, 0xf9, 0xc2, 0xbb, 0xd6, 0x80, 0x85, 0xa6, 0x01) value:
   (0x1b << 0) | (0x28 << 7) | (0x79 << 14) | (0x42 << 21) |
   (0x3bLL << 28) | (0x56LL << 35) | (0x00LL << 42) |
   (0x05LL << 49) | (0x26LL << 56) | (0x01LL << 63)];
}


/** Tests writeRawLittleEndian32() and writeRawLittleEndian64(). */
- (void) testWriteLittleEndian {
  [self assertWriteLittleEndian32:bytes(0x78, 0x56, 0x34, 0x12) value:0x12345678];
  [self assertWriteLittleEndian32:bytes(0xf0, 0xde, 0xbc, 0x9a) value:0x9abcdef0];

  [self assertWriteLittleEndian64:
   bytes(0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12) value:
   0x123456789abcdef0LL];
  [self assertWriteLittleEndian64:
   bytes(0x78, 0x56, 0x34, 0x12, 0xf0, 0xde, 0xbc, 0x9a) value:
   0x9abcdef012345678LL];
}


/** Test encodeZigZag32() and encodeZigZag64(). */
- (void) testEncodeZigZag {
  XCTAssertTrue(0 == encodeZigZag32( 0), @"");
  XCTAssertTrue(1 == encodeZigZag32(-1), @"");
  XCTAssertTrue(2 == encodeZigZag32( 1), @"");
  XCTAssertTrue(3 == encodeZigZag32(-2), @"");
  XCTAssertTrue(0x7FFFFFFE == encodeZigZag32(0x3FFFFFFF), @"");
  XCTAssertTrue(0x7FFFFFFF == encodeZigZag32(0xC0000000), @"");
  XCTAssertTrue(0xFFFFFFFE == encodeZigZag32(0x7FFFFFFF), @"");
  XCTAssertTrue(0xFFFFFFFF == encodeZigZag32(0x80000000), @"");

  XCTAssertTrue(0 == encodeZigZag64( 0), @"");
  XCTAssertTrue(1 == encodeZigZag64(-1), @"");
  XCTAssertTrue(2 == encodeZigZag64( 1), @"");
  XCTAssertTrue(3 == encodeZigZag64(-2), @"");
  XCTAssertTrue(0x000000007FFFFFFELL == encodeZigZag64(0x000000003FFFFFFFLL), @"");
  XCTAssertTrue(0x000000007FFFFFFFLL == encodeZigZag64(0xFFFFFFFFC0000000LL), @"");
  XCTAssertTrue(0x00000000FFFFFFFELL == encodeZigZag64(0x000000007FFFFFFFLL), @"");
  XCTAssertTrue(0x00000000FFFFFFFFLL == encodeZigZag64(0xFFFFFFFF80000000LL), @"");
  XCTAssertTrue(0xFFFFFFFFFFFFFFFELL == encodeZigZag64(0x7FFFFFFFFFFFFFFFLL), @"");
  XCTAssertTrue(0xFFFFFFFFFFFFFFFFLL == encodeZigZag64(0x8000000000000000LL), @"");

  // Some easier-to-verify round-trip tests.  The inputs (other than 0, 1, -1)
  // were chosen semi-randomly via keyboard bashing.
  XCTAssertTrue(0 == encodeZigZag32(decodeZigZag32(0)), @"");
  XCTAssertTrue(1 == encodeZigZag32(decodeZigZag32(1)), @"");
  XCTAssertTrue(-1 == encodeZigZag32(decodeZigZag32(-1)), @"");
  XCTAssertTrue(14927 == encodeZigZag32(decodeZigZag32(14927)), @"");
  XCTAssertTrue(-3612 == encodeZigZag32(decodeZigZag32(-3612)), @"");

  XCTAssertTrue(0 == encodeZigZag64(decodeZigZag64(0)), @"");
  XCTAssertTrue(1 == encodeZigZag64(decodeZigZag64(1)), @"");
  XCTAssertTrue(-1 == encodeZigZag64(decodeZigZag64(-1)), @"");
  XCTAssertTrue(14927 == encodeZigZag64(decodeZigZag64(14927)), @"");
  XCTAssertTrue(-3612 == encodeZigZag64(decodeZigZag64(-3612)), @"");

  XCTAssertTrue(856912304801416LL == encodeZigZag64(decodeZigZag64(856912304801416LL)), @"");
  XCTAssertTrue(-75123905439571256LL == encodeZigZag64(decodeZigZag64(-75123905439571256LL)), @"");
}


/** Tests writing a whole message with every field type. */

- (void) testWriteWholeMessage {
    TestAllTypes* message = [TestUtilities allSet];
    
    NSData* rawBytes = message.data;
    NSData* goldenData = [TestUtilities goldenData];
    NSAssert(goldenData != nil, @"Golden data must be present");
    XCTAssertEqualObjects(rawBytes, goldenData, @"");
    
    // Try different block sizes.
    for (int blockSize = 1; blockSize < 256; blockSize *= 2) {
        NSOutputStream* rawOutput = [self openMemoryStream];
        PBCodedOutputStream* output = [PBCodedOutputStream streamWithOutputStream:rawOutput bufferSize:blockSize];
        [message writeToCodedOutputStream:output];
        [output flush];
        
        NSData* actual = [rawOutput propertyForKey:NSStreamDataWrittenToMemoryStreamKey];
        XCTAssertEqualObjects(rawBytes, actual, @"");
    }
}

@end
