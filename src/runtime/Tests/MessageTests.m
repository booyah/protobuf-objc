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

  STAssertEqualObjects(result.data, self.mergeResult.data, @"");
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
  TestRequired_Builder* builder = [TestRequired builder];

  STAssertFalse(builder.isInitialized, @"");
  [builder setA:1];
  STAssertFalse(builder.isInitialized, @"");
  [builder setB:1];
  STAssertFalse(builder.isInitialized, @"");
  [builder setC:1];
  STAssertTrue(builder.isInitialized, @"");
}


- (void) testRequiredForeign {
  TestRequiredForeign_Builder* builder = [TestRequiredForeign builder];

  STAssertTrue(builder.isInitialized, @"");

  [builder setOptionalMessage:self.testRequiredUninitialized];
  STAssertFalse(builder.isInitialized, @"");

  [builder setOptionalMessage:self.testRequiredInitialized];
  STAssertTrue(builder.isInitialized, @"");

  [builder addRepeatedMessage:self.testRequiredUninitialized];
  STAssertFalse(builder.isInitialized, @"");
}


- (void) testRequiredExtension {
  TestAllExtensions_Builder* builder = [TestAllExtensions builder];

  STAssertTrue(builder.isInitialized, @"");

  [builder setExtension:[TestRequired single] value:self.testRequiredUninitialized];
  STAssertFalse(builder.isInitialized, @"");

  [builder setExtension:[TestRequired single] value:self.testRequiredInitialized];
  STAssertTrue(builder.isInitialized, @"");

  [builder addExtension:[TestRequired multi] value:self.testRequiredUninitialized];
  STAssertFalse(builder.isInitialized, @"");

  [builder setExtension:[TestRequired multi] index:0 value:self.testRequiredInitialized];
  STAssertTrue(builder.isInitialized, @"");
}


- (void) testUninitializedException {
  STAssertThrows([[TestRequired builder] build], @"");
}


- (void) testBuildPartial {
  // We're mostly testing that no exception is thrown.
  TestRequired* message = [[TestRequired builder] buildPartial];
  STAssertFalse(message.isInitialized, @"");
}


- (void) testNestedUninitializedException {
  STAssertThrows([[[[[TestRequiredForeign builder]
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

  STAssertFalse(message.isInitialized, @"");
}


- (void) testParseUnititialized {
  STAssertThrows([TestRequired parseFromData:[NSData data]], @"");
}


- (void) testParseNestedUnititialized {
  TestRequiredForeign* message =
  [[[[[TestRequiredForeign builder]
      setOptionalMessage:self.testRequiredUninitialized]
     addRepeatedMessage:self.testRequiredUninitialized]
    addRepeatedMessage:self.testRequiredUninitialized]
   buildPartial];

  NSData* data = message.data;

  STAssertThrows([TestRequiredForeign parseFromData:data], @"");
}

@end
