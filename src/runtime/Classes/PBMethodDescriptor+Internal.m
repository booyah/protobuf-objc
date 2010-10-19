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

#import "PBMethodDescriptor+Internal.h"

#import "Descriptor.pb.h"

#import "PBDescriptor.h"
#import "PBDescriptorPool.h"
#import "PBExceptions.h"
#import "PBFileDescriptor.h"
#import "PBServiceDescriptor.h"

@implementation PBMethodDescriptor (PBMethodDescriptorCreation)

- (id)initWithProto:(PBMethodDescriptorProto *)proto
			   file:(PBFileDescriptor *)file
			 parent:(PBServiceDescriptor *)parent
			  index:(NSInteger)index
{
	if (self = [super init])
	{
		_index = index;
		_proto = [proto retain];
		_file = [file retain];
		_service = [parent retain];

		_fullName = [[NSString alloc] initWithFormat:@"%@.%@", parent.fullName, proto.name];

		[_file.pool addSymbol:self];
	}

	return self;
}

- (id<PBGenericDescriptor>)messageNamed:(NSString *)name
{
	id<PBGenericDescriptor> message = [_file.pool descriptorNamed:name relativeTo:self];
	if (![message isKindOfClass:[PBDescriptor class]])
	{
		[NSException raise:PBInvalidDescriptorException format:@"'%@' is not a message type.", name];
	}

	return message;
}

- (void)crossLink
{
	_inputType = [[self messageNamed:_proto.inputType] retain];
	_outputType = [[self messageNamed:_proto.outputType] retain]; 
}

@end