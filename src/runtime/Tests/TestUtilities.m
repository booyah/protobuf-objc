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

#import "TestUtilities.h"
#import "ProtocolBuffers.h"
#import "Unittest.pb.h"

@implementation TestUtilities

+ (NSData*) getData:(NSString*) str {
  return [str dataUsingEncoding:NSUTF8StringEncoding];
}


+ (NSData*) goldenData {
  
  NSString *str = [[[NSBundle bundleForClass:[self class]] resourcePath] stringByAppendingPathComponent:@"golden_message"];
  NSData* goldenData = [NSData dataWithContentsOfFile:str];
  return goldenData;
}


+ (NSData*) goldenPackedFieldsData {
  NSString* path = [[NSBundle mainBundle] pathForResource:@"golden_packed_fields_message" ofType:nil];
  if (path == nil) {
    path = @"golden_packed_fields_message";
  }
  NSData* goldenData = [NSData dataWithContentsOfFile:path];
  return goldenData;
}


- (void) failWithException:(NSException *) anException {
  @throw anException;
}


// -------------------------------------------------------------------

/**
 * Modify the repeated extensions of {@code message} to contain the values
 * expected by {@code assertRepeatedExtensionsModified()}.
 */
+ (void) modifyRepeatedExtensions:(TestAllExtensionsBuilder*) message {
  [message setExtension:[UnittestRoot repeatedInt32Extension] index:1 value:[NSNumber numberWithInteger:501]];
  [message setExtension:[UnittestRoot repeatedInt64Extension] index:1 value:[NSNumber numberWithInteger:502]];
  [message setExtension:[UnittestRoot repeatedUint32Extension] index:1 value:[NSNumber numberWithInteger:503]];
  [message setExtension:[UnittestRoot repeatedUint64Extension] index:1 value:[NSNumber numberWithInteger:504]];
  [message setExtension:[UnittestRoot repeatedSint32Extension] index:1 value:[NSNumber numberWithInteger:505]];
  [message setExtension:[UnittestRoot repeatedSint64Extension] index:1 value:[NSNumber numberWithInteger:506]];
  [message setExtension:[UnittestRoot repeatedFixed32Extension] index:1 value:[NSNumber numberWithInteger:507]];
  [message setExtension:[UnittestRoot repeatedFixed64Extension] index:1 value:[NSNumber numberWithInteger:508]];
  [message setExtension:[UnittestRoot repeatedSfixed32Extension] index:1 value:[NSNumber numberWithInteger:509]];
  [message setExtension:[UnittestRoot repeatedSfixed64Extension] index:1 value:[NSNumber numberWithInteger:510]];
  [message setExtension:[UnittestRoot repeatedFloatExtension] index:1 value:[NSNumber numberWithFloat:511.0]];
  [message setExtension:[UnittestRoot repeatedDoubleExtension] index:1 value:[NSNumber numberWithDouble:512.0]];
  [message setExtension:[UnittestRoot repeatedBoolExtension] index:1 value:[NSNumber numberWithBool:YES]];
  [message setExtension:[UnittestRoot repeatedStringExtension] index:1 value:@"515"];
  [message setExtension:[UnittestRoot repeatedBytesExtension] index:1 value:[TestUtilities getData:@"516"]];

  [message setExtension:[UnittestRoot repeatedGroupExtension] index:1 value:
   [[[RepeatedGroup_extension builder] setA:517] build]];
  [message setExtension:[UnittestRoot repeatedNestedMessageExtension] index:1 value:
   [[[TestAllTypesNestedMessage builder] setBb:518] build]];
  [message setExtension:[UnittestRoot repeatedForeignMessageExtension] index:1 value:
   [[[ForeignMessage builder] setC:519] build]];
  [message setExtension:[UnittestRoot repeatedImportMessageExtension] index:1 value:
   [[[ImportMessage builder] setD:520] build]];

  [message setExtension:[UnittestRoot repeatedNestedEnumExtension] index:1 value:
   [NSNumber numberWithInteger:TestAllTypesNestedEnumFoo]];
  [message setExtension:[UnittestRoot repeatedForeignEnumExtension] index:1 value:
   [NSNumber numberWithInteger:ForeignEnumForeignFoo]];
  [message setExtension:[UnittestRoot repeatedImportEnumExtension] index:1 value:
   [NSNumber numberWithInteger:ImportEnumImportFoo]];

  [message setExtension:[UnittestRoot repeatedStringPieceExtension] index:1 value:@"524"];
  [message setExtension:[UnittestRoot repeatedCordExtension] index:1 value:@"525"];
}



/**
 * Assert (using {@code junit.framework.Assert}} that all extensions of
 * {@code message} are set to the values assigned by {@code setAllExtensions}.
 */
