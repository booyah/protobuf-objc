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

#import <Foundation/Foundation.h>

NSString * const PBArrayTypeMismatchException;
NSString * const PBArrayNumberExpectedException;

typedef enum _PBArrayValueType
{
	PBArrayValueTypeBool,
	PBArrayValueTypeInt32,
	PBArrayValueTypeUInt32,
	PBArrayValueTypeInt64,
	PBArrayValueTypeUInt64,
	PBArrayValueTypeFloat,
	PBArrayValueTypeDouble,
	PBArrayValueTypeObject,
} PBArrayValueType;

@interface PBArray : NSObject
{
@private
	PBArrayValueType	_valueType;
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
- (float_t)floatAtIndex:(NSUInteger)index;
- (double)doubleAtIndex:(NSUInteger)index;

@property (nonatomic,assign,readonly) PBArrayValueType valueType;
@property (nonatomic,assign,readonly) const void * data;
@property (nonatomic,assign,readonly,getter=count) NSUInteger count;

@end

@interface PBArray (PBArrayCreation)

+ (id)arrayWithValues:(const void *)values count:(NSUInteger)count valueType:(PBArrayValueType)valueType;
+ (id)arrayWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType;
- (id)initWithValues:(const void *)values count:(NSUInteger)count valueType:(PBArrayValueType)valueType;
- (id)initWithArray:(NSArray *)array valueType:(PBArrayValueType)valueType;

@end