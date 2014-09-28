// Protocol Buffers for Objective C
//
// Copyright 2010 Booyah Inc.
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

#import "ArrayTests.h"

#import "PBArray.h"

@implementation ArrayTests

#pragma mark PBArray

- (void)testfilterArray
{
	PBAppendableArray *array = [[PBAppendableArray alloc] initWithArray:@[@2, @3, @4, @5, @7, @77] valueType:PBArrayValueTypeInt32];
	PBArray *filter = [array filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self.integerValue >= 5"]];
	NSLog(@"%@",filter);
	XCTAssertEqual([filter count], (NSUInteger)3);
	
	XCTAssertEqual((((NSNumber *)filter[0]).integerValue), 5);
	XCTAssertEqual((((NSNumber *)filter[1]).integerValue), 7);
	XCTAssertEqual((((NSNumber *)filter[2]).integerValue), 77);
	
}

- (void)testCount
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	XCTAssertEqual([array count], (NSUInteger)3);
	XCTAssertEqual(array.count, (NSUInteger)3);

}

- (void)testValueType
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	XCTAssertEqual(array.valueType, PBArrayValueTypeInt32);
}

- (void)testPrimitiveAccess
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	XCTAssertEqual([array int32AtIndex:1], (SInt32)2);

}

- (void)testObjectAccess
{
	PBArray *array = [[PBArray alloc] initWithArray:@[@2] valueType:PBArrayValueTypeInt32];
	XCTAssertTrue([array[0] integerValue]==2);

}

- (void)testEmpty
{
	PBArray *array = [[PBArray alloc] init];
	XCTAssertEqual(array.count, (NSUInteger)0);
	XCTAssertEqual(array.valueType,PBArrayValueTypeBool);
	XCTAssertEqual(array.data, (const void *)nil);
	XCTAssertThrowsSpecificNamed([array boolAtIndex:0], NSException, NSRangeException, @"");

}

- (void)testCopy
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *original = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	PBArray *copy = [original copy];
	XCTAssertEqual(original.valueType, copy.valueType);
	XCTAssertEqual(original.count, copy.count);
	XCTAssertEqual([original int32AtIndex:1], [copy int32AtIndex:1]);

}

- (void)testCopyObjects
{
	const id kValues[1] = { @2 };
	PBArray *original = [[PBArray alloc] initWithValues:kValues count:1 valueType:PBArrayValueTypeInt32];
	PBArray *copy = [original copy];
	XCTAssertEqual(original.valueType, copy.valueType);
	XCTAssertEqual(original.count, copy.count);
	XCTAssertEqual([original[0] integerValue], [copy[0] integerValue]);
}

- (void)testFastEnumeration
{
  NSArray *arrayFirst =  @[@1, @2];
	PBArray *array = [[PBArray alloc] initWithArray:arrayFirst valueType:PBArrayValueTypeInt32];

	__block NSUInteger count = 0;
	[array enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
      count = idx;
  }];
	XCTAssertEqual(count, (UInt32)1);


}

- (void)testArrayAppendingArray
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *a = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	PBArray *b = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];

  PBArray *copy = [a arrayByAppendingArray:b];
	XCTAssertEqual(copy.valueType, a.valueType);
	XCTAssertEqual(copy.count, a.count + b.count);
}

- (void)testArrayAppendingArrayObjects
{
	const id kValues[1] = { @1 };
	PBArray *a = [[PBArray alloc] initWithValues:kValues count:1 valueType:PBArrayValueTypeInt32];
	PBArray *b = [[PBArray alloc] initWithValues:kValues count:1 valueType:PBArrayValueTypeInt32];

  PBArray *copy = [a arrayByAppendingArray:b];
	XCTAssertEqual(copy.valueType, a.valueType);
	XCTAssertEqual(copy.count, a.count + b.count);

}

- (void)testAppendArrayTypeException
{
	const SInt32 kValuesA[3] = { 1, 2, 3 };
	const SInt64 kValuesB[3] = { 1, 2, 3 };
	PBArray *a = [[PBArray alloc] initWithValues:kValuesA count:3 valueType:PBArrayValueTypeInt32];
	PBArray *b = [[PBArray alloc] initWithValues:kValuesB count:3 valueType:PBArrayValueTypeInt64];
	XCTAssertThrowsSpecificNamed([a arrayByAppendingArray:b], NSException, PBArrayTypeMismatchException, @"");

}

- (void)testRangeException
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	XCTAssertFalse(array[10] != nil);

}

- (void)testTypeMismatchException
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	XCTAssertThrowsSpecificNamed([array boolAtIndex:0], NSException, PBArrayTypeMismatchException, @"");

}

- (void)testNumberExpectedException
{
	NSArray *objects = [[NSArray alloc] initWithObjects:@"Test", nil];
	XCTAssertThrowsSpecificNamed([[PBArray alloc] initWithArray:objects valueType:PBArrayValueTypeInt32],
								NSException, PBArrayNumberExpectedException, @"");

}

#pragma mark PBAppendableArray

- (void)testAddValue
{
	PBAppendableArray *array = [[PBAppendableArray alloc] initWithValueType:PBArrayValueTypeInt32];
	[array addInt32:1];
	[array addInt32:4];
	XCTAssertEqual(array.count, (NSUInteger)2);
	XCTAssertThrowsSpecificNamed([array addBool:NO], NSException, PBArrayTypeMismatchException, @"");

}

- (void)testAddObject
{
	PBAppendableArray *array = [[PBAppendableArray alloc] initWithValueType:PBArrayValueTypeInt32];
	[array addInt32:1];
	[array addInt32:2];
	XCTAssertEqual(array.count, (NSUInteger)2);
	XCTAssertThrowsSpecificNamed([array addBool:NO], NSException, PBArrayTypeMismatchException, @"");

}

- (void)testAppendArray
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *source = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	PBAppendableArray *array = [[PBAppendableArray alloc] initWithValueType:PBArrayValueTypeInt32];
	[array appendArray:source];
  XCTAssertEqual(array.count, source.count);
	XCTAssertEqual([array int32AtIndex:1], (SInt32)2);

}

- (void)testAppendValues
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBAppendableArray *array = [[PBAppendableArray alloc] initWithValueType:PBArrayValueTypeInt32];
	[array appendValues:kValues count:3];
	XCTAssertEqual(array.count, (NSUInteger)3);
	XCTAssertEqual([array int32AtIndex:1], (SInt32)2);

}

- (void)testEqualValues
{
	const SInt32 kValues[3] = { 1, 2, 3 };
	PBArray *array1 = [[PBArray alloc] initWithValues:kValues count:2 valueType:PBArrayValueTypeInt32];

	// Test self equality.
	XCTAssertEqualObjects(array1, array1);

	PBArray *array2 = [[PBArray alloc] initWithValues:kValues count:2 valueType:PBArrayValueTypeInt32];
	// Test other equality.
	XCTAssertEqualObjects(array1, array2);

	// Test non equality of nil.
	XCTAssertFalse([array1 isEqual:nil]);

	// Test non equality of other object type.
	XCTAssertFalse([array1 isEqual:@""]);

	// Test non equality of arrays of different sizes with same prefix.
	PBArray *array3 = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	XCTAssertFalse([array1 isEqual:array3]);

	// Test non equality of arrays of same sizes with different contents.
	const SInt32 kValues2[2] = { 2, 1 };
	PBArray *array4 = [[PBArray alloc] initWithValues:kValues2 count:2 valueType:PBArrayValueTypeInt32];
	XCTAssertFalse([array1 isEqual:array4]);

}

@end