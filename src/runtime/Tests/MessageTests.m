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

#import "MessageTests.h"

#import "Unittest.pb.h"

@implementation MessageTests

- (TestAllTypes*) mergeSource {
  return [[[[[[TestAllTypes builder]
              setOptionalInt32:1]
             setOptionalString:@"foo"]
            setOptionalForeignMessage:[ForeignMessage defaultInstance]]
           addRepeatedString:@"bar"]
          build];
}


- (TestAllTypes*) mergeDestination {
  return [[[[[[TestAllTypes builder]
              setOptionalInt64:2]
             setOptionalString:@"baz"]
            setOptionalForeignMessage:[[[ForeignMessage builder] setC:3] build]]
           addRepeatedString:@"qux"]
          build];
}


- (TestAllTypes*) mergeResult {
  return [[[[[[[[TestAllTypes builder]
                setOptionalInt32:1]
               setOptionalInt64:2]
              setOptionalString:@"foo"]
             setOptionalForeignMessage:[[[ForeignMessage builder] setC:3] build]]
            addRepeatedString:@"qux"]
           addRepeatedString:@"bar"]
          build];
}


- (void) testMergeFrom {
  TestAllTypes* result =
  [[[TestAllTypes builderWithPrototype:self.mergeDestination]
    mergeFrom:self.mergeSource] build];

  XCTAssertEqualObjects(result.data, self.mergeResult.data, @"");
}

// =================================================================
// Required-field-related tests.

- (TestRequired*) testRequiredUninitialized {
  return [TestRequired defaultInstance];
}


- (TestRequired*) testRequiredInitialized {
  return [[[[[TestRequired builder] setA:1] setB:2] setC:3] build];
}


- (void) testRequired {
  TestRequiredBuilder* builder = [TestRequired builder];

  XCTAssertFalse(builder.isInitialized, @"");
  [builder setA:1];
  XCTAssertFalse(builder.isInitialized, @"");
  [builder setB:1];
  XCTAssertFalse(builder.isInitialized, @"");
  [builder setC:1];
  XCTAssertTrue(builder.isInitialized, @"");
}


- (void) testRequiredForeign {
  TestRequiredForeignBuilder* builder = [TestRequiredForeign builder];

  XCTAssertTrue(builder.isInitialized, @"");

  [builder setOptionalMessage:self.testRequiredUninitialized];
  XCTAssertFalse(builder.isInitialized, @"");

  [builder setOptionalMessage:self.testRequiredInitialized];
  XCTAssertTrue(builder.isInitialized, @"");

  [builder addRepeatedMessage:self.testRequiredUninitialized];
  XCTAssertFalse(builder.isInitialized, @"");
}


- (void) testRequiredExtension {
  TestAllExtensionsBuilder* builder = [TestAllExtensions builder];

  XCTAssertTrue(builder.isInitialized, @"");

  [builder setExtension:[TestRequired single] value:self.testRequiredUninitialized];
  XCTAssertFalse(builder.isInitialized, @"");

  [builder setExtension:[TestRequired single] value:self.testRequiredInitialized];
  XCTAssertTrue(builder.isInitialized, @"");

  [builder addExtension:[TestRequired multi] value:self.testRequiredUninitialized];
  XCTAssertFalse(builder.isInitialized, @"");

  [builder setExtension:[TestRequired multi] index:0 value:self.testRequiredInitialized];
  XCTAssertTrue(builder.isInitialized, @"");
}


- (void) testUninitializedException {
  XCTAssertThrows([[TestRequired builder] build], @"");
}


- (void) testBuildPartial {
  // We're mostly testing that no exception is thrown.
  TestRequired* message = [[TestRequired builder] buildPartial];
  XCTAssertFalse(message.isInitialized, @"");
}


- (void) testNestedUninitializedException {
  XCTAssertThrows([[[[[TestRequiredForeign builder]
                     setOptionalMessage:self.testRequiredUninitialized]
                    addRepeatedMessage:self.testRequiredUninitialized]
                   addRepeatedMessage:self.testRequiredUninitialized]
                  build], @"");
}


- (void) testBuildNestedPartial {
  // We're mostly testing that no exception is thrown.

  TestRequiredForeign* message =
  [[[[[TestRequiredForeign builder]
      setOptionalMessage:self.testRequiredUninitialized]
     addRepeatedMessage:self.testRequiredUninitialized]
    addRepeatedMessage:self.testRequiredUninitialized]
   buildPartial];

  XCTAssertFalse(message.isInitialized, @"");
}


- (void) testParseUnititialized {
  XCTAssertThrows([TestRequired parseFromData:[NSData data]], @"");
}


- (void) testParseNestedUnititialized {
  TestRequiredForeign* message =
  [[[[[TestRequiredForeign builder]
      setOptionalMessage:self.testRequiredUninitialized]
     addRepeatedMessage:self.testRequiredUninitialized]
    addRepeatedMessage:self.testRequiredUninitialized]
   buildPartial];

  NSData* data = message.data;

  XCTAssertThrows([TestRequiredForeign parseFromData:data], @"");
}

@end
