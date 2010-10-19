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
#import "PBTypes.h"

@class PBDescriptor;
@class PBEnumDescriptor;
@class PBFieldDescriptorProto;
@class PBFieldOptions;
@class PBFileDescriptor;

@interface PBFieldDescriptor : NSObject <PBGenericDescriptor>
{
@private
	NSInteger					_index;
	
	PBFieldDescriptorProto *	_proto;
	NSString *					_fullName;
	PBFileDescriptor *			_file;
	PBDescriptor *				_extensionScope;
	
	PBType						_type;
	PBDescriptor *				_containingType;
	PBDescriptor *				_messageType;
	PBEnumDescriptor *			_enumType;
	
	NSObject *					_defaultValue;
}

@property (nonatomic,assign,readonly)	NSInteger					index;
@property (nonatomic,retain,readonly)	PBGeneratedMessage *		proto;
@property (nonatomic,retain,readonly)	NSString *					fullName;
@property (nonatomic,retain,readonly)	PBFileDescriptor *			file;
@property (nonatomic,assign,readonly)	PBType						type;
@property (nonatomic,assign,readonly)	PBObjCType					nativeType;
@property (nonatomic,retain,readonly)	PBDescriptor *				extensionScope;
@property (nonatomic,retain,readonly)	PBDescriptor *				containingType;
@property (nonatomic,retain,readonly)	PBDescriptor *				messageType;
@property (nonatomic,retain,readonly)	PBEnumDescriptor *			enumType;
@property (nonatomic,retain,readonly)	NSObject *					defaultValue;

@property (nonatomic,retain,readonly)	NSString *			name;
@property (nonatomic,assign,readonly)	NSInteger			number;
@property (nonatomic,retain,readonly)	PBFieldOptions *	options;

@property (nonatomic,readonly,getter=isRequired)	BOOL	required;
@property (nonatomic,readonly,getter=isOptional)	BOOL	optional;
@property (nonatomic,readonly,getter=isRepeated)	BOOL	repeated;
@property (nonatomic,readonly,getter=isPacked)		BOOL	packed;
@property (nonatomic,readonly,getter=isPackable)	BOOL	packable;
@property (nonatomic,readonly,getter=isExtension)	BOOL	extension;

- (NSComparisonResult)compare:(PBFieldDescriptor *)other;

@end