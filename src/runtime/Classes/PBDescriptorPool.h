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

@class PBEnumValueDescriptor;
@class PBFieldDescriptor;
@class PBFileDescriptor;
@protocol PBGenericDescriptor;

@interface PBDescriptorPool : NSObject
{
@private
	NSMutableArray *		_dependencies;
	NSMutableDictionary *	_descriptors;
	NSMutableDictionary *	_fields;
	NSMutableDictionary *	_enumValues;
}

@property (nonatomic,assign,readonly) NSDictionary * fields;
@property (nonatomic,assign,readonly) NSDictionary * enumValues;

- (void)addSymbol:(id<PBGenericDescriptor>)descriptor;
- (void)addPackage:(PBFileDescriptor *)file withName:(NSString *)fullName;
- (void)addField:(PBFieldDescriptor *)field;
- (void)addEnumValue:(PBEnumValueDescriptor *)enumValue;

- (id<PBGenericDescriptor>)descriptorNamed:(NSString *)fullName;
- (id<PBGenericDescriptor>)descriptorNamed:(NSString *)fullName withType:(Class)type;
- (id<PBGenericDescriptor>)descriptorNamed:(NSString *)fullName relativeTo:(id<PBGenericDescriptor>)parent;

@end

@interface PBDescriptorPoolCompositeKey : NSObject <NSCopying>
{
@private
	id<PBGenericDescriptor>	_descriptor;
	NSInteger				_number;
}

- (id)initWithDescriptor:(id<PBGenericDescriptor>)descriptor andNumber:(NSInteger)number;

@end