- (void) assertAllExtensionsSet:(TestAllExtensions*) message {
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalInt32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalInt64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalUint32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalUint64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalSint32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalSint64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalFixed32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalFixed64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalSfixed32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalSfixed64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalFloatExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalDoubleExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalBoolExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalStringExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalBytesExtension]], @"");

  XCTAssertTrue([message hasExtension:[UnittestRoot optionalGroupExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalNestedMessageExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalForeignMessageExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalImportMessageExtension]], @"");

  XCTAssertTrue([[message getExtension:[UnittestRoot optionalGroupExtension]] hasA], @"");
  XCTAssertTrue([[message getExtension:[UnittestRoot optionalNestedMessageExtension]] hasBb], @"");
  XCTAssertTrue([[message getExtension:[UnittestRoot optionalForeignMessageExtension]] hasC], @"");
  XCTAssertTrue([[message getExtension:[UnittestRoot optionalImportMessageExtension]] hasD], @"");

  XCTAssertTrue([message hasExtension:[UnittestRoot optionalNestedEnumExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalForeignEnumExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalImportEnumExtension]], @"");

  XCTAssertTrue([message hasExtension:[UnittestRoot optionalStringPieceExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot optionalCordExtension]], @"");

  XCTAssertTrue(101 == [[message getExtension:[UnittestRoot optionalInt32Extension]] integerValue], @"");
  XCTAssertTrue(102L == [[message getExtension:[UnittestRoot optionalInt64Extension]] integerValue], @"");
  XCTAssertTrue(103 == [[message getExtension:[UnittestRoot optionalUint32Extension]] integerValue], @"");
  XCTAssertTrue(104L == [[message getExtension:[UnittestRoot optionalUint64Extension]] integerValue], @"");
  XCTAssertTrue(105 == [[message getExtension:[UnittestRoot optionalSint32Extension]] integerValue], @"");
  XCTAssertTrue(106L == [[message getExtension:[UnittestRoot optionalSint64Extension]] integerValue], @"");
  XCTAssertTrue(107 == [[message getExtension:[UnittestRoot optionalFixed32Extension]] integerValue], @"");
  XCTAssertTrue(108L == [[message getExtension:[UnittestRoot optionalFixed64Extension]] integerValue], @"");
  XCTAssertTrue(109 == [[message getExtension:[UnittestRoot optionalSfixed32Extension]] integerValue], @"");
  XCTAssertTrue(110L == [[message getExtension:[UnittestRoot optionalSfixed64Extension]] integerValue], @"");
  XCTAssertTrue(111.0 == [[message getExtension:[UnittestRoot optionalFloatExtension]] floatValue], @"");
  XCTAssertTrue(112.0 == [[message getExtension:[UnittestRoot optionalDoubleExtension]] doubleValue], @"");
  XCTAssertTrue(YES == [[message getExtension:[UnittestRoot optionalBoolExtension]] boolValue], @"");
  XCTAssertEqualObjects(@"115", [message getExtension:[UnittestRoot optionalStringExtension]], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"116"], [message getExtension:[UnittestRoot optionalBytesExtension]], @"");

  XCTAssertTrue(117 == [(OptionalGroup_extension *)[message getExtension:[UnittestRoot optionalGroupExtension]] a], @"");
  XCTAssertTrue(118 == [(TestAllTypesNestedMessage *)[message getExtension:[UnittestRoot optionalNestedMessageExtension]] bb], @"");
  XCTAssertTrue(119 == [[message getExtension:[UnittestRoot optionalForeignMessageExtension]] c], @"");
  XCTAssertTrue(120 == [[message getExtension:[UnittestRoot optionalImportMessageExtension]] d], @"");

  XCTAssertTrue(TestAllTypesNestedEnumBaz == [[message getExtension:[UnittestRoot optionalNestedEnumExtension]] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignBaz == [[message getExtension:[UnittestRoot optionalForeignEnumExtension]] integerValue], @"");
  XCTAssertTrue(ImportEnumImportBaz == [[message getExtension:[UnittestRoot optionalImportEnumExtension]] integerValue], @"");

  XCTAssertEqualObjects(@"124", [message getExtension:[UnittestRoot optionalStringPieceExtension]], @"");
  XCTAssertEqualObjects(@"125", [message getExtension:[UnittestRoot optionalCordExtension]], @"");

  // -----------------------------------------------------------------

  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedInt32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedInt64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedUint32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedUint64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSint32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSint64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedFixed32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedFixed64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSfixed32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSfixed64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedFloatExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedDoubleExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedBoolExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedStringExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedBytesExtension]] count], @"");

  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedGroupExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedNestedMessageExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedForeignMessageExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedImportMessageExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedNestedEnumExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedForeignEnumExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedImportEnumExtension]] count], @"");

  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedStringPieceExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedCordExtension]] count], @"");

  XCTAssertTrue(201 == [[[message getExtension:[UnittestRoot repeatedInt32Extension]] objectAtIndex:0] integerValue], @"");;
  XCTAssertTrue(202L == [[[message getExtension:[UnittestRoot repeatedInt64Extension]] objectAtIndex:0] integerValue], @"");;
  XCTAssertTrue(203 == [[[message getExtension:[UnittestRoot repeatedUint32Extension]] objectAtIndex:0] integerValue], @"");;
  XCTAssertTrue(204L == [[[message getExtension:[UnittestRoot repeatedUint64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(205 == [[[message getExtension:[UnittestRoot repeatedSint32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(206L == [[[message getExtension:[UnittestRoot repeatedSint64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(207 == [[[message getExtension:[UnittestRoot repeatedFixed32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(208L == [[[message getExtension:[UnittestRoot repeatedFixed64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(209 == [[[message getExtension:[UnittestRoot repeatedSfixed32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(210L == [[[message getExtension:[UnittestRoot repeatedSfixed64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(211.0 == [[[message getExtension:[UnittestRoot repeatedFloatExtension]] objectAtIndex:0] floatValue], @"");
  XCTAssertTrue(212.0 == [[[message getExtension:[UnittestRoot repeatedDoubleExtension]] objectAtIndex:0] doubleValue], @"");
  XCTAssertTrue(YES == [[[message getExtension:[UnittestRoot repeatedBoolExtension]] objectAtIndex:0] boolValue], @"");
  XCTAssertEqualObjects(@"215", [[message getExtension:[UnittestRoot repeatedStringExtension]] objectAtIndex:0], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"216"], [[message getExtension:[UnittestRoot repeatedBytesExtension]] objectAtIndex:0], @"");

  XCTAssertTrue(217 == [(RepeatedGroup_extension *)[[message getExtension:[UnittestRoot repeatedGroupExtension]] objectAtIndex:0] a], @"");
  XCTAssertTrue(218 == [(TestAllTypesNestedMessage *)[[message getExtension:[UnittestRoot repeatedNestedMessageExtension]] objectAtIndex:0] bb], @"");
  XCTAssertTrue(219 == [[[message getExtension:[UnittestRoot repeatedForeignMessageExtension]] objectAtIndex:0] c], @"");
  XCTAssertTrue(220 == [[[message getExtension:[UnittestRoot repeatedImportMessageExtension]] objectAtIndex:0] d], @"");

  XCTAssertTrue(TestAllTypesNestedEnumBar == [[[message getExtension:[UnittestRoot repeatedNestedEnumExtension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignBar == [[[message getExtension:[UnittestRoot repeatedForeignEnumExtension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(ImportEnumImportBar == [[[message getExtension:[UnittestRoot repeatedImportEnumExtension]] objectAtIndex:0] integerValue], @"");

  XCTAssertEqualObjects(@"224", [[message getExtension:[UnittestRoot repeatedStringPieceExtension]] objectAtIndex:0], @"");
  XCTAssertEqualObjects(@"225", [[message getExtension:[UnittestRoot repeatedCordExtension]] objectAtIndex:0], @"");

  XCTAssertTrue(301 == [[[message getExtension:[UnittestRoot repeatedInt32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(302L == [[[message getExtension:[UnittestRoot repeatedInt64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(303 == [[[message getExtension:[UnittestRoot repeatedUint32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(304L == [[[message getExtension:[UnittestRoot repeatedUint64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(305 == [[[message getExtension:[UnittestRoot repeatedSint32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(306L == [[[message getExtension:[UnittestRoot repeatedSint64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(307 == [[[message getExtension:[UnittestRoot repeatedFixed32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(308L == [[[message getExtension:[UnittestRoot repeatedFixed64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(309 == [[[message getExtension:[UnittestRoot repeatedSfixed32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(310L == [[[message getExtension:[UnittestRoot repeatedSfixed64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(311.0 == [[[message getExtension:[UnittestRoot repeatedFloatExtension]] objectAtIndex:1] floatValue], @"");
  XCTAssertTrue(312.0 == [[[message getExtension:[UnittestRoot repeatedDoubleExtension]] objectAtIndex:1] doubleValue], @"");
  XCTAssertTrue(NO == [[[message getExtension:[UnittestRoot repeatedBoolExtension]] objectAtIndex:1] boolValue], @"");
  XCTAssertEqualObjects(@"315", [[message getExtension:[UnittestRoot repeatedStringExtension]] objectAtIndex:1], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"316"], [[message getExtension:[UnittestRoot repeatedBytesExtension]] objectAtIndex:1], @"");

  XCTAssertTrue(317 == [(RepeatedGroup_extension *)[[message getExtension:[UnittestRoot repeatedGroupExtension]] objectAtIndex:1] a], @"");
  XCTAssertTrue(318 == [(TestAllTypesNestedMessage *)[[message getExtension:[UnittestRoot repeatedNestedMessageExtension]] objectAtIndex:1] bb], @"");
  XCTAssertTrue(319 == [[[message getExtension:[UnittestRoot repeatedForeignMessageExtension]] objectAtIndex:1] c], @"");
  XCTAssertTrue(320 == [[[message getExtension:[UnittestRoot repeatedImportMessageExtension]] objectAtIndex:1] d], @"");

  XCTAssertTrue(TestAllTypesNestedEnumBaz == [[[message getExtension:[UnittestRoot repeatedNestedEnumExtension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignBaz == [[[message getExtension:[UnittestRoot repeatedForeignEnumExtension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(ImportEnumImportBaz == [[[message getExtension:[UnittestRoot repeatedImportEnumExtension]] objectAtIndex:1] integerValue], @"");

  XCTAssertEqualObjects(@"324", [[message getExtension:[UnittestRoot repeatedStringPieceExtension]] objectAtIndex:1], @"");
  XCTAssertEqualObjects(@"325", [[message getExtension:[UnittestRoot repeatedCordExtension]] objectAtIndex:1], @"");

  // -----------------------------------------------------------------

  XCTAssertTrue([message hasExtension:[UnittestRoot defaultInt32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultInt64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultUint32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultUint64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultSint32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultSint64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultFixed32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultFixed64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultSfixed32Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultSfixed64Extension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultFloatExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultDoubleExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultBoolExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultStringExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultBytesExtension]], @"");

  XCTAssertTrue([message hasExtension:[UnittestRoot defaultNestedEnumExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultForeignEnumExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultImportEnumExtension]], @"");

  XCTAssertTrue([message hasExtension:[UnittestRoot defaultStringPieceExtension]], @"");
  XCTAssertTrue([message hasExtension:[UnittestRoot defaultCordExtension]], @"");

  XCTAssertTrue(401 == [[message getExtension:[UnittestRoot defaultInt32Extension]] integerValue], @"");
  XCTAssertTrue(402L == [[message getExtension:[UnittestRoot defaultInt64Extension]] integerValue], @"");
  XCTAssertTrue(403 == [[message getExtension:[UnittestRoot defaultUint32Extension]] integerValue], @"");
  XCTAssertTrue(404L == [[message getExtension:[UnittestRoot defaultUint64Extension]] integerValue], @"");
  XCTAssertTrue(405 == [[message getExtension:[UnittestRoot defaultSint32Extension]] integerValue], @"");
  XCTAssertTrue(406L == [[message getExtension:[UnittestRoot defaultSint64Extension]] integerValue], @"");
  XCTAssertTrue(407 == [[message getExtension:[UnittestRoot defaultFixed32Extension]] integerValue], @"");
  XCTAssertTrue(408L == [[message getExtension:[UnittestRoot defaultFixed64Extension]] integerValue], @"");
  XCTAssertTrue(409 == [[message getExtension:[UnittestRoot defaultSfixed32Extension]] integerValue], @"");
  XCTAssertTrue(410L == [[message getExtension:[UnittestRoot defaultSfixed64Extension]] integerValue], @"");
  XCTAssertTrue(411.0 == [[message getExtension:[UnittestRoot defaultFloatExtension]] floatValue], @"");
  XCTAssertTrue(412.0 == [[message getExtension:[UnittestRoot defaultDoubleExtension]] doubleValue], @"");
  XCTAssertTrue(NO == [[message getExtension:[UnittestRoot defaultBoolExtension]] boolValue], @"");
  XCTAssertEqualObjects(@"415", [message getExtension:[UnittestRoot defaultStringExtension]], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"416"], [message getExtension:[UnittestRoot defaultBytesExtension]], @"");

  XCTAssertTrue(TestAllTypesNestedEnumFoo == [[message getExtension:[UnittestRoot defaultNestedEnumExtension]] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignFoo == [[message getExtension:[UnittestRoot defaultForeignEnumExtension]] integerValue], @"");
  XCTAssertTrue(ImportEnumImportFoo == [[message getExtension:[UnittestRoot defaultImportEnumExtension]] integerValue], @"");

  XCTAssertEqualObjects(@"424", [message getExtension:[UnittestRoot defaultStringPieceExtension]], @"");
  XCTAssertEqualObjects(@"425", [message getExtension:[UnittestRoot defaultCordExtension]], @"");
}

+ (void) assertAllExtensionsSet:(TestAllExtensions*) message {
  return [[[TestUtilities alloc] init] assertAllExtensionsSet:message];
}


- (void) assertRepeatedExtensionsModified:(TestAllExtensions*) message {
  // ModifyRepeatedFields only sets the second repeated element of each
  // field.  In addition to verifying this, we also verify that the first
  // element and size were *not* modified.
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedInt32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedInt64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedUint32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedUint64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSint32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSint64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedFixed32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedFixed64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSfixed32Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedSfixed64Extension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedFloatExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedDoubleExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedBoolExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedStringExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedBytesExtension]] count], @"");

  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedGroupExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedNestedMessageExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedForeignMessageExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedImportMessageExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedNestedEnumExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedForeignEnumExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedImportEnumExtension]] count], @"");

  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedStringPieceExtension]] count], @"");
  XCTAssertTrue(2 == [[message getExtension:[UnittestRoot repeatedCordExtension]] count], @"");

  XCTAssertTrue(201  == [[[message getExtension:[UnittestRoot repeatedInt32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(202L == [[[message getExtension:[UnittestRoot repeatedInt64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(203  == [[[message getExtension:[UnittestRoot repeatedUint32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(204L == [[[message getExtension:[UnittestRoot repeatedUint64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(205  == [[[message getExtension:[UnittestRoot repeatedSint32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(206L == [[[message getExtension:[UnittestRoot repeatedSint64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(207  == [[[message getExtension:[UnittestRoot repeatedFixed32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(208L == [[[message getExtension:[UnittestRoot repeatedFixed64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(209  == [[[message getExtension:[UnittestRoot repeatedSfixed32Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(210L == [[[message getExtension:[UnittestRoot repeatedSfixed64Extension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(211.0 == [[[message getExtension:[UnittestRoot repeatedFloatExtension]] objectAtIndex:0] floatValue], @"");
  XCTAssertTrue(212.0 == [[[message getExtension:[UnittestRoot repeatedDoubleExtension]] objectAtIndex:0] doubleValue], @"");
  XCTAssertTrue(YES == [[[message getExtension:[UnittestRoot repeatedBoolExtension]] objectAtIndex:0] boolValue], @"");
  XCTAssertEqualObjects(@"215", [[message getExtension:[UnittestRoot repeatedStringExtension]] objectAtIndex:0], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"216"], [[message getExtension:[UnittestRoot repeatedBytesExtension]] objectAtIndex:0], @"");

  XCTAssertTrue(217 == [(RepeatedGroup_extension *)[[message getExtension:[UnittestRoot repeatedGroupExtension]] objectAtIndex:0] a], @"");
  XCTAssertTrue(218 == [(TestAllTypesNestedMessage *)[[message getExtension:[UnittestRoot repeatedNestedMessageExtension]] objectAtIndex:0] bb], @"");
  XCTAssertTrue(219 == [[[message getExtension:[UnittestRoot repeatedForeignMessageExtension]] objectAtIndex:0] c], @"");
  XCTAssertTrue(220 == [[[message getExtension:[UnittestRoot repeatedImportMessageExtension]] objectAtIndex:0] d], @"");

  XCTAssertTrue(TestAllTypesNestedEnumBar ==
               [[[message getExtension:[UnittestRoot repeatedNestedEnumExtension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignBar ==
               [[[message getExtension:[UnittestRoot repeatedForeignEnumExtension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(ImportEnumImportBar ==
               [[[message getExtension:[UnittestRoot repeatedImportEnumExtension]] objectAtIndex:0] integerValue], @"");

  XCTAssertEqualObjects(@"224", [[message getExtension:[UnittestRoot repeatedStringPieceExtension]] objectAtIndex:0], @"");
  XCTAssertEqualObjects(@"225", [[message getExtension:[UnittestRoot repeatedCordExtension]] objectAtIndex:0], @"");

  // Actually verify the second (modified) elements now.
  XCTAssertTrue(501  == [[[message getExtension:[UnittestRoot repeatedInt32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(502L == [[[message getExtension:[UnittestRoot repeatedInt64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(503  == [[[message getExtension:[UnittestRoot repeatedUint32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(504L == [[[message getExtension:[UnittestRoot repeatedUint64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(505  == [[[message getExtension:[UnittestRoot repeatedSint32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(506L == [[[message getExtension:[UnittestRoot repeatedSint64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(507  == [[[message getExtension:[UnittestRoot repeatedFixed32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(508L == [[[message getExtension:[UnittestRoot repeatedFixed64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(509  == [[[message getExtension:[UnittestRoot repeatedSfixed32Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(510L == [[[message getExtension:[UnittestRoot repeatedSfixed64Extension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(511.0 == [[[message getExtension:[UnittestRoot repeatedFloatExtension]] objectAtIndex:1] floatValue], @"");
  XCTAssertTrue(512.0 == [[[message getExtension:[UnittestRoot repeatedDoubleExtension]] objectAtIndex:1] doubleValue], @"");
  XCTAssertTrue(YES == [[[message getExtension:[UnittestRoot repeatedBoolExtension]] objectAtIndex:1] boolValue], @"");
  XCTAssertEqualObjects(@"515", [[message getExtension:[UnittestRoot repeatedStringExtension]] objectAtIndex:1], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"516"], [[message getExtension:[UnittestRoot repeatedBytesExtension]] objectAtIndex:1], @"");

  XCTAssertTrue(517 == [(RepeatedGroup_extension *)[[message getExtension:[UnittestRoot repeatedGroupExtension]] objectAtIndex:1] a], @"");
  XCTAssertTrue(518 == [(TestAllTypesNestedMessage *)[[message getExtension:[UnittestRoot repeatedNestedMessageExtension]] objectAtIndex:1] bb], @"");
  XCTAssertTrue(519 == [[[message getExtension:[UnittestRoot repeatedForeignMessageExtension]] objectAtIndex:1] c], @"");
  XCTAssertTrue(520 == [[[message getExtension:[UnittestRoot repeatedImportMessageExtension]] objectAtIndex:1] d], @"");

  XCTAssertTrue(TestAllTypesNestedEnumFoo ==
               [[[message getExtension:[UnittestRoot repeatedNestedEnumExtension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignFoo ==
               [[[message getExtension:[UnittestRoot repeatedForeignEnumExtension]] objectAtIndex:1] integerValue], @"");
  XCTAssertTrue(ImportEnumImportFoo ==
               [[[message getExtension:[UnittestRoot repeatedImportEnumExtension]] objectAtIndex:1] integerValue], @"");

  XCTAssertEqualObjects(@"524", [[message getExtension:[UnittestRoot repeatedStringPieceExtension]] objectAtIndex:1], @"");
  XCTAssertEqualObjects(@"525", [[message getExtension:[UnittestRoot repeatedCordExtension]] objectAtIndex:1], @"");
}


+ (void) assertRepeatedExtensionsModified:(TestAllExtensions*) message {
  [[[TestUtilities alloc] init] assertRepeatedExtensionsModified:message];
}


// -------------------------------------------------------------------

/**
 * Assert (using {@code junit.framework.Assert}} that all fields of
 * {@code message} are set to the values assigned by {@code setAllFields}.
 */
- (void) assertAllFieldsSet:(TestAllTypes*) message {

  XCTAssertTrue(message.hasOptionalInt32, @"");
  XCTAssertTrue(message.hasOptionalInt64, @"");
  XCTAssertTrue(message.hasOptionalUint32, @"");
  XCTAssertTrue(message.hasOptionalUint64, @"");
  XCTAssertTrue(message.hasOptionalSint32, @"");
  XCTAssertTrue(message.hasOptionalSint64, @"");
  XCTAssertTrue(message.hasOptionalFixed32, @"");
  XCTAssertTrue(message.hasOptionalFixed64, @"");
  XCTAssertTrue(message.hasOptionalSfixed32, @"");
  XCTAssertTrue(message.hasOptionalSfixed64, @"");
  XCTAssertTrue(message.hasOptionalFloat, @"");
  XCTAssertTrue(message.hasOptionalDouble, @"");
  XCTAssertTrue(message.hasOptionalBool, @"");
  XCTAssertTrue(message.hasOptionalString, @"");
  XCTAssertTrue(message.hasOptionalBytes, @"");

  XCTAssertTrue(message.hasOptionalGroup, @"");
  XCTAssertTrue(message.hasOptionalNestedMessage, @"");
  XCTAssertTrue(message.hasOptionalForeignMessage, @"");
  XCTAssertTrue(message.hasOptionalImportMessage, @"");

  XCTAssertTrue(message.optionalGroup.hasA, @"");
  XCTAssertTrue(message.optionalNestedMessage.hasBb, @"");
  XCTAssertTrue(message.optionalForeignMessage.hasC, @"");
  XCTAssertTrue(message.optionalImportMessage.hasD, @"");

  XCTAssertTrue(message.hasOptionalNestedEnum, @"");
  XCTAssertTrue(message.hasOptionalForeignEnum, @"");
  XCTAssertTrue(message.hasOptionalImportEnum, @"");

  XCTAssertTrue(message.hasOptionalStringPiece, @"");
  XCTAssertTrue(message.hasOptionalCord, @"");

  XCTAssertTrue(101 == message.optionalInt32, @"");
  XCTAssertTrue(102 == message.optionalInt64, @"");
  XCTAssertTrue(103 == message.optionalUint32, @"");
  XCTAssertTrue(104 == message.optionalUint64, @"");
  XCTAssertTrue(105 == message.optionalSint32, @"");
  XCTAssertTrue(106 == message.optionalSint64, @"");
  XCTAssertTrue(107 == message.optionalFixed32, @"");
  XCTAssertTrue(108 == message.optionalFixed64, @"");
  XCTAssertTrue(109 == message.optionalSfixed32, @"");
  XCTAssertTrue(110 == message.optionalSfixed64, @"");
  XCTAssertEqualWithAccuracy(111.0f, message.optionalFloat, 0.1, @"");
  XCTAssertEqualWithAccuracy(112.0, message.optionalDouble, 0.1, @"");
  XCTAssertTrue(YES == message.optionalBool, @"");
  XCTAssertEqualObjects(@"115", message.optionalString, @"");
  XCTAssertEqualObjects([TestUtilities getData:@"116"], message.optionalBytes, @"");

  XCTAssertTrue(117 == message.optionalGroup.a, @"");
  XCTAssertTrue(118 == message.optionalNestedMessage.bb, @"");
  XCTAssertTrue(119 == message.optionalForeignMessage.c, @"");
  XCTAssertTrue(120 == message.optionalImportMessage.d, @"");

  XCTAssertTrue(TestAllTypesNestedEnumBaz == message.optionalNestedEnum, @"");
  XCTAssertTrue(ForeignEnumForeignBaz == message.optionalForeignEnum, @"");
  XCTAssertTrue(ImportEnumImportBaz == message.optionalImportEnum, @"");

  XCTAssertEqualObjects(@"124", message.optionalStringPiece, @"");
  XCTAssertEqualObjects(@"125", message.optionalCord, @"");

  // -----------------------------------------------------------------

  XCTAssertTrue(2 == message.repeatedInt32.count, @"");
  XCTAssertTrue(2 == message.repeatedInt64.count, @"");
  XCTAssertTrue(2 == message.repeatedUint32.count, @"");
  XCTAssertTrue(2 == message.repeatedUint64.count, @"");
  XCTAssertTrue(2 == message.repeatedSint32.count, @"");
  XCTAssertTrue(2 == message.repeatedSint64.count, @"");
  XCTAssertTrue(2 == message.repeatedFixed32.count, @"");
  XCTAssertTrue(2 == message.repeatedFixed64.count, @"");
  XCTAssertTrue(2 == message.repeatedSfixed32.count, @"");
  XCTAssertTrue(2 == message.repeatedSfixed64.count, @"");
  XCTAssertTrue(2 == message.repeatedFloat.count, @"");
  XCTAssertTrue(2 == message.repeatedDouble.count, @"");
  XCTAssertTrue(2 == message.repeatedBool.count, @"");
  XCTAssertTrue(2 == message.repeatedString.count, @"");
  XCTAssertTrue(2 == message.repeatedBytes.count, @"");

  XCTAssertTrue(2 == message.repeatedGroup.count, @"");
  XCTAssertTrue(2 == message.repeatedNestedMessage.count, @"");
  XCTAssertTrue(2 == message.repeatedForeignMessage.count, @"");
  XCTAssertTrue(2 == message.repeatedImportMessage.count, @"");
  XCTAssertTrue(2 == message.repeatedNestedEnum.count, @"");
  XCTAssertTrue(2 == message.repeatedForeignEnum.count, @"");
  XCTAssertTrue(2 == message.repeatedImportEnum.count, @"");

  XCTAssertTrue(2 == message.repeatedStringPiece.count, @"");
  XCTAssertTrue(2 == message.repeatedCord.count, @"");

  XCTAssertTrue(201 == [message repeatedInt32AtIndex:0], @"");
  XCTAssertTrue(202 == [message repeatedInt64AtIndex:0], @"");
  XCTAssertTrue(203 == [message repeatedUint32AtIndex:0], @"");
  XCTAssertTrue(204 == [message repeatedUint64AtIndex:0], @"");
  XCTAssertTrue(205 == [message repeatedSint32AtIndex:0], @"");
  XCTAssertTrue(206 == [message repeatedSint64AtIndex:0], @"");
  XCTAssertTrue(207 == [message repeatedFixed32AtIndex:0], @"");
  XCTAssertTrue(208 == [message repeatedFixed64AtIndex:0], @"");
  XCTAssertTrue(209 == [message repeatedSfixed32AtIndex:0], @"");
  XCTAssertTrue(210 == [message repeatedSfixed64AtIndex:0], @"");
  XCTAssertEqualWithAccuracy(211.0f, [message repeatedFloatAtIndex:0], 0.1, @"");
  XCTAssertEqualWithAccuracy(212.0, [message repeatedDoubleAtIndex:0], 0.1, @"");
  XCTAssertTrue(YES == [message repeatedBoolAtIndex:0], @"");
  XCTAssertEqualObjects(@"215", [message repeatedStringAtIndex:0], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"216"], [message repeatedBytesAtIndex:0], @"");

  XCTAssertTrue(217 == [message repeatedGroupAtIndex:0].a, @"");
  XCTAssertTrue(218 == [message repeatedNestedMessageAtIndex:0].bb, @"");
  XCTAssertTrue(219 == [message repeatedForeignMessageAtIndex:0].c, @"");
  XCTAssertTrue(220 == [message repeatedImportMessageAtIndex:0].d, @"");

  XCTAssertTrue(TestAllTypesNestedEnumBar == [message repeatedNestedEnumAtIndex:0], @"");
  XCTAssertTrue(ForeignEnumForeignBar == [message repeatedForeignEnumAtIndex:0], @"");
  XCTAssertTrue(ImportEnumImportBar == [message repeatedImportEnumAtIndex:0], @"");

  XCTAssertEqualObjects(@"224", [message repeatedStringPieceAtIndex:0], @"");
  XCTAssertEqualObjects(@"225", [message repeatedCordAtIndex:0], @"");

  XCTAssertTrue(301 == [message repeatedInt32AtIndex:1], @"");
  XCTAssertTrue(302 == [message repeatedInt64AtIndex:1], @"");
  XCTAssertTrue(303 == [message repeatedUint32AtIndex:1], @"");
  XCTAssertTrue(304 == [message repeatedUint64AtIndex:1], @"");
  XCTAssertTrue(305 == [message repeatedSint32AtIndex:1], @"");
  XCTAssertTrue(306 == [message repeatedSint64AtIndex:1], @"");
  XCTAssertTrue(307 == [message repeatedFixed32AtIndex:1], @"");
  XCTAssertTrue(308 == [message repeatedFixed64AtIndex:1], @"");
  XCTAssertTrue(309 == [message repeatedSfixed32AtIndex:1], @"");
  XCTAssertTrue(310 == [message repeatedSfixed64AtIndex:1], @"");
  XCTAssertEqualWithAccuracy(311.0f, [message repeatedFloatAtIndex:1], 0.1, @"");
  XCTAssertEqualWithAccuracy(312.0, [message repeatedDoubleAtIndex:1], 0.1, @"");
  XCTAssertTrue(NO == [message repeatedBoolAtIndex:1], @"");
  XCTAssertEqualObjects(@"315", [message repeatedStringAtIndex:1], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"316"], [message repeatedBytesAtIndex:1], @"");

  XCTAssertTrue(317 == [message repeatedGroupAtIndex:1].a, @"");
  XCTAssertTrue(318 == [message repeatedNestedMessageAtIndex:1].bb, @"");
  XCTAssertTrue(319 == [message repeatedForeignMessageAtIndex:1].c, @"");
  XCTAssertTrue(320 == [message repeatedImportMessageAtIndex:1].d, @"");

  XCTAssertTrue(TestAllTypesNestedEnumBaz == [message repeatedNestedEnumAtIndex:1], @"");
  XCTAssertTrue(ForeignEnumForeignBaz == [message repeatedForeignEnumAtIndex:1], @"");
  XCTAssertTrue(ImportEnumImportBaz == [message repeatedImportEnumAtIndex:1], @"");

  XCTAssertEqualObjects(@"324", [message repeatedStringPieceAtIndex:1], @"");
  XCTAssertEqualObjects(@"325", [message repeatedCordAtIndex:1], @"");

  // -----------------------------------------------------------------

  XCTAssertTrue(message.hasDefaultInt32, @"");
  XCTAssertTrue(message.hasDefaultInt64, @"");
  XCTAssertTrue(message.hasDefaultUint32, @"");
  XCTAssertTrue(message.hasDefaultUint64, @"");
  XCTAssertTrue(message.hasDefaultSint32, @"");
  XCTAssertTrue(message.hasDefaultSint64, @"");
  XCTAssertTrue(message.hasDefaultFixed32, @"");
  XCTAssertTrue(message.hasDefaultFixed64, @"");
  XCTAssertTrue(message.hasDefaultSfixed32, @"");
  XCTAssertTrue(message.hasDefaultSfixed64, @"");
  XCTAssertTrue(message.hasDefaultFloat, @"");
  XCTAssertTrue(message.hasDefaultDouble, @"");
  XCTAssertTrue(message.hasDefaultBool, @"");
  XCTAssertTrue(message.hasDefaultString, @"");
  XCTAssertTrue(message.hasDefaultBytes, @"");

  XCTAssertTrue(message.hasDefaultNestedEnum, @"");
  XCTAssertTrue(message.hasDefaultForeignEnum, @"");
  XCTAssertTrue(message.hasDefaultImportEnum, @"");

  XCTAssertTrue(message.hasDefaultStringPiece, @"");
  XCTAssertTrue(message.hasDefaultCord, @"");

  XCTAssertTrue(401 == message.defaultInt32, @"");
  XCTAssertTrue(402 == message.defaultInt64, @"");
  XCTAssertTrue(403 == message.defaultUint32, @"");
  XCTAssertTrue(404 == message.defaultUint64, @"");
  XCTAssertTrue(405 == message.defaultSint32, @"");
  XCTAssertTrue(406 == message.defaultSint64, @"");
  XCTAssertTrue(407 == message.defaultFixed32, @"");
  XCTAssertTrue(408 == message.defaultFixed64, @"");
  XCTAssertTrue(409 == message.defaultSfixed32, @"");
  XCTAssertTrue(410 == message.defaultSfixed64, @"");
  XCTAssertEqualWithAccuracy(411.0f, message.defaultFloat, 0.1, @"");
  XCTAssertEqualWithAccuracy(412.0, message.defaultDouble, 0.1, @"");
  XCTAssertTrue(NO == message.defaultBool, @"");
  XCTAssertEqualObjects(@"415", message.defaultString, @"");
  XCTAssertEqualObjects([TestUtilities getData:@"416"], message.defaultBytes, @"");

  XCTAssertTrue(TestAllTypesNestedEnumFoo == message.defaultNestedEnum, @"");
  XCTAssertTrue(ForeignEnumForeignFoo == message.defaultForeignEnum, @"");
  XCTAssertTrue(ImportEnumImportFoo == message.defaultImportEnum, @"");

  XCTAssertEqualObjects(@"424", message.defaultStringPiece, @"");
  XCTAssertEqualObjects(@"425", message.defaultCord, @"");
}

+ (void) assertAllFieldsSet:(TestAllTypes*) message {
  [[[TestUtilities alloc] init] assertAllFieldsSet:message];
}


+ (void) setAllFields:(TestAllTypesBuilder*) message {
  [message setOptionalInt32:101];
  [message setOptionalInt64:102];
  [message setOptionalUint32:103];
  [message setOptionalUint64:104];
  [message setOptionalSint32:105];
  [message setOptionalSint64:106];
  [message setOptionalFixed32:107];
  [message setOptionalFixed64:108];
  [message setOptionalSfixed32:109];
  [message setOptionalSfixed64:110];
  [message setOptionalFloat:111];
  [message setOptionalDouble:112];
  [message setOptionalBool:YES];
  [message setOptionalString:@"115"];
  [message setOptionalBytes:[self getData:@"116"]];

  [message setOptionalGroup:[[[TestAllTypesOptionalGroup builder] setA:117] build]];
  [message setOptionalNestedMessage:[[[TestAllTypesNestedMessage builder] setBb:118] build]];
  [message setOptionalForeignMessage:[[[ForeignMessage builder] setC:119] build]];
  [message setOptionalImportMessage:[[[ImportMessage builder] setD:120] build]];

  [message setOptionalNestedEnum:TestAllTypesNestedEnumBaz];
  [message setOptionalForeignEnum:ForeignEnumForeignBaz];
  [message setOptionalImportEnum:ImportEnumImportBaz];

  [message setOptionalStringPiece:@"124"];
  [message setOptionalCord:@"125"];

  // -----------------------------------------------------------------

  [message addRepeatedInt32   :201];
  [message addRepeatedInt64   :202];
  [message addRepeatedUint32  :203];
  [message addRepeatedUint64  :204];
  [message addRepeatedSint32  :205];
  [message addRepeatedSint64  :206];
  [message addRepeatedFixed32 :207];
  [message addRepeatedFixed64 :208];
  [message addRepeatedSfixed32:209];
  [message addRepeatedSfixed64:210];
  [message addRepeatedFloat   :211];
  [message addRepeatedDouble  :212];
  [message addRepeatedBool    :YES];
  [message addRepeatedString  :@"215"];
  [message addRepeatedBytes   :[self getData:@"216"]];

  [message addRepeatedGroup:[[[TestAllTypesRepeatedGroup builder] setA:217] build]];
  [message addRepeatedNestedMessage:[[[TestAllTypesNestedMessage builder] setBb:218] build]];
  [message addRepeatedForeignMessage:[[[ForeignMessage builder] setC:219] build]];
  [message addRepeatedImportMessage:[[[ImportMessage builder] setD:220] build]];

  [message addRepeatedNestedEnum:TestAllTypesNestedEnumBar];
  [message addRepeatedForeignEnum:ForeignEnumForeignBar];
  [message addRepeatedImportEnum:ImportEnumImportBar];

  [message addRepeatedStringPiece:@"224"];
  [message addRepeatedCord:@"225"];

  // Add a second one of each field.
  [message addRepeatedInt32   :301];
  [message addRepeatedInt64   :302];
  [message addRepeatedUint32  :303];
  [message addRepeatedUint64  :304];
  [message addRepeatedSint32  :305];
  [message addRepeatedSint64  :306];
  [message addRepeatedFixed32 :307];
  [message addRepeatedFixed64 :308];
  [message addRepeatedSfixed32:309];
  [message addRepeatedSfixed64:310];
  [message addRepeatedFloat   :311];
  [message addRepeatedDouble  :312];
  [message addRepeatedBool    :NO];
  [message addRepeatedString  :@"315"];
  [message addRepeatedBytes   :[self getData:@"316"]];

  [message addRepeatedGroup:[[[TestAllTypesRepeatedGroup builder] setA:317] build]];
  [message addRepeatedNestedMessage:[[[TestAllTypesNestedMessage builder] setBb:318] build]];
  [message addRepeatedForeignMessage:[[[ForeignMessage builder] setC:319] build]];
  [message addRepeatedImportMessage:[[[ImportMessage builder] setD:320] build]];

  [message addRepeatedNestedEnum:TestAllTypesNestedEnumBaz];
  [message addRepeatedForeignEnum:ForeignEnumForeignBaz];
  [message addRepeatedImportEnum:ImportEnumImportBaz];

  [message addRepeatedStringPiece:@"324"];
  [message addRepeatedCord:@"325"];

  // -----------------------------------------------------------------

  [message setDefaultInt32   :401];
  [message setDefaultInt64   :402];
  [message setDefaultUint32  :403];
  [message setDefaultUint64  :404];
  [message setDefaultSint32  :405];
  [message setDefaultSint64  :406];
  [message setDefaultFixed32 :407];
  [message setDefaultFixed64 :408];
  [message setDefaultSfixed32:409];
  [message setDefaultSfixed64:410];
  [message setDefaultFloat   :411];
  [message setDefaultDouble  :412];
  [message setDefaultBool    :NO];
  [message setDefaultString  :@"415"];
  [message setDefaultBytes   :[self getData:@"416"]];

  [message setDefaultNestedEnum :TestAllTypesNestedEnumFoo];
  [message setDefaultForeignEnum:ForeignEnumForeignFoo];
  [message setDefaultImportEnum :ImportEnumImportFoo];

  [message setDefaultStringPiece:@"424"];
  [message setDefaultCord:@"425"];
}

/**
 * Set every field of {@code message} to the values expected by
 * {@code assertAllExtensionsSet()}.
 */
+ (void) setAllExtensions:(TestAllExtensionsBuilder*) message {
  [message setExtension:[UnittestRoot optionalInt32Extension]   value:[NSNumber numberWithInteger:101]];
  [message setExtension:[UnittestRoot optionalInt64Extension]   value:[NSNumber numberWithInteger:102L]];
  [message setExtension:[UnittestRoot optionalUint32Extension]  value:[NSNumber numberWithInteger:103]];
  [message setExtension:[UnittestRoot optionalUint64Extension]  value:[NSNumber numberWithInteger:104L]];
  [message setExtension:[UnittestRoot optionalSint32Extension]  value:[NSNumber numberWithInteger:105]];
  [message setExtension:[UnittestRoot optionalSint64Extension]  value:[NSNumber numberWithInteger:106L]];
  [message setExtension:[UnittestRoot optionalFixed32Extension] value:[NSNumber numberWithInteger:107]];
  [message setExtension:[UnittestRoot optionalFixed64Extension] value:[NSNumber numberWithInteger:108L]];
  [message setExtension:[UnittestRoot optionalSfixed32Extension] value:[NSNumber numberWithInteger:109]];
  [message setExtension:[UnittestRoot optionalSfixed64Extension] value:[NSNumber numberWithInteger:110L]];
  [message setExtension:[UnittestRoot optionalFloatExtension]   value:[NSNumber numberWithFloat:111.0]];
  [message setExtension:[UnittestRoot optionalDoubleExtension]  value:[NSNumber numberWithDouble:112.0]];
  [message setExtension:[UnittestRoot optionalBoolExtension]    value:[NSNumber numberWithBool:YES]];
  [message setExtension:[UnittestRoot optionalStringExtension]  value:@"115"];
  [message setExtension:[UnittestRoot optionalBytesExtension]   value:[self getData:@"116"]];

  [message setExtension:[UnittestRoot optionalGroupExtension]
                  value:[[[OptionalGroup_extension builder] setA:117] build]];
  [message setExtension:[UnittestRoot optionalNestedMessageExtension]
                  value:[[[TestAllTypesNestedMessage builder] setBb:118] build]];
  [message setExtension:[UnittestRoot optionalForeignMessageExtension]
                  value:[[[ForeignMessage builder] setC:119] build]];
  [message setExtension:[UnittestRoot optionalImportMessageExtension]
                  value:[[[ImportMessage builder] setD:120] build]];

  [message setExtension:[UnittestRoot optionalNestedEnumExtension]
                  value:[NSNumber numberWithInteger:TestAllTypesNestedEnumBaz]];
  [message setExtension:[UnittestRoot optionalForeignEnumExtension]
                  value:[NSNumber numberWithInteger:ForeignEnumForeignBaz]];
  [message setExtension:[UnittestRoot optionalImportEnumExtension]
                  value:[NSNumber numberWithInteger:ImportEnumImportBaz]];

  [message setExtension:[UnittestRoot optionalStringPieceExtension]  value:@"124"];
  [message setExtension:[UnittestRoot optionalCordExtension] value:@"125"];

  // -----------------------------------------------------------------

  [message addExtension:[UnittestRoot repeatedInt32Extension]    value:[NSNumber numberWithInteger:201]];
  [message addExtension:[UnittestRoot repeatedInt64Extension]    value:[NSNumber numberWithInteger:202L]];
  [message addExtension:[UnittestRoot repeatedUint32Extension]   value:[NSNumber numberWithInteger:203]];
  [message addExtension:[UnittestRoot repeatedUint64Extension]   value:[NSNumber numberWithInteger:204L]];
  [message addExtension:[UnittestRoot repeatedSint32Extension]   value:[NSNumber numberWithInteger:205]];
  [message addExtension:[UnittestRoot repeatedSint64Extension]   value:[NSNumber numberWithInteger:206L]];
  [message addExtension:[UnittestRoot repeatedFixed32Extension]  value:[NSNumber numberWithInteger:207]];
  [message addExtension:[UnittestRoot repeatedFixed64Extension]  value:[NSNumber numberWithInteger:208L]];
  [message addExtension:[UnittestRoot repeatedSfixed32Extension] value:[NSNumber numberWithInteger:209]];
  [message addExtension:[UnittestRoot repeatedSfixed64Extension] value:[NSNumber numberWithInteger:210L]];
  [message addExtension:[UnittestRoot repeatedFloatExtension]    value:[NSNumber numberWithFloat:211.0]];
  [message addExtension:[UnittestRoot repeatedDoubleExtension]   value:[NSNumber numberWithDouble:212.0]];
  [message addExtension:[UnittestRoot repeatedBoolExtension]     value:[NSNumber numberWithBool:YES]];
  [message addExtension:[UnittestRoot repeatedStringExtension]  value:@"215"];
  [message addExtension:[UnittestRoot repeatedBytesExtension]   value:[self getData:@"216"]];

  [message addExtension:[UnittestRoot repeatedGroupExtension]
                  value:[[[RepeatedGroup_extension builder] setA:217] build]];
  [message addExtension:[UnittestRoot repeatedNestedMessageExtension]
                  value:[[[TestAllTypesNestedMessage builder] setBb:218] build]];
  [message addExtension:[UnittestRoot repeatedForeignMessageExtension]
                  value:[[[ForeignMessage builder] setC:219] build]];
  [message addExtension:[UnittestRoot repeatedImportMessageExtension]
                  value:[[[ImportMessage builder] setD:220] build]];

  [message addExtension:[UnittestRoot repeatedNestedEnumExtension]
                  value:[NSNumber numberWithInteger:TestAllTypesNestedEnumBar]];
  [message addExtension:[UnittestRoot repeatedForeignEnumExtension]
                  value:[NSNumber numberWithInteger:ForeignEnumForeignBar]];
  [message addExtension:[UnittestRoot repeatedImportEnumExtension]
                  value:[NSNumber numberWithInteger:ImportEnumImportBar]];

  [message addExtension:[UnittestRoot repeatedStringPieceExtension] value:@"224"];
  [message addExtension:[UnittestRoot repeatedCordExtension] value:@"225"];

  // Add a second one of each field.
  [message addExtension:[UnittestRoot repeatedInt32Extension] value:[NSNumber numberWithInteger:301]];
  [message addExtension:[UnittestRoot repeatedInt64Extension] value:[NSNumber numberWithInteger:302L]];
  [message addExtension:[UnittestRoot repeatedUint32Extension] value:[NSNumber numberWithInteger:303]];
  [message addExtension:[UnittestRoot repeatedUint64Extension] value:[NSNumber numberWithInteger:304L]];
  [message addExtension:[UnittestRoot repeatedSint32Extension] value:[NSNumber numberWithInteger:305]];
  [message addExtension:[UnittestRoot repeatedSint64Extension] value:[NSNumber numberWithInteger:306L]];
  [message addExtension:[UnittestRoot repeatedFixed32Extension] value:[NSNumber numberWithInteger:307]];
  [message addExtension:[UnittestRoot repeatedFixed64Extension] value:[NSNumber numberWithInteger:308L]];
  [message addExtension:[UnittestRoot repeatedSfixed32Extension] value:[NSNumber numberWithInteger:309]];
  [message addExtension:[UnittestRoot repeatedSfixed64Extension] value:[NSNumber numberWithInteger:310L]];
  [message addExtension:[UnittestRoot repeatedFloatExtension] value:[NSNumber numberWithFloat:311.0]];
  [message addExtension:[UnittestRoot repeatedDoubleExtension] value:[NSNumber numberWithDouble:312.0]];
  [message addExtension:[UnittestRoot repeatedBoolExtension] value:[NSNumber numberWithBool:NO]];
  [message addExtension:[UnittestRoot repeatedStringExtension] value:@"315"];
  [message addExtension:[UnittestRoot repeatedBytesExtension] value:[self getData:@"316"]];

  [message addExtension:[UnittestRoot repeatedGroupExtension]
                  value:[[[RepeatedGroup_extension builder] setA:317] build]];
  [message addExtension:[UnittestRoot repeatedNestedMessageExtension]
                  value:[[[TestAllTypesNestedMessage builder] setBb:318] build]];
  [message addExtension:[UnittestRoot repeatedForeignMessageExtension]
                  value:[[[ForeignMessage builder] setC:319] build]];
  [message addExtension:[UnittestRoot repeatedImportMessageExtension]
                  value:[[[ImportMessage builder] setD:320] build]];

  [message addExtension:[UnittestRoot repeatedNestedEnumExtension]
                  value:[NSNumber numberWithInteger:TestAllTypesNestedEnumBaz]];
  [message addExtension:[UnittestRoot repeatedForeignEnumExtension]
                  value:[NSNumber numberWithInteger:ForeignEnumForeignBaz]];
  [message addExtension:[UnittestRoot repeatedImportEnumExtension]
                  value:[NSNumber numberWithInteger:ImportEnumImportBaz]];

  [message addExtension:[UnittestRoot repeatedStringPieceExtension] value:@"324"];
  [message addExtension:[UnittestRoot repeatedCordExtension] value:@"325"];

  // -----------------------------------------------------------------

  [message setExtension:[UnittestRoot defaultInt32Extension] value:[NSNumber numberWithInteger:401]];
  [message setExtension:[UnittestRoot defaultInt64Extension] value:[NSNumber numberWithInteger:402L]];
  [message setExtension:[UnittestRoot defaultUint32Extension] value:[NSNumber numberWithInteger:403]];
  [message setExtension:[UnittestRoot defaultUint64Extension] value:[NSNumber numberWithInteger:404L]];
  [message setExtension:[UnittestRoot defaultSint32Extension] value:[NSNumber numberWithInteger:405]];
  [message setExtension:[UnittestRoot defaultSint64Extension] value:[NSNumber numberWithInteger:406L]];
  [message setExtension:[UnittestRoot defaultFixed32Extension] value:[NSNumber numberWithInteger:407]];
  [message setExtension:[UnittestRoot defaultFixed64Extension] value:[NSNumber numberWithInteger:408L]];
  [message setExtension:[UnittestRoot defaultSfixed32Extension] value:[NSNumber numberWithInteger:409]];
  [message setExtension:[UnittestRoot defaultSfixed64Extension] value:[NSNumber numberWithInteger:410L]];
  [message setExtension:[UnittestRoot defaultFloatExtension] value:[NSNumber numberWithFloat:411.0]];
  [message setExtension:[UnittestRoot defaultDoubleExtension] value:[NSNumber numberWithDouble:412.0]];
  [message setExtension:[UnittestRoot defaultBoolExtension] value:[NSNumber numberWithBool:NO]];
  [message setExtension:[UnittestRoot defaultStringExtension] value:@"415"];
  [message setExtension:[UnittestRoot defaultBytesExtension] value:[self getData:@"416"]];

  [message setExtension:[UnittestRoot defaultNestedEnumExtension]
                  value:[NSNumber numberWithInteger:TestAllTypesNestedEnumFoo]];
  [message setExtension:[UnittestRoot defaultForeignEnumExtension]
                  value:[NSNumber numberWithInteger:ForeignEnumForeignFoo]];
  [message setExtension:[UnittestRoot defaultImportEnumExtension]
                  value:[NSNumber numberWithInteger:ImportEnumImportFoo]];

  [message setExtension:[UnittestRoot defaultStringPieceExtension] value:@"424"];
  [message setExtension:[UnittestRoot defaultCordExtension] value:@"425"];
}


/**
 * Register all of {@code TestAllExtensions}' extensions with the
 * given {@link ExtensionRegistry}.
 */
+ (void) registerAllExtensions:(PBMutableExtensionRegistry*) registry {
  [UnittestRoot registerAllExtensions:registry];
  /*
  [registry addExtension:[UnittestRoot optionalInt32Extension]];
  [registry addExtension:[UnittestRoot optionalInt64Extension]];
  [registry addExtension:[UnittestRoot optionalUint32Extension]];
  [registry addExtension:[UnittestRoot optionalUint64Extension]];
  [registry addExtension:[UnittestRoot optionalSint32Extension]];
  [registry addExtension:[UnittestRoot optionalSint64Extension]];
  [registry addExtension:[UnittestRoot optionalFixed32Extension]];
  [registry addExtension:[UnittestRoot optionalFixed64Extension]];
  [registry addExtension:[UnittestRoot optionalSfixed32Extension]];
  [registry addExtension:[UnittestRoot optionalSfixed64Extension]];
  [registry addExtension:[UnittestRoot optionalFloatExtension]];
  [registry addExtension:[UnittestRoot optionalDoubleExtension]];
  [registry addExtension:[UnittestRoot optionalBoolExtension]];
  [registry addExtension:[UnittestRoot optionalStringExtension]];
  [registry addExtension:[UnittestRoot optionalBytesExtension]];
  [registry addExtension:[UnittestRoot optionalGroupExtension]];
  [registry addExtension:[UnittestRoot optionalNestedMessageExtension]];
  [registry addExtension:[UnittestRoot optionalForeignMessageExtension]];
  [registry addExtension:[UnittestRoot optionalImportMessageExtension]];
  [registry addExtension:[UnittestRoot optionalNestedEnumExtension]];
  [registry addExtension:[UnittestRoot optionalForeignEnumExtension]];
  [registry addExtension:[UnittestRoot optionalImportEnumExtension]];
  [registry addExtension:[UnittestRoot optionalStringPieceExtension]];
  [registry addExtension:[UnittestRoot optionalCordExtension]];

  [registry addExtension:[UnittestRoot repeatedInt32Extension]];
  [registry addExtension:[UnittestRoot repeatedInt64Extension]];
  [registry addExtension:[UnittestRoot repeatedUint32Extension]];
  [registry addExtension:[UnittestRoot repeatedUint64Extension]];
  [registry addExtension:[UnittestRoot repeatedSint32Extension]];
  [registry addExtension:[UnittestRoot repeatedSint64Extension]];
  [registry addExtension:[UnittestRoot repeatedFixed32Extension]];
  [registry addExtension:[UnittestRoot repeatedFixed64Extension]];
  [registry addExtension:[UnittestRoot repeatedSfixed32Extension]];
  [registry addExtension:[UnittestRoot repeatedSfixed64Extension]];
  [registry addExtension:[UnittestRoot repeatedFloatExtension]];
  [registry addExtension:[UnittestRoot repeatedDoubleExtension]];
  [registry addExtension:[UnittestRoot repeatedBoolExtension]];
  [registry addExtension:[UnittestRoot repeatedStringExtension]];
  [registry addExtension:[UnittestRoot repeatedBytesExtension]];
  [registry addExtension:[UnittestRoot repeatedGroupExtension]];
  [registry addExtension:[UnittestRoot repeatedNestedMessageExtension]];
  [registry addExtension:[UnittestRoot repeatedForeignMessageExtension]];
  [registry addExtension:[UnittestRoot repeatedImportMessageExtension]];
  [registry addExtension:[UnittestRoot repeatedNestedEnumExtension]];
  [registry addExtension:[UnittestRoot repeatedForeignEnumExtension]];
  [registry addExtension:[UnittestRoot repeatedImportEnumExtension]];
  [registry addExtension:[UnittestRoot repeatedStringPieceExtension]];
  [registry addExtension:[UnittestRoot repeatedCordExtension]];

  [registry addExtension:[UnittestRoot defaultInt32Extension]];
  [registry addExtension:[UnittestRoot defaultInt64Extension]];
  [registry addExtension:[UnittestRoot defaultUint32Extension]];
  [registry addExtension:[UnittestRoot defaultUint64Extension]];
  [registry addExtension:[UnittestRoot defaultSint32Extension]];
  [registry addExtension:[UnittestRoot defaultSint64Extension]];
  [registry addExtension:[UnittestRoot defaultFixed32Extension]];
  [registry addExtension:[UnittestRoot defaultFixed64Extension]];
  [registry addExtension:[UnittestRoot defaultSfixed32Extension]];
  [registry addExtension:[UnittestRoot defaultSfixed64Extension]];
  [registry addExtension:[UnittestRoot defaultFloatExtension]];
  [registry addExtension:[UnittestRoot defaultDoubleExtension]];
  [registry addExtension:[UnittestRoot defaultBoolExtension]];
  [registry addExtension:[UnittestRoot defaultStringExtension]];
  [registry addExtension:[UnittestRoot defaultBytesExtension]];
  [registry addExtension:[UnittestRoot defaultNestedEnumExtension]];
  [registry addExtension:[UnittestRoot defaultForeignEnumExtension]];
  [registry addExtension:[UnittestRoot defaultImportEnumExtension]];
  [registry addExtension:[UnittestRoot defaultStringPieceExtension]];
  [registry addExtension:[UnittestRoot defaultCordExtension]];
   */
}


/**
 * Get an unmodifiable {@link ExtensionRegistry} containing all the
 * extensions of {@code TestAllExtensions}.
 */
+ (PBExtensionRegistry*) extensionRegistry {
  PBMutableExtensionRegistry* registry = [PBMutableExtensionRegistry registry];
  [self registerAllExtensions:registry];
  return registry;
}


+ (TestAllTypes*) allSet {
  TestAllTypesBuilder* builder = [TestAllTypes builder];
  [self setAllFields:builder];
  return [builder build];
}


+ (TestAllExtensions*) allExtensionsSet {
  TestAllExtensionsBuilder* builder = [TestAllExtensions builder];
  [self setAllExtensions:builder];
  return [builder build];
}


+ (TestPackedTypes*) packedSet {
  TestPackedTypesBuilder* builder = [TestPackedTypes builder];
  [self setPackedFields:builder];
  return [builder build];
}


+ (TestPackedExtensions*) packedExtensionsSet {
  TestPackedExtensionsBuilder* builder = [TestPackedExtensions builder];
  [self setPackedExtensions:builder];
  return [builder build];
}

// -------------------------------------------------------------------

/**
 * Assert (using {@code junit.framework.Assert}} that all fields of
 * {@code message} are cleared, and that getting the fields returns their
 * default values.
 */
- (void) assertClear:(TestAllTypes*) message {
  // hasBlah() should initially be NO for all optional fields.
  XCTAssertFalse(message.hasOptionalInt32, @"");
  XCTAssertFalse(message.hasOptionalInt64, @"");
  XCTAssertFalse(message.hasOptionalUint32, @"");
  XCTAssertFalse(message.hasOptionalUint64, @"");
  XCTAssertFalse(message.hasOptionalSint32, @"");
  XCTAssertFalse(message.hasOptionalSint64, @"");
  XCTAssertFalse(message.hasOptionalFixed32, @"");
  XCTAssertFalse(message.hasOptionalFixed64, @"");
  XCTAssertFalse(message.hasOptionalSfixed32, @"");
  XCTAssertFalse(message.hasOptionalSfixed64, @"");
  XCTAssertFalse(message.hasOptionalFloat, @"");
  XCTAssertFalse(message.hasOptionalDouble, @"");
  XCTAssertFalse(message.hasOptionalBool, @"");
  XCTAssertFalse(message.hasOptionalString, @"");
  XCTAssertFalse(message.hasOptionalBytes, @"");

  XCTAssertFalse(message.hasOptionalGroup, @"");
  XCTAssertFalse(message.hasOptionalNestedMessage, @"");
  XCTAssertFalse(message.hasOptionalForeignMessage, @"");
  XCTAssertFalse(message.hasOptionalImportMessage, @"");

  XCTAssertFalse(message.hasOptionalNestedEnum, @"");
  XCTAssertFalse(message.hasOptionalForeignEnum, @"");
  XCTAssertFalse(message.hasOptionalImportEnum, @"");

  XCTAssertFalse(message.hasOptionalStringPiece, @"");
  XCTAssertFalse(message.hasOptionalCord, @"");

  // Optional fields without defaults are set to zero or something like it.
  XCTAssertTrue(0 == message.optionalInt32, @"");
  XCTAssertTrue(0 == message.optionalInt64, @"");
  XCTAssertTrue(0 == message.optionalUint32, @"");
  XCTAssertTrue(0 == message.optionalUint64, @"");
  XCTAssertTrue(0 == message.optionalSint32, @"");
  XCTAssertTrue(0 == message.optionalSint64, @"");
  XCTAssertTrue(0 == message.optionalFixed32, @"");
  XCTAssertTrue(0 == message.optionalFixed64, @"");
  XCTAssertTrue(0 == message.optionalSfixed32, @"");
  XCTAssertTrue(0 == message.optionalSfixed64, @"");
  XCTAssertTrue(0 == message.optionalFloat, @"");
  XCTAssertTrue(0 == message.optionalDouble, @"");
  XCTAssertTrue(NO == message.optionalBool, @"");
  XCTAssertEqualObjects(@"", message.optionalString, @"");
  XCTAssertEqualObjects([NSData data], message.optionalBytes, @"");

  // Embedded messages should also be clear.
  XCTAssertFalse(message.optionalGroup.hasA, @"");
  XCTAssertFalse(message.optionalNestedMessage.hasBb, @"");
  XCTAssertFalse(message.optionalForeignMessage.hasC, @"");
  XCTAssertFalse(message.optionalImportMessage.hasD, @"");

  XCTAssertTrue(0 == message.optionalGroup.a, @"");
  XCTAssertTrue(0 == message.optionalNestedMessage.bb, @"");
  XCTAssertTrue(0 == message.optionalForeignMessage.c, @"");
  XCTAssertTrue(0 == message.optionalImportMessage.d, @"");

  // Enums without defaults are set to the first value in the enum.
  XCTAssertTrue(TestAllTypesNestedEnumFoo == message.optionalNestedEnum, @"");
  XCTAssertTrue(ForeignEnumForeignFoo == message.optionalForeignEnum, @"");
  XCTAssertTrue(ImportEnumImportFoo == message.optionalImportEnum, @"");

  XCTAssertEqualObjects(@"", message.optionalStringPiece, @"");
  XCTAssertEqualObjects(@"", message.optionalCord, @"");

  // Repeated fields are empty.
  XCTAssertTrue(0 == message.repeatedInt32.count, @"");
  XCTAssertTrue(0 == message.repeatedInt64.count, @"");
  XCTAssertTrue(0 == message.repeatedUint32.count, @"");
  XCTAssertTrue(0 == message.repeatedUint64.count, @"");
  XCTAssertTrue(0 == message.repeatedSint32.count, @"");
  XCTAssertTrue(0 == message.repeatedSint64.count, @"");
  XCTAssertTrue(0 == message.repeatedFixed32.count, @"");
  XCTAssertTrue(0 == message.repeatedFixed64.count, @"");
  XCTAssertTrue(0 == message.repeatedSfixed32.count, @"");
  XCTAssertTrue(0 == message.repeatedSfixed64.count, @"");
  XCTAssertTrue(0 == message.repeatedFloat.count, @"");
  XCTAssertTrue(0 == message.repeatedDouble.count, @"");
  XCTAssertTrue(0 == message.repeatedBool.count, @"");
  XCTAssertTrue(0 == message.repeatedString.count, @"");
  XCTAssertTrue(0 == message.repeatedBytes.count, @"");

  XCTAssertTrue(0 == message.repeatedGroup.count, @"");
  XCTAssertTrue(0 == message.repeatedNestedMessage.count, @"");
  XCTAssertTrue(0 == message.repeatedForeignMessage.count, @"");
  XCTAssertTrue(0 == message.repeatedImportMessage.count, @"");
  XCTAssertTrue(0 == message.repeatedNestedEnum.count, @"");
  XCTAssertTrue(0 == message.repeatedForeignEnum.count, @"");
  XCTAssertTrue(0 == message.repeatedImportEnum.count, @"");

  XCTAssertTrue(0 == message.repeatedStringPiece.count, @"");
  XCTAssertTrue(0 == message.repeatedCord.count, @"");

  // hasBlah() should also be NO for all default fields.
  XCTAssertFalse(message.hasDefaultInt32, @"");
  XCTAssertFalse(message.hasDefaultInt64, @"");
  XCTAssertFalse(message.hasDefaultUint32, @"");
  XCTAssertFalse(message.hasDefaultUint64, @"");
  XCTAssertFalse(message.hasDefaultSint32, @"");
  XCTAssertFalse(message.hasDefaultSint64, @"");
  XCTAssertFalse(message.hasDefaultFixed32, @"");
  XCTAssertFalse(message.hasDefaultFixed64, @"");
  XCTAssertFalse(message.hasDefaultSfixed32, @"");
  XCTAssertFalse(message.hasDefaultSfixed64, @"");
  XCTAssertFalse(message.hasDefaultFloat, @"");
  XCTAssertFalse(message.hasDefaultDouble, @"");
  XCTAssertFalse(message.hasDefaultBool, @"");
  XCTAssertFalse(message.hasDefaultString, @"");
  XCTAssertFalse(message.hasDefaultBytes, @"");

  XCTAssertFalse(message.hasDefaultNestedEnum, @"");
  XCTAssertFalse(message.hasDefaultForeignEnum, @"");
  XCTAssertFalse(message.hasDefaultImportEnum, @"");

  XCTAssertFalse(message.hasDefaultStringPiece, @"");
  XCTAssertFalse(message.hasDefaultCord, @"");

  // Fields with defaults have their default values (duh).
  XCTAssertTrue( 41 == message.defaultInt32, @"");
  XCTAssertTrue( 42 == message.defaultInt64, @"");
  XCTAssertTrue( 43 == message.defaultUint32, @"");
  XCTAssertTrue( 44 == message.defaultUint64, @"");
  XCTAssertTrue(-45 == message.defaultSint32, @"");
  XCTAssertTrue( 46 == message.defaultSint64, @"");
  XCTAssertTrue( 47 == message.defaultFixed32, @"");
  XCTAssertTrue( 48 == message.defaultFixed64, @"");
  XCTAssertTrue( 49 == message.defaultSfixed32, @"");
  XCTAssertTrue(-50 == message.defaultSfixed64, @"");
  XCTAssertEqualWithAccuracy(51.5, message.defaultFloat, 0.1, @"");
  XCTAssertEqualWithAccuracy(52e3, message.defaultDouble, 0.1, @"");
  XCTAssertTrue(YES == message.defaultBool, @"");
  XCTAssertEqualObjects(@"hello", message.defaultString, @"");
  XCTAssertEqualObjects([TestUtilities getData:@"world"], message.defaultBytes, @"");

  XCTAssertTrue(TestAllTypesNestedEnumBar == message.defaultNestedEnum, @"");
  XCTAssertTrue(ForeignEnumForeignBar == message.defaultForeignEnum, @"");
  XCTAssertTrue(ImportEnumImportBar == message.defaultImportEnum, @"");

  XCTAssertEqualObjects(@"abc", message.defaultStringPiece, @"");
  XCTAssertEqualObjects(@"123", message.defaultCord, @"");
}


+ (void) assertClear:(TestAllTypes*) message {
  return [[[TestUtilities alloc] init] assertClear:message];
}


- (void) assertExtensionsClear:(TestAllExtensions*) message {
  // hasBlah() should initially be NO for all optional fields.
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalInt32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalInt64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalUint32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalUint64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalSint32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalSint64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalFixed32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalFixed64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalSfixed32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalSfixed64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalFloatExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalDoubleExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalBoolExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalStringExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalBytesExtension]], @"");

  XCTAssertFalse([message hasExtension:[UnittestRoot optionalGroupExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalNestedMessageExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalForeignMessageExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalImportMessageExtension]], @"");

  XCTAssertFalse([message hasExtension:[UnittestRoot optionalNestedEnumExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalForeignEnumExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalImportEnumExtension]], @"");

  XCTAssertFalse([message hasExtension:[UnittestRoot optionalStringPieceExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot optionalCordExtension]], @"");

  // Optional fields without defaults are set to zero or something like it.
  XCTAssertTrue(0     == [[message getExtension:[UnittestRoot optionalInt32Extension]] integerValue], @"");
  XCTAssertTrue(0L    == [[message getExtension:[UnittestRoot optionalInt64Extension]] integerValue], @"");
  XCTAssertTrue(0     == [[message getExtension:[UnittestRoot optionalUint32Extension]] integerValue], @"");
  XCTAssertTrue(0L    == [[message getExtension:[UnittestRoot optionalUint64Extension]] integerValue], @"");
  XCTAssertTrue(0     == [[message getExtension:[UnittestRoot optionalSint32Extension]] integerValue], @"");
  XCTAssertTrue(0L    == [[message getExtension:[UnittestRoot optionalSint64Extension]] integerValue], @"");
  XCTAssertTrue(0     == [[message getExtension:[UnittestRoot optionalFixed32Extension]] integerValue], @"");
  XCTAssertTrue(0L    == [[message getExtension:[UnittestRoot optionalFixed64Extension]] integerValue], @"");
  XCTAssertTrue(0     == [[message getExtension:[UnittestRoot optionalSfixed32Extension]] integerValue], @"");
  XCTAssertTrue(0L    == [[message getExtension:[UnittestRoot optionalSfixed64Extension]] integerValue], @"");
  XCTAssertTrue(0    == [[message getExtension:[UnittestRoot optionalFloatExtension]] floatValue], @"");
  XCTAssertTrue(0    == [[message getExtension:[UnittestRoot optionalDoubleExtension]] doubleValue], @"");
  XCTAssertTrue(NO == [[message getExtension:[UnittestRoot optionalBoolExtension]] boolValue], @"");
  XCTAssertEqualObjects(@"", [message getExtension:[UnittestRoot optionalStringExtension]], @"");
  XCTAssertEqualObjects([NSData data], [message getExtension:[UnittestRoot optionalBytesExtension]], @"");

  // Embedded messages should also be clear.

  XCTAssertFalse([[message getExtension:[UnittestRoot optionalGroupExtension]] hasA], @"");
  XCTAssertFalse([[message getExtension:[UnittestRoot optionalNestedMessageExtension]] hasBb], @"");
  XCTAssertFalse([[message getExtension:[UnittestRoot optionalForeignMessageExtension]] hasC], @"");
  XCTAssertFalse([[message getExtension:[UnittestRoot optionalImportMessageExtension]] hasD], @"");

  XCTAssertTrue(0 == [(OptionalGroup_extension *)[message getExtension:[UnittestRoot optionalGroupExtension]] a], @"");
  XCTAssertTrue(0 == [(TestAllTypesNestedMessage *)[message getExtension:[UnittestRoot optionalNestedMessageExtension]] bb], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot optionalForeignMessageExtension]] c], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot optionalImportMessageExtension]] d], @"");

  // Enums without defaults are set to the first value in the enum.
  XCTAssertTrue(TestAllTypesNestedEnumFoo ==
               [[message getExtension:[UnittestRoot optionalNestedEnumExtension]] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignFoo ==
               [[message getExtension:[UnittestRoot optionalForeignEnumExtension]] integerValue], @"");
  XCTAssertTrue(ImportEnumImportFoo ==
               [[message getExtension:[UnittestRoot optionalImportEnumExtension]] integerValue], @"");

  XCTAssertEqualObjects(@"", [message getExtension:[UnittestRoot optionalStringPieceExtension]], @"");
  XCTAssertEqualObjects(@"", [message getExtension:[UnittestRoot optionalCordExtension]], @"");

  // Repeated fields are empty.
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedInt32Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedInt64Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedUint32Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedUint64Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedSint32Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedSint64Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedFixed32Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedFixed64Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedSfixed32Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedSfixed64Extension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedFloatExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedDoubleExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedBoolExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedStringExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedBytesExtension]] count], @"");

  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedGroupExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedNestedMessageExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedForeignMessageExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedImportMessageExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedNestedEnumExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedForeignEnumExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedImportEnumExtension]] count], @"");

  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedStringPieceExtension]] count], @"");
  XCTAssertTrue(0 == [[message getExtension:[UnittestRoot repeatedCordExtension]] count], @"");

  // hasBlah() should also be NO for all default fields.
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultInt32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultInt64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultUint32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultUint64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultSint32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultSint64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultFixed32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultFixed64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultSfixed32Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultSfixed64Extension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultFloatExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultDoubleExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultBoolExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultStringExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultBytesExtension]], @"");

  XCTAssertFalse([message hasExtension:[UnittestRoot defaultNestedEnumExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultForeignEnumExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultImportEnumExtension]], @"");

  XCTAssertFalse([message hasExtension:[UnittestRoot defaultStringPieceExtension]], @"");
  XCTAssertFalse([message hasExtension:[UnittestRoot defaultCordExtension]], @"");

  // Fields with defaults have their default values (duh).
  XCTAssertTrue( 41     == [[message getExtension:[UnittestRoot defaultInt32Extension]] integerValue], @"");
  XCTAssertTrue( 42L    == [[message getExtension:[UnittestRoot defaultInt64Extension]] integerValue], @"");
  XCTAssertTrue( 43     == [[message getExtension:[UnittestRoot defaultUint32Extension]] integerValue], @"");
  XCTAssertTrue( 44L    == [[message getExtension:[UnittestRoot defaultUint64Extension]] integerValue], @"");
  XCTAssertTrue(-45     == [[message getExtension:[UnittestRoot defaultSint32Extension]] integerValue], @"");
  XCTAssertTrue( 46L    == [[message getExtension:[UnittestRoot defaultSint64Extension]] integerValue], @"");
  XCTAssertTrue( 47     == [[message getExtension:[UnittestRoot defaultFixed32Extension]] integerValue], @"");
  XCTAssertTrue( 48L    == [[message getExtension:[UnittestRoot defaultFixed64Extension]] integerValue], @"");
  XCTAssertTrue( 49     == [[message getExtension:[UnittestRoot defaultSfixed32Extension]] integerValue], @"");
  XCTAssertTrue(-50L    == [[message getExtension:[UnittestRoot defaultSfixed64Extension]] integerValue], @"");
  XCTAssertTrue( 51.5  == [[message getExtension:[UnittestRoot defaultFloatExtension]] floatValue], @"");
  XCTAssertTrue( 52e3  == [[message getExtension:[UnittestRoot defaultDoubleExtension]] doubleValue], @"");
  XCTAssertTrue(YES    == [[message getExtension:[UnittestRoot defaultBoolExtension]] boolValue], @"");
  XCTAssertEqualObjects(@"hello", [message getExtension:[UnittestRoot defaultStringExtension]], @"");
  XCTAssertEqualObjects([TestUtilities getData:@"world"], [message getExtension:[UnittestRoot defaultBytesExtension]], @"");

  XCTAssertTrue(TestAllTypesNestedEnumBar ==
               [[message getExtension:[UnittestRoot defaultNestedEnumExtension]] integerValue], @"");
  XCTAssertTrue(ForeignEnumForeignBar ==
               [[message getExtension:[UnittestRoot defaultForeignEnumExtension]] integerValue], @"");
  XCTAssertTrue(ImportEnumImportBar ==
               [[message getExtension:[UnittestRoot defaultImportEnumExtension]] integerValue], @"");

  XCTAssertEqualObjects(@"abc", [message getExtension:[UnittestRoot defaultStringPieceExtension]], @"");
  XCTAssertEqualObjects(@"123", [message getExtension:[UnittestRoot defaultCordExtension]], @"");
}


+ (void) assertExtensionsClear:(TestAllExtensions*) message {
  [[[TestUtilities alloc] init] assertExtensionsClear:message];
}

+ (void) setPackedFields:(TestPackedTypesBuilder*) message {
  [message addPackedInt32   :601];
  [message addPackedInt64   :602];
  [message addPackedUint32  :603];
  [message addPackedUint64  :604];
  [message addPackedSint32  :605];
  [message addPackedSint64  :606];
  [message addPackedFixed32 :607];
  [message addPackedFixed64 :608];
  [message addPackedSfixed32:609];
  [message addPackedSfixed64:610];
  [message addPackedFloat   :611];
  [message addPackedDouble  :612];
  [message addPackedBool    :YES];
  [message addPackedEnum    :ForeignEnumForeignBar];
  // Add a second one of each field.
  [message addPackedInt32   :701];
  [message addPackedInt64   :702];
  [message addPackedUint32  :703];
  [message addPackedUint64  :704];
  [message addPackedSint32  :705];
  [message addPackedSint64  :706];
  [message addPackedFixed32 :707];
  [message addPackedFixed64 :708];
  [message addPackedSfixed32:709];
  [message addPackedSfixed64:710];
  [message addPackedFloat   :711];
  [message addPackedDouble  :712];
  [message addPackedBool    :NO];
  [message addPackedEnum    :ForeignEnumForeignBaz];
}


- (void) assertPackedFieldsSet:(TestPackedTypes*) message {
  XCTAssertTrue(2 ==  message.packedInt32.count, @"");
  XCTAssertTrue(2 ==  message.packedInt64.count, @"");
  XCTAssertTrue(2 ==  message.packedUint32.count, @"");
  XCTAssertTrue(2 ==  message.packedUint64.count, @"");
  XCTAssertTrue(2 ==  message.packedSint32.count, @"");
  XCTAssertTrue(2 ==  message.packedSint64.count, @"");
  XCTAssertTrue(2 ==  message.packedFixed32.count, @"");
  XCTAssertTrue(2 ==  message.packedFixed64.count, @"");
  XCTAssertTrue(2 ==  message.packedSfixed32.count, @"");
  XCTAssertTrue(2 ==  message.packedSfixed64.count, @"");
  XCTAssertTrue(2 ==  message.packedFloat.count, @"");
  XCTAssertTrue(2 ==  message.packedDouble.count, @"");
  XCTAssertTrue(2 ==  message.packedBool.count, @"");
  XCTAssertTrue(2 ==  message.packedEnum.count, @"");
  XCTAssertTrue(601   ==  [message packedInt32AtIndex:0], @"");
  XCTAssertTrue(602   ==  [message packedInt64AtIndex:0], @"");
  XCTAssertTrue(603   ==  [message packedUint32AtIndex:0], @"");
  XCTAssertTrue(604   ==  [message packedUint64AtIndex:0], @"");
  XCTAssertTrue(605   ==  [message packedSint32AtIndex:0], @"");
  XCTAssertTrue(606   ==  [message packedSint64AtIndex:0], @"");
  XCTAssertTrue(607   ==  [message packedFixed32AtIndex:0], @"");
  XCTAssertTrue(608   ==  [message packedFixed64AtIndex:0], @"");
  XCTAssertTrue(609   ==  [message packedSfixed32AtIndex:0], @"");
  XCTAssertTrue(610   ==  [message packedSfixed64AtIndex:0], @"");
  XCTAssertTrue(611   ==  [message packedFloatAtIndex:0], @"");
  XCTAssertTrue(612   ==  [message packedDoubleAtIndex:0], @"");
  XCTAssertTrue(YES  ==  [message packedBoolAtIndex:0], @"");
  XCTAssertTrue(ForeignEnumForeignBar ==  [message packedEnumAtIndex:0], @"");
  XCTAssertTrue(701   ==  [message packedInt32AtIndex:1], @"");
  XCTAssertTrue(702   ==  [message packedInt64AtIndex:1], @"");
  XCTAssertTrue(703   ==  [message packedUint32AtIndex:1], @"");
  XCTAssertTrue(704   ==  [message packedUint64AtIndex:1], @"");
  XCTAssertTrue(705   ==  [message packedSint32AtIndex:1], @"");
  XCTAssertTrue(706   ==  [message packedSint64AtIndex:1], @"");
  XCTAssertTrue(707   ==  [message packedFixed32AtIndex:1], @"");
  XCTAssertTrue(708   ==  [message packedFixed64AtIndex:1], @"");
  XCTAssertTrue(709   ==  [message packedSfixed32AtIndex:1], @"");
  XCTAssertTrue(710   ==  [message packedSfixed64AtIndex:1], @"");
  XCTAssertTrue(711   ==  [message packedFloatAtIndex:1], @"");
  XCTAssertTrue(712   ==  [message packedDoubleAtIndex:1], @"");
  XCTAssertTrue(NO ==  [message packedBoolAtIndex:1], @"");
  XCTAssertTrue(ForeignEnumForeignBaz ==  [message packedEnumAtIndex:1], @"");
}


+ (void) assertPackedFieldsSet:(TestPackedTypes*) message {
  [[[TestUtilities alloc] init] assertPackedFieldsSet:message];
}



+ (void) setPackedExtensions:(TestPackedExtensionsBuilder*) message {
  [message addExtension:[UnittestRoot packedInt32Extension   ] value:[NSNumber numberWithInteger: 601]];
  [message addExtension:[UnittestRoot packedInt64Extension   ] value:[NSNumber numberWithLongLong: 602L]];
  [message addExtension:[UnittestRoot packedUint32Extension  ] value:[NSNumber numberWithInteger: 603]];
  [message addExtension:[UnittestRoot packedUint64Extension  ] value:[NSNumber numberWithLongLong: 604L]];
  [message addExtension:[UnittestRoot packedSint32Extension  ] value:[NSNumber numberWithInteger: 605]];
  [message addExtension:[UnittestRoot packedSint64Extension  ] value:[NSNumber numberWithLongLong: 606L]];
  [message addExtension:[UnittestRoot packedFixed32Extension ] value:[NSNumber numberWithInteger: 607]];
  [message addExtension:[UnittestRoot packedFixed64Extension ] value:[NSNumber numberWithLongLong: 608L]];
  [message addExtension:[UnittestRoot packedSfixed32Extension] value:[NSNumber numberWithInteger: 609]];
  [message addExtension:[UnittestRoot packedSfixed64Extension] value:[NSNumber numberWithLongLong: 610L]];
  [message addExtension:[UnittestRoot packedFloatExtension   ] value:[NSNumber numberWithFloat: 611.0F]];
  [message addExtension:[UnittestRoot packedDoubleExtension  ] value:[NSNumber numberWithDouble: 612.0]];
  [message addExtension:[UnittestRoot packedBoolExtension    ] value:[NSNumber numberWithBool: YES]];
  [message addExtension:[UnittestRoot packedEnumExtension] value:[NSNumber numberWithInteger: ForeignEnumForeignBar]];
  // Add a second one of each field.
  [message addExtension:[UnittestRoot packedInt32Extension   ] value:[NSNumber numberWithInteger: 701]];
  [message addExtension:[UnittestRoot packedInt64Extension   ] value:[NSNumber numberWithLongLong: 702L]];
  [message addExtension:[UnittestRoot packedUint32Extension  ] value:[NSNumber numberWithInteger: 703]];
  [message addExtension:[UnittestRoot packedUint64Extension  ] value:[NSNumber numberWithLongLong: 704L]];
  [message addExtension:[UnittestRoot packedSint32Extension  ] value:[NSNumber numberWithInteger: 705]];
  [message addExtension:[UnittestRoot packedSint64Extension  ] value:[NSNumber numberWithLongLong: 706L]];
  [message addExtension:[UnittestRoot packedFixed32Extension ] value:[NSNumber numberWithInteger: 707]];
  [message addExtension:[UnittestRoot packedFixed64Extension ] value:[NSNumber numberWithLongLong: 708L]];
  [message addExtension:[UnittestRoot packedSfixed32Extension] value:[NSNumber numberWithInteger: 709]];
  [message addExtension:[UnittestRoot packedSfixed64Extension] value:[NSNumber numberWithLongLong: 710L]];
  [message addExtension:[UnittestRoot packedFloatExtension   ] value:[NSNumber numberWithFloat: 711.0F]];
  [message addExtension:[UnittestRoot packedDoubleExtension  ] value:[NSNumber numberWithDouble: 712.0]];
  [message addExtension:[UnittestRoot packedBoolExtension    ] value:[NSNumber numberWithBool: NO]];
  [message addExtension:[UnittestRoot packedEnumExtension] value:[NSNumber numberWithInteger:ForeignEnumForeignBaz]];
}


- (void) assertPackedExtensionsSet:(TestPackedExtensions*) message {
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedInt32Extension   ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedInt64Extension   ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedUint32Extension  ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedUint64Extension  ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedSint32Extension  ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedSint64Extension  ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedFixed32Extension ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedFixed64Extension ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedSfixed32Extension]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedSfixed64Extension]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedFloatExtension   ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedDoubleExtension  ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedBoolExtension    ]] count], @"");
  XCTAssertTrue(2 ==  [[message getExtension:[UnittestRoot packedEnumExtension]] count], @"");
  XCTAssertTrue(601   ==  [[[message getExtension:[UnittestRoot packedInt32Extension   ]] objectAtIndex: 0] integerValue], @"");
  XCTAssertTrue(602L  ==  [[[message getExtension:[UnittestRoot packedInt64Extension   ]] objectAtIndex: 0] longLongValue], @"");
  XCTAssertTrue(603   ==  [[[message getExtension:[UnittestRoot packedUint32Extension  ]] objectAtIndex: 0] integerValue], @"");
  XCTAssertTrue(604L  ==  [[[message getExtension:[UnittestRoot packedUint64Extension  ]] objectAtIndex: 0] longLongValue], @"");
  XCTAssertTrue(605   ==  [[[message getExtension:[UnittestRoot packedSint32Extension  ]] objectAtIndex: 0] integerValue], @"");
  XCTAssertTrue(606L  ==  [[[message getExtension:[UnittestRoot packedSint64Extension  ]] objectAtIndex: 0] longLongValue], @"");
  XCTAssertTrue(607   ==  [[[message getExtension:[UnittestRoot packedFixed32Extension ]] objectAtIndex: 0] integerValue], @"");
  XCTAssertTrue(608L  ==  [[[message getExtension:[UnittestRoot packedFixed64Extension ]] objectAtIndex: 0] longLongValue], @"");
  XCTAssertTrue(609   ==  [[[message getExtension:[UnittestRoot packedSfixed32Extension]] objectAtIndex: 0] integerValue], @"");
  XCTAssertTrue(610L  ==  [[[message getExtension:[UnittestRoot packedSfixed64Extension]] objectAtIndex: 0] longLongValue], @"");
  XCTAssertTrue(611.0F  ==  [[[message getExtension:[UnittestRoot packedFloatExtension   ]] objectAtIndex: 0] floatValue], @"");
  XCTAssertTrue(612.0  ==  [[[message getExtension:[UnittestRoot packedDoubleExtension  ]] objectAtIndex: 0] doubleValue], @"");
  XCTAssertTrue(YES  ==  [[[message getExtension:[UnittestRoot packedBoolExtension    ]] objectAtIndex: 0] boolValue], @"");
  XCTAssertTrue(ForeignEnumForeignBar == [[[message getExtension:[UnittestRoot packedEnumExtension]] objectAtIndex:0] integerValue], @"");
  XCTAssertTrue(701   ==  [[[message getExtension:[UnittestRoot packedInt32Extension   ]] objectAtIndex: 1] integerValue], @"");
  XCTAssertTrue(702L  ==  [[[message getExtension:[UnittestRoot packedInt64Extension   ]] objectAtIndex: 1] longLongValue], @"");
  XCTAssertTrue(703   ==  [[[message getExtension:[UnittestRoot packedUint32Extension  ]] objectAtIndex: 1] integerValue], @"");
  XCTAssertTrue(704L  ==  [[[message getExtension:[UnittestRoot packedUint64Extension  ]] objectAtIndex: 1] longLongValue], @"");
  XCTAssertTrue(705   ==  [[[message getExtension:[UnittestRoot packedSint32Extension  ]] objectAtIndex: 1] integerValue], @"");
  XCTAssertTrue(706L  ==  [[[message getExtension:[UnittestRoot packedSint64Extension  ]] objectAtIndex: 1] longLongValue], @"");
  XCTAssertTrue(707   ==  [[[message getExtension:[UnittestRoot packedFixed32Extension ]] objectAtIndex: 1] integerValue], @"");
  XCTAssertTrue(708L  ==  [[[message getExtension:[UnittestRoot packedFixed64Extension ]] objectAtIndex: 1] longLongValue], @"");
  XCTAssertTrue(709   ==  [[[message getExtension:[UnittestRoot packedSfixed32Extension]] objectAtIndex: 1] integerValue], @"");
  XCTAssertTrue(710L  ==  [[[message getExtension:[UnittestRoot packedSfixed64Extension]] objectAtIndex: 1] longLongValue], @"");
  XCTAssertTrue(711.0F  ==  [[[message getExtension:[UnittestRoot packedFloatExtension   ]] objectAtIndex: 1] floatValue], @"");
  XCTAssertTrue(712.0  ==  [[[message getExtension:[UnittestRoot packedDoubleExtension  ]] objectAtIndex: 1] doubleValue], @"");
  XCTAssertTrue(NO ==  [[[message getExtension:[UnittestRoot packedBoolExtension    ]] objectAtIndex: 1] boolValue], @"");
  XCTAssertTrue(ForeignEnumForeignBaz == [[[message getExtension:[UnittestRoot packedEnumExtension]] objectAtIndex:1] integerValue], @"");
}


+ (void) assertPackedExtensionsSet:(TestPackedExtensions*) message {
  [[[TestUtilities alloc] init] assertPackedExtensionsSet:message];
}


@end
