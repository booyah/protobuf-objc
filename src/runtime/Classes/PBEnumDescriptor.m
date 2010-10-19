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

#import "PBEnumDescriptor+Internal.h"

#import "Descriptor.pb.h"
#import "PBDescriptorPool.h"
#import "PBFileDescriptor.h"

@implementation PBEnumDescriptor

@synthesize index = _index;
@synthesize proto = _proto;
@synthesize fullName = _fullName;
@synthesize file = _file;
@synthesize containingType = _containingType;
@synthesize values = _values;
@dynamic name;
@dynamic options;

- (void)dealloc
{
	[_proto release];
	[_fullName release];
	[_file release];
	[_containingType release];
	[_values release];
	[super dealloc];
}

- (void)setProto:(PBGeneratedMessage *)newValue
{
	if (newValue != _proto)
	{
		[newValue retain];
		[_proto release];
		_proto = (PBEnumDescriptorProto *)newValue;

		for (PBEnumValueDescriptor *value in _values)
		{
			value.proto = newValue;
		}
	}
}

- (NSString *)name
{
	return _proto.name;
}

- (PBEnumOptions *)options
{
	return _proto.options;
}

- (PBEnumValueDescriptor *)valueNamed:(NSString *)name
{
	NSString *symbol = [NSString stringWithFormat:@"%@.@%", _fullName, name];
	return [_file.pool descriptorNamed:symbol withType:[PBEnumValueDescriptor class]];
}

- (PBEnumValueDescriptor *)valueNumbered:(NSInteger)number
{
	PBEnumValueDescriptor *descriptor = nil;

	PBDescriptorPoolCompositeKey *key = [[PBDescriptorPoolCompositeKey alloc]
										 initWithDescriptor:self andNumber:number];
	if (key)
	{
		descriptor = [_file.pool.enumValues objectForKey:key];
		[key release];
	}

	return descriptor;
}

@end

#pragma mark -

@implementation PBEnumValueDescriptor

@synthesize index = _index;
@synthesize proto = _proto;
@synthesize fullName = _fullName;
@synthesize file = _file;
@synthesize type = _type;
@dynamic name;
@dynamic number;
@dynamic options;

- (void)dealloc
{
	[_proto release];
	[_fullName release];
	[_file release];
	[_type release];
	[super dealloc];
}

- (NSString *)name
{
	return _proto.name;
}

- (NSInteger)number
{
	return _proto.number;
}

- (PBEnumValueOptions *)options
{
	return _proto.options;
}

@end