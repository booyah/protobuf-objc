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
	NSUInteger			_capacity;
	NSUInteger			_count;
	void *				_data;
}

- (NSUInteger)count;
- (id)objectAtIndex:(NSUInteger)index;
- (BOOL)boolAtIndex:(NSUInteger)index;
- (int32_t)int32AtIndex:(NSUInteger)index;
- (uint32_t)uint32AtIndex:(NSUInteger)index;
- (int64_t)int64AtIndex:(NSUInteger)index;
- (uint64_t)uint64AtIndex:(NSUInteger)index;
- (Float32)floatAtIndex:(NSUInteger)index;
- (Float64)doubleAtIndex:(NSUInteger)index;
- (BOOL)isEqualToArray:(PBArray *)array;

@property (nonatomic,assign,readonly) PBArrayValueType valueType;
@property (nonatomic,assign,readonly) const void * data;
@property (nonatomic,assign,readonly,getter=count) NSUInteger count;

@end

@interface PBArray (PBArrayExtended)

- (id)arrayByAppendingArray:(PBArray *)array;

@end

@interface PBArray (PBArrayCreation)

+ (id)arrayWithValueType:(PBArrayValueType)valueType;
+ (id)arrayWithValues:(const void *)values count:(NSUInteger)count valueType:(PBArrayValueType)valueType;
+ (id)arrayWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType;
- (id)initWithValueType:(PBArrayValueType)valueType;
- (id)initWithValues:(const void *)values count:(NSUInteger)count valueType:(PBArrayValueType)valueType;
- (id)initWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType;

@end

// PBAppendableArray extends PBArray with the ability to append new values to
// the end of the array.
@interface PBAppendableArray : PBArray

- (void)addObject:(id)value;
- (void)addBool:(BOOL)value;
- (void)addInt32:(int32_t)value;
- (void)addUint32:(uint32_t)value;
- (void)addInt64:(int64_t)value;
- (void)addUint64:(uint64_t)value;
- (void)addFloat:(Float32)value;
- (void)addDouble:(Float64)value;

- (void)appendArray:(PBArray *)array;
- (void)appendValues:(const void *)values count:(NSUInteger)count;

@end
