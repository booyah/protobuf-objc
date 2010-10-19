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

#import "PBDescriptor+Internal.h"

#import "Descriptor.pb.h"
#import "PBDescriptorPool+Internal.h"
#import "PBEnumDescriptor+Internal.h"
#import "PBFieldDescriptor+Internal.h"
#import "PBFileDescriptor.h"

@implementation PBDescriptor (PBDescriptorCreation)

- (id)initWithProto:(PBDescriptorProto *)proto
			   file:(PBFileDescriptor *)file
			 parent:(PBDescriptor *)parent
			  index:(NSInteger)index
{
	if (self = [super init])
	{
		_index = index;
		_proto = [proto retain];
		_file = [file retain];
		_containingType = [parent retain];

		_fullName = [PBComputeFullName(file, parent, proto.name) retain];

		_nestedTypes = [[NSMutableArray alloc] initWithCapacity:proto.nestedTypeList.count];
		for (NSUInteger i = 0; i < proto.nestedTypeList.count; ++i)
		{
			PBDescriptorProto *p = [proto.nestedTypeList objectAtIndex:i];
			PBDescriptor *d = [[PBDescriptor alloc] initWithProto:p file:file parent:self index:i];
			[_nestedTypes addObject:d];
			[d release];
		}

		_enumTypes = [[NSMutableArray alloc] initWithCapacity:proto.enumTypeList.count];
		for (NSUInteger i = 0; i < proto.enumTypeList.count; ++i)
		{
			PBEnumDescriptorProto *p = [proto.enumTypeList objectAtIndex:i];
			PBEnumDescriptor *d = [[PBEnumDescriptor alloc] initWithProto:p file:file parent:self index:i];
			[_enumTypes addObject:d];
			[d release];
		}		

		_fields = [[NSMutableArray alloc] initWithCapacity:proto.fieldList.count];
		for (NSUInteger i = 0; i < proto.fieldList.count; ++i)
		{
			PBFieldDescriptorProto *p = [proto.fieldList objectAtIndex:i];
			PBFieldDescriptor *d = [[PBFieldDescriptor alloc] initWithProto:p file:file parent:self index:i isExtension:NO];
			[_fields addObject:d];
			[d release];
		}

		_extensions = [[NSMutableArray alloc] initWithCapacity:proto.extensionList.count];
		for (NSUInteger i = 0; i < proto.extensionList.count; ++i)
		{
			PBFieldDescriptorProto *p = [proto.extensionList objectAtIndex:i];
			PBFieldDescriptor *d = [[PBFieldDescriptor alloc] initWithProto:p file:file parent:self index:i isExtension:YES];
			[_extensions addObject:d];
			[d release];
		}
		
		[_file.pool addSymbol:self];
	}

	return self;
}

- (void)crossLink
{
	for (PBDescriptor *descriptor in _nestedTypes)
	{
		[descriptor crossLink];
	}
	
	for (PBFieldDescriptor *field in _fields)
	{
		[field crossLink];
	}
	
	for (PBFieldDescriptor *extension in _extensions)
	{
		[extension crossLink];
	}
}

- (void)setProto:(PBGeneratedMessage *)proto
{
	[proto retain];
	[_proto release];
	proto = _proto;
	
	for (NSUInteger i = 0; i < _nestedTypes.count; ++i)
	{
		PBDescriptor *d = [_nestedTypes objectAtIndex:i];
		d.proto = [_proto.nestedTypeList objectAtIndex:i];
	}
	
	for (NSUInteger i = 0; i < _enumTypes.count; ++i)
	{
		PBEnumDescriptor *d = [_enumTypes objectAtIndex:i];
		d.proto = [_proto.enumTypeList objectAtIndex:i];
	}

	for (NSUInteger i = 0; i < _fields.count; ++i)
	{
		PBFieldDescriptor *d = [_fields objectAtIndex:i];
		d.proto = [_proto.fieldList objectAtIndex:i];
	}

	for (NSUInteger i = 0; i < _extensions.count; ++i)
	{
		PBFieldDescriptor *d = [_extensions objectAtIndex:i];
		d.proto = [_proto.extensionList objectAtIndex:i];
	}
}

@end