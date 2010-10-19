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

#import "PBFileDescriptor+Internal.h"

#import "Descriptor.pb.h"
#import "PBDescriptor+Internal.h"
#import "PBDescriptorPool.h"
#import "PBEnumDescriptor+Internal.h"
#import "PBFieldDescriptor+Internal.h"
#import "PBServiceDescriptor+Internal.h"

@implementation PBFileDescriptor (PBFileDescriptorCreation)

- (id)initWithProto:(PBFileDescriptorProto *)proto
	   dependencies:(NSArray *)dependencies
			   pool:(PBDescriptorPool *)pool
{
	if (self = [super init])
	{
		_proto = [proto retain];
		_pool = [pool retain];
		_dependencies = [dependencies copy];
		
		[_pool addPackage:self withName:self.package];
		
		_messageTypes = [[NSMutableArray alloc] initWithCapacity:_proto.messageTypeList.count];
		for (NSUInteger i = 0; i < _proto.messageTypeList.count; ++i)
		{
			PBDescriptorProto *p = [_proto.messageTypeList objectAtIndex:i];
			PBDescriptor *d = [[PBDescriptor alloc] initWithProto:p file:self parent:nil index:i];
			[_messageTypes addObject:d];
			[d release];
		}

		_enumTypes = [[NSMutableArray alloc] initWithCapacity:_proto.enumTypeList.count];
		for (NSUInteger i = 0; i < _proto.enumTypeList.count; ++i)
		{
			PBEnumDescriptorProto *p = [_proto.enumTypeList objectAtIndex:i];
			PBEnumDescriptor *d = [[PBEnumDescriptor alloc] initWithProto:p file:self parent:nil index:i];
			[_enumTypes addObject:d];
			[d release];
		}
	
		_services = [[NSMutableArray alloc] initWithCapacity:_proto.serviceList.count];
		for (NSUInteger i = 0; i < _proto.serviceList.count; ++i)
		{
			PBServiceDescriptorProto *p = [_proto.serviceList objectAtIndex:i];
			PBServiceDescriptor *d = [[PBServiceDescriptor alloc] initWithProto:p file:self index:i];
			[_services addObject:d];
			[d release];
		}
	
		_extensions = [[NSMutableArray alloc] initWithCapacity:_proto.extensionList.count];
		for (NSUInteger i = 0; i < _proto.extensionList.count; ++i)
		{
			PBFieldDescriptorProto *p = [_proto.extensionList objectAtIndex:i];
			PBFieldDescriptor *d = [[PBFieldDescriptor alloc] initWithProto:p file:self parent:nil index:i isExtension:YES];
			[_extensions addObject:d];
			[d release];
		}
	}

	return self;
}

- (void)crossLink
{
	for (PBDescriptor *messageType in _messageTypes)
	{
		[messageType crossLink];
	}
	
	for (PBServiceDescriptor *service in _services)
	{
		[service crossLink];
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
	_proto = (PBFileDescriptorProto *)proto;

	for (NSUInteger i = 0; i < _messageTypes.count; ++i)
	{
		PBDescriptor *d = [_messageTypes objectAtIndex:i];
		d.proto = [_proto.messageTypeList objectAtIndex:i];
	}
	
	for (NSUInteger i = 0; i < _enumTypes.count; ++i)
	{
		PBEnumDescriptor *d = [_enumTypes objectAtIndex:i];
		d.proto = [_proto.enumTypeList objectAtIndex:i];
	}
	
	for (NSUInteger i = 0; i < _services.count; ++i)
	{
		PBServiceDescriptor *d = [_services objectAtIndex:i];
		d.proto = [_proto.serviceList objectAtIndex:i];
	}
	
	for (NSUInteger i = 0; i < _extensions.count; ++i)
	{
		PBFieldDescriptor *d = [_extensions objectAtIndex:i];
		d.proto = [_proto.extensionList objectAtIndex:i];
	}
}

@end