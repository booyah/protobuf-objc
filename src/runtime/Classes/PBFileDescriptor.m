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
#import "PBDescriptor.h"
#import "PBDescriptorPool+Internal.h"
#import "PBEnumDescriptor.h"
#import "PBExceptions.h"
#import "PBFieldDescriptor.h"
#import "PBFileDescriptor.h"
#import "PBGenericDescriptor.h"
#import "PBServiceDescriptor.h"

@implementation PBFileDescriptor

@synthesize proto = _proto;
@synthesize messageTypes = _messageTypes;
@synthesize enumTypes = _enumTypes;
@synthesize services = _services;
@synthesize extensions = _extensions;
@synthesize dependencies = _dependencies;
@synthesize pool = _pool;
@dynamic name;
@dynamic package;
@dynamic options;

+ (PBFileDescriptor *)buildFrom:(PBFileDescriptorProto *)proto
				   dependencies:(NSArray *)dependencies
{
	PBFileDescriptor *file = nil;

	if ([dependencies count] != proto.dependencyList.count)
	{
		[NSException raise:PBInvalidDescriptorException
					format:@"Dependencies don't match those listed in the FileDescriptorProto."];
	}

	for (NSUInteger i = 0; i < proto.dependencyList.count; ++i)
	{
		NSString *a = ((PBFileDescriptor *)[dependencies objectAtIndex:i]).name;
		NSString *b = [proto.dependencyList objectAtIndex:i];

		if (![a isEqualToString:b])
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"Dependencies don't match those listed in the FileDescriptorProto."];
		}
	}

	PBDescriptorPool *pool = [[PBDescriptorPool alloc] initWithDependencies:dependencies];
	if (pool)
	{
		file = [[PBFileDescriptor alloc] initWithProto:proto dependencies:dependencies pool:pool];
		[file crossLink];
		[pool release];
	}

	return [file autorelease];
}

- (void)dealloc
{
	[_proto release];
	[_messageTypes release];
	[_enumTypes release];
	[_services release];
	[_extensions release];
	[_dependencies release];
	[super dealloc];
}

- (NSString *)getName
{
	return _proto.name;
}

- (NSString *)getPackage
{
	return _proto.package;
}

- (PBFileOptions *)getOptions
{
	return _proto.options;
}

- (id<PBGenericDescriptor>)descriptorForName:(NSString *)name withType:(Class)type
{
	// Don't allow looking up nested types.
	if ([name rangeOfString:@":"].length > 0)
	{
		return nil;
	}

	NSString *fullName = name;

	NSString *package = self.package;
	if ([package length] > 0)
	{
		fullName = [NSString stringWithFormat:@"%@.%@", package, name];
	}

	id<PBGenericDescriptor> descriptor = [_pool descriptorNamed:fullName withType:type];
	if (descriptor && [descriptor.file isEqual:self])
	{
		return descriptor;
	}

	return nil;
}

- (PBDescriptor *)messageTypeWithName:(NSString *)name
{
	return [self descriptorForName:name withType:[PBDescriptor class]];
}

- (PBEnumDescriptor *)enumTypeWithName:(NSString *)name
{
	return [self descriptorForName:name withType:[PBEnumDescriptor class]];
}

- (PBServiceDescriptor *)serviceWithName:(NSString *)name
{
	return [self descriptorForName:name withType:[PBServiceDescriptor class]];
}

- (PBFieldDescriptor *)extensionWithName:(NSString *)name
{
	return [self descriptorForName:name withType:[PBFieldDescriptor class]];
}

@end