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
//
// Author: Jon Parise <jon@booyah.com>

#import <Foundation/Foundation.h>

extern NSString * const PBArrayTypeMismatchException;
extern NSString * const PBArrayNumberExpectedException;
extern NSString * const PBArrayAllocationFailureException;

typedef enum _PBArrayValueType
{
	PBArrayValueTypeObject,
	PBArrayValueTypeBool,
	PBArrayValueTypeInt32,
	PBArrayValueTypeUInt32,
	PBArrayValueTypeInt64,
	PBArrayValueTypeUInt64,
	PBArrayValueTypeFloat,
	PBArrayValueTypeDouble,
} PBArrayValueType;

// PBArray is an immutable array class that's optimized for storing primitive
// values.  All values stored in an PBArray instance must have the same type
// (PBArrayValueType).  Object values (PBArrayValueTypeObject) are retained.
@interface PBArray : NSObject <NSCopying, NSFastEnumeration>
{
@protected
	PBArrayValueType	_valueType;
	unsigned long			_capacity;
	unsigned long			_count;
	void *				_data;

}

- (unsigned long)count;
- (id)objectAtIndex:(unsigned long)index;
- (BOOL)boolAtIndex:(unsigned long)index;
- (long)int32AtIndex:(unsigned long)index;
- (unsigned long)uint32AtIndex:(unsigned long)index;
- (long long)int64AtIndex:(unsigned long)index;
- (unsigned long long)uint64AtIndex:(unsigned long)index;
- (Float32)floatAtIndex:(unsigned long)index;
- (Float64)doubleAtIndex:(unsigned long)index;
- (BOOL)isEqualToArray:(PBArray *)array;
- (void)enumerateObjectsUsingBlock:(void (^)(id obj, unsigned long idx, BOOL *stop))block;
- (id)firstObject;
- (id)lastObject;
- (id)objectAtIndexedSubscript:(unsigned long)idx;

@property (nonatomic,assign,readonly) PBArrayValueType valueType;
@property (nonatomic,assign,readonly) const void * data;
@property (nonatomic,assign,readonly,getter=count) unsigned long count;

@end

@interface PBArray (PBArrayExtended)

- (id)arrayByAppendingArray:(PBArray *)array;

@end

@interface PBArray (PBArrayCreation)

+ (id)arrayWithValueType:(PBArrayValueType)valueType;
+ (id)arrayWithValues:(const void *)values count:(unsigned long)count valueType:(PBArrayValueType)valueType;
+ (id)arrayWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType;
- (id)initWithValueType:(PBArrayValueType)valueType;
- (id)initWithValues:(const void *)values count:(unsigned long)count valueType:(PBArrayValueType)valueType;
- (id)initWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType;

@end

// PBAppendableArray extends PBArray with the ability to append new values to
// the end of the array.
@interface PBAppendableArray : PBArray

- (void)addObject:(id)value;
- (void)addBool:(BOOL)value;
- (void)addInt32:(long)value;
- (void)addUint32:(unsigned long)value;
- (void)addInt64:(long long)value;
- (void)addUint64:(unsigned long long)value;
- (void)addFloat:(Float32)value;
- (void)addDouble:(Float64)value;

- (void)appendArray:(PBArray *)array;
- (void)appendValues:(const void *)values count:(unsigned long)count;

@end
