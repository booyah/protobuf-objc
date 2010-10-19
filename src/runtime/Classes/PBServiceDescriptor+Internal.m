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

#import "PBServiceDescriptor+Internal.h"

#import "Descriptor.pb.h"
#import "PBDescriptorPool+Internal.h"
#import "PBMethodDescriptor+Internal.h"

@implementation PBServiceDescriptor (PBServiceDescriptorCreation)

- (id)initWithProto:(PBServiceDescriptorProto *)proto
			   file:(PBFileDescriptor *)file
			  index:(NSInteger)index
{
	if (self = [super init])
	{
		_index = index;
		_proto = [proto retain];
		_file = [file retain];

		_fullName = [PBComputeFullName(file, nil, proto.name) retain];
	}

	return self;
}

- (void)crossLink
{
}

- (void)setProto:(PBGeneratedMessage *)proto
{
	[proto retain];
	[_proto release];
	_proto = (PBServiceDescriptorProto *)proto;

	for (NSUInteger i = 0; i < _methods.count; ++i)
	{
		PBMethodDescriptor *method = [_methods objectAtIndex:i];
		method.proto = [_proto.methodList objectAtIndex:i];
	}
}

@end