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

@class PBDescriptor;
@class PBDescriptorPool;
@class PBEnumDescriptor;
@class PBFieldDescriptor;
@class PBFileDescriptorProto;
@class PBFileOptions;
@class PBServiceDescriptor;

@interface PBFileDescriptor : NSObject
{
@private
	PBFileDescriptorProto *		_proto;
	NSMutableArray *			_messageTypes;
	NSMutableArray *			_enumTypes;
	NSMutableArray *			_services;
	NSMutableArray *			_extensions;
	NSArray *					_dependencies;
	PBDescriptorPool *			_pool;
}

@property (nonatomic,retain,readonly)	PBGeneratedMessage *	proto;
@property (nonatomic,retain,readonly)	NSArray *				messageTypes;
@property (nonatomic,retain,readonly)	NSArray *				enumTypes;
@property (nonatomic,retain,readonly)	NSArray *				services;
@property (nonatomic,retain,readonly)	NSArray *				extensions;
@property (nonatomic,retain,readonly)	NSArray *				dependencies;
@property (nonatomic,retain,readonly)	PBDescriptorPool *		pool;
@property (nonatomic,readonly)			NSString *				name;
@property (nonatomic,readonly)			NSString *				package;
@property (nonatomic,readonly)			PBFileOptions *			options;

+ (PBFileDescriptor *)buildFrom:(PBFileDescriptorProto *)proto
				   dependencies:(NSArray *)dependencies;

- (PBDescriptor *)messageTypeWithName:(NSString *)name;
- (PBEnumDescriptor *)enumTypeWithName:(NSString *)name;
- (PBServiceDescriptor *)serviceWithName:(NSString *)name;
- (PBFieldDescriptor *)extensionWithName:(NSString *)name;

@end