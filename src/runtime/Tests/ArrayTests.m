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

- (void)testCount
{
	const int32_t kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	STAssertEquals([array count], (NSUInteger)3, nil);
	STAssertEquals(array.count, (NSUInteger)3, nil);
	[array release];
}

- (void)testValueType
{
	const int32_t kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	STAssertEquals(array.valueType, PBArrayValueTypeInt32, nil);
	[array release];
}

- (void)testPrimitiveAccess
{
	const int32_t kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	STAssertEquals([array int32AtIndex:1], 2, nil);
	[array release];
}

- (void)testObjectAccess
{
	const id kValues[1] = { [NSString stringWithFormat:@"Test"] };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:1 valueType:PBArrayValueTypeObject];
	STAssertTrue([[array objectAtIndex:0] isEqualToString:@"Test"], nil);
	[array release];
}

- (void)testTypeMismatchException
{
	const int32_t kValues[3] = { 1, 2, 3 };
	PBArray *array = [[PBArray alloc] initWithValues:kValues count:3 valueType:PBArrayValueTypeInt32];
	STAssertThrowsSpecificNamed([array objectAtIndex:0], NSException, PBArrayTypeMismatchException, nil);
	[array release];
}

- (void)testNumberExpectedException
{
	NSArray *objects = [[NSArray alloc] initWithObjects:@"Test", nil];
	STAssertThrowsSpecificNamed([[PBArray alloc] initWithArray:objects valueType:PBArrayValueTypeInt32],
								NSException, PBArrayNumberExpectedException, nil);
	[objects release];
}

@end