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

#import "GeneratedMessageTests.h"

#import "TestUtilities.h"
#import "Unittest.pb.h"

@implementation GeneratedMessageTests

- (void) testDefaultInstance {
  XCTAssertTrue([TestAllTypes defaultInstance] ==
               [[TestAllTypes defaultInstance] defaultInstance], @"");
  XCTAssertTrue([TestAllTypes defaultInstance] ==
               [[TestAllTypes builder] defaultInstance], @"");
}


- (void) testAccessors {
  TestAllTypesBuilder* builder = [TestAllTypes builder];
  [TestUtilities setAllFields:builder];
  TestAllTypes* message = [builder build];
  [TestUtilities assertAllFieldsSet:message];
}


- (void) testRepeatedAppend {
  TestAllTypesBuilder* builder = [TestAllTypes builder];

  NSArray* array =
  [NSArray arrayWithObjects:
   [NSNumber numberWithInteger:1],
   [NSNumber numberWithInteger:2],
   [NSNumber numberWithInteger:3],
   [NSNumber numberWithInteger:4], nil];

  [builder setRepeatedInt32Array:array];
  [builder setRepeatedForeignEnumArray:
   [NSArray arrayWithObject:
    [NSNumber numberWithInteger:ForeignEnumForeignBaz]]];

  ForeignMessage* foreignMessage = [[[ForeignMessage builder] setC:12] build];
  [builder setRepeatedForeignMessageArray:[NSArray arrayWithObject:foreignMessage]];

  TestAllTypes* message = [builder build];
  XCTAssertTrue(1 == message.repeatedForeignMessage.count, @"");
  XCTAssertTrue(12 == [[message repeatedForeignMessageAtIndex:0] c], @"");
}


- (void) testClearExtension {
  // clearExtension() is not actually used in TestUtil, so try it manually.
  PBExtendableMessageBuilder* builder1 =
  [[TestAllExtensions builder]
   setExtension:[UnittestRoot optionalInt32Extension] value:[NSNumber numberWithInteger:1]];

  XCTAssertTrue([builder1 hasExtension:[UnittestRoot optionalInt32Extension]], @"");
  [builder1 clearExtension:[UnittestRoot optionalInt32Extension]];
  XCTAssertFalse([builder1 hasExtension:[UnittestRoot optionalInt32Extension]], @"");

  PBExtendableMessageBuilder* builder2 =
  [[TestAllExtensions builder]
   addExtension:[UnittestRoot repeatedInt32Extension] value:[NSNumber numberWithInteger:1]];

  XCTAssertTrue(1 == [[builder2 getExtension:[UnittestRoot repeatedInt32Extension]] count], @"");
  [builder2 clearExtension:[UnittestRoot repeatedInt32Extension]];
  XCTAssertTrue(0 == [[builder2 getExtension:[UnittestRoot repeatedInt32Extension]] count], @"");
}


- (void) testExtensionAccessors {
  TestAllExtensionsBuilder* builder = [TestAllExtensions builder];
  [TestUtilities setAllExtensions:builder];
  TestAllExtensions* message = [builder build];
  [TestUtilities assertAllExtensionsSet:message];
}


- (void) testExtensionRepeatedSetters {
  TestAllExtensionsBuilder* builder = [TestAllExtensions builder];
  [TestUtilities setAllExtensions:builder];
  [TestUtilities modifyRepeatedExtensions:builder];
  TestAllExtensions* message = [builder build];
  [TestUtilities assertRepeatedExtensionsModified:message];
}


- (void) testExtensionDefaults {
  [TestUtilities assertExtensionsClear:[TestAllExtensions defaultInstance]];
  [TestUtilities assertExtensionsClear:[[TestAllExtensions builder] build]];
}

@end
