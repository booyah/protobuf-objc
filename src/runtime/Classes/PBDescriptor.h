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

#import "PBGenericDescriptor.h"

@class PBDescriptorProto;
@class PBEnumDescriptor;
@class PBFieldDescriptor;
@class PBFileDescriptor;
@class PBMessageOptions;

@interface PBDescriptor : NSObject <PBGenericDescriptor>
{
@private
	NSInteger				_index;
	PBDescriptorProto *		_proto;
	NSString *				_fullName;
	PBFileDescriptor *		_file;
	PBDescriptor *			_containingType;
	NSMutableArray *		_nestedTypes;
	NSMutableArray *		_enumTypes;
	NSMutableArray *		_fields;
	NSMutableArray *		_extensions;
}

@property (nonatomic,retain,readonly)	PBGeneratedMessage *	proto;
@property (nonatomic,retain,readonly)	NSString *				name;
@property (nonatomic,retain,readonly)	NSString *				fullName;
@property (nonatomic,retain,readonly)	PBFileDescriptor *		file;
@property (nonatomic,retain,readonly)	PBDescriptor *			containingType;
@property (nonatomic,retain,readonly)	PBMessageOptions *		options;
@property (nonatomic,retain,readonly)	NSArray *				nestedTypes;
@property (nonatomic,retain,readonly)	NSArray *				enumTypes;
@property (nonatomic,retain,readonly)	NSArray *				fields;
@property (nonatomic,retain,readonly)	NSArray *				extensions;

- (BOOL)isExtensionNumber:(NSInteger)number;

- (PBFieldDescriptor *)fieldNamed:(NSString *)name;
- (PBDescriptor *)nestedTypeNamed:(NSString *)name;
- (PBEnumDescriptor *)enumTypeNamed:(NSString *)name;

@end