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

#import "PBArray.h"

NSString * const PBArrayTypeMismatchException = @"PBArrayTypeMismatchException";
NSString * const PBArrayNumberExpectedException = @"PBArrayNumberExpectedException";

typedef void (*PBArrayValueSetter)(NSNumber *number, void *value);

static void PBArraySetBoolValue(NSNumber *number, void *value)
{
	*((BOOL *)value) = [number charValue];
}

static void PBArraySetInt32Value(NSNumber *number, void *value)
{
	*((int32_t *)value) = [number intValue];
}

static void PBArraySetUInt32Value(NSNumber *number, void *value)
{
	*((uint32_t *)value) = [number unsignedIntValue];
}

static void PBArraySetInt64Value(NSNumber *number, void *value)
{
	*((int64_t *)value) = [number longLongValue];
}

static void PBArraySetUInt64Value(NSNumber *number, void *value)
{
	*((uint64_t *)value) = [number unsignedLongLongValue];
}

static void PBArraySetFloatValue(NSNumber *number, void *value)
{
	*((float *)value) = [number floatValue];
}

static void PBArraySetDoubleValue(NSNumber *number, void *value)
{
	*((double *)value) = [number doubleValue];
}

typedef struct _PBArrayValueTypeInfo
{
	const char * const name;
	const size_t size;
	const PBArrayValueSetter setter;
} PBArrayValueTypeInfo;

static PBArrayValueTypeInfo PBValueTypes[] =
{
	{ "BOOL",		sizeof(BOOL),		PBArraySetBoolValue		},
	{ "int32_t",	sizeof(int32_t),	PBArraySetInt32Value	},
	{ "uint32_t",	sizeof(uint32_t),	PBArraySetUInt32Value	},
	{ "int64_t",	sizeof(int64_t),	PBArraySetInt64Value	},
	{ "uint64_t",	sizeof(uint64_t),	PBArraySetUInt64Value	},
	{ "float",		sizeof(float),		PBArraySetFloatValue	},
	{ "double",		sizeof(double),		PBArraySetDoubleValue	},
	{ "id",			sizeof(id),			NULL					},
};

#define PBArrayValueTypeName(type)		PBValueTypes[type].name
#define PBArrayValueTypeSize(type)		PBValueTypes[type].size
#define PBArrayValueTypeSetter(type)	PBValueTypes[type].setter

#define PBArrayValueTypeAssert(type) \
	if (__builtin_expect(_valueType != type, 0)) \
		[NSException raise:PBArrayTypeMismatchException \
					format:@"array value type mismatch (expected '%s')", PBArrayValueTypeName(type)];

#define PBArrayValueRangeAssert(index) \
	if (__builtin_expect(index >= _count, 0)) \
		[NSException raise:NSRangeException format: @"index (%lu) beyond bounds (%lu)", index, _count];

#define PBArrayNumberAssert(value) \
	if (__builtin_expect(![value isKindOfClass:[NSNumber class]], 0)) \
		[NSException raise:PBArrayNumberExpectedException format:@"NSNumber expected (got '%@')", [value class]];

#pragma mark -
#pragma mark PBArray

@implementation PBArray

@synthesize valueType = _valueType;
@dynamic data;

- (void)dealloc
{
	if (_data)
	{
		if (_valueType == PBArrayValueTypeObject)
		{
			for (NSUInteger i = 0; i < _count; ++i)
			{
				id object = ((id *)_data)[i];
				[object release];
			}
		}

		free(_data);
	}

	[super dealloc];
}

- (NSUInteger)count
{
	return _count;
}

- (const void *)data
{
	return _data;
}

- (id)objectAtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeObject);
	return ((id *)_data)[index];
}

- (BOOL)boolAtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeBool);
	return ((BOOL *)_data)[index];
}

- (int32_t)int32AtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeInt32);
	return ((int32_t *)_data)[index];
}

- (uint32_t)uint32AtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeUInt32);
	return ((uint32_t *)_data)[index];
}

- (int64_t)int64AtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeInt64);
	return ((int64_t *)_data)[index];
}

- (uint64_t)uint64AtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeUInt64);
	return ((uint64_t *)_data)[index];
}

- (float_t)floatAtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeFloat);
	return ((float *)_data)[index];
}

- (double)doubleAtIndex:(NSUInteger)index
{
	PBArrayValueRangeAssert(index);
	PBArrayValueTypeAssert(PBArrayValueTypeDouble);
	return ((double *)_data)[index];
}

@end

@implementation PBArray (PBArrayCreation)

+ (id)arrayWithValues:(const void *)values count:(NSUInteger)count valueType:(PBArrayValueType)valueType
{
	return [[[PBArray alloc] initWithValues:values count:count valueType:valueType] autorelease];
}

+ (id)arrayWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType
{
	return [[[PBArray alloc] initWithArray:array valueType:valueType] autorelease];
}

- (id)initWithCapacity:(NSUInteger)count valueType:(PBArrayValueType)valueType
{
	if (self = [super init])
	{
		_valueType = valueType;
		_count = count;

		_data = malloc(_count * PBArrayValueTypeSize(_valueType));
		if (_data == NULL)
		{
			[self release];
			self = nil;
		}
	}

	return self;
}

- (id)initWithValues:(const void *)values count:(NSUInteger)count valueType:(PBArrayValueType)valueType
{
	if (self = [self initWithCapacity:count valueType:valueType])
	{
		if (valueType == PBArrayValueTypeObject)
		{
			for (NSUInteger i = 0; i < count; ++i)
			{
				id object = ((id *)values)[i];
				[object retain];
			}
		}

		memcpy(_data, values, count * PBArrayValueTypeSize(_valueType));
	}

	return self;
}

- (id)initWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType
{
	if (self = [self initWithCapacity:[array count] valueType:valueType])
	{
		const size_t elementSize = PBArrayValueTypeSize(valueType);
		size_t offset = 0;

		if (valueType == PBArrayValueTypeObject)
		{
			for (id object in array)
			{
				*(id *)(_data + offset) = [object retain];
				offset += elementSize;
			}
		}
		else
		{
			PBArrayValueSetter setter = PBArrayValueTypeSetter(valueType);
			for (id object in array)
			{
				PBArrayNumberAssert(object);
				setter((NSNumber *)object, _data + offset);
				offset += elementSize;
			}
		}
	}

	return self;
}

@end