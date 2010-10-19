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

#import "PBFieldDescriptor.h"

#import "Descriptor.pb.h"
#import "PBExceptions.h"

@implementation PBFieldDescriptor

@synthesize index = _index;
@synthesize proto = _proto;
@synthesize fullName = _fullName;
@synthesize file = _file;
@synthesize type = _type;
@synthesize extensionScope = _extensionScope;
@synthesize containingType = _containingType;
@synthesize messageType = _messageType;
@synthesize enumType = _enumType;
@synthesize defaultValue = _defaultValue;
@dynamic nativeType;
@dynamic name;
@dynamic number;
@dynamic options;
@dynamic required;
@dynamic optional;
@dynamic repeated;
@dynamic packed;
@dynamic packable;
@dynamic extension;

- (void)dealloc
{
	[_proto release];
	[_fullName release];
	[_file release];
	[_extensionScope release];
	[_containingType release];
	[_messageType release];
	[_enumType release];
	[_defaultValue release];
	[super dealloc];
}

- (NSComparisonResult)compare:(PBFieldDescriptor *)other
{
	if (![other isKindOfClass:[PBFieldDescriptor class]])
	{
		NSString *reason = [NSString stringWithFormat:@"PBFieldDescriptors can only be compared to other PBFieldDescriptors for fields of the same message type"];
		@throw [NSException exceptionWithName:@"" reason:reason userInfo:nil];
	}

	const NSInteger diff = self.number - other.number;
	if (diff < 0)
	{
		return NSOrderedDescending;
	}
	else if (diff > 0)
	{
		return NSOrderedAscending;
	}

	return NSOrderedSame;
}

- (PBObjCType)nativeType
{
	return PBTypeToObjCType(_type);
}

- (PBDescriptor *)extensionScope
{
	if (!self.extension)
	{
		[NSException raise:PBUnsupportedOperationException format:@"This field is not an extension."];
	}
	
	return _extensionScope;
}

- (PBDescriptor *)messageType
{
	if (self.nativeType != PBObjCTypeMessage)
	{
		[NSException raise:PBUnsupportedOperationException format:@"This field is not a message type."];
	}
	
	return _messageType;
}

- (PBEnumDescriptor *)enumType
{
	if (self.nativeType != PBObjCTypeEnum)
	{
		[NSException raise:PBUnsupportedOperationException format:@"This field is not an enum type."];
	}
	
	return _enumType;
}

- (NSObject *)defaultValue
{
	if (self.nativeType == PBObjCTypeMessage)
	{
		[NSException raise:PBUnsupportedOperationException format:@"defaultValue called on an embedded message field."];
	}

	return _defaultValue;
}

- (NSString *)name
{
	return _proto.name;
}

- (NSInteger)number
{
	return _proto.number;
}

- (PBFieldOptions *)options
{
	return _proto.options;
}

- (BOOL)isRequired
{
	return (_proto.label == PBFieldDescriptorProto_LabelLabelRequired);
}

- (BOOL)isOptional
{
	return (_proto.label == PBFieldDescriptorProto_LabelLabelOptional);
}

- (BOOL)isRepeated
{
	return (_proto.label == PBFieldDescriptorProto_LabelLabelRepeated);
}

- (BOOL)isPacked
{
	return self.options.packed;
}

- (BOOL)isPackable
{
	return (self.repeated && PBIsTypePackable(_type));
}

- (BOOL)isExtension
{
	return [_proto hasExtendee];
}

@end