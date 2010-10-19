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
#import "PBDescriptorPool.h"
#import "PBEnumDescriptor.h"
#import "PBFieldDescriptor.h"
#import "PBFileDescriptor.h"

@implementation PBDescriptor

@synthesize proto = _proto;
@synthesize fullName = _fullName;
@synthesize file = _file;
@synthesize containingType = _containingType;
@synthesize nestedTypes = _nestedTypes;
@synthesize enumTypes = _enumTypes;
@synthesize fields = _fields;
@synthesize extensions = _extensions;
@dynamic name;
@dynamic options;

- (void)dealloc
{
	[_proto release];
	[_fullName release];
	[_file release];
	[_containingType release];
	[_nestedTypes release];
	[_enumTypes release];
	[_fields release];
	[_extensions release];
	[super dealloc];
}

- (NSString *)name
{
	return _proto.name;
}

- (PBMessageOptions *)options
{
	return _proto.options;
}

- (BOOL)isExtensionNumber:(NSInteger)number
{
	for (PBDescriptorProto_ExtensionRange *range in _proto.extensionRangeList)
	{
		if (range.start <= number && number < range.end)
		{
			return YES;
		}
	}

	return NO;
}

- (PBFieldDescriptor *)fieldNamed:(NSString *)name
{
	NSString *fullName = [NSString stringWithFormat:@"%@.%@", _fullName, name];
	return [_file.pool descriptorNamed:fullName withType:[PBFieldDescriptor class]];
}

- (PBDescriptor *)nestedTypeNamed:(NSString *)name
{
	NSString *fullName = [NSString stringWithFormat:@"%@.%@", _fullName, name];
	return [_file.pool descriptorNamed:fullName withType:[PBDescriptor class]];
}

- (PBEnumDescriptor *)enumTypeNamed:(NSString *)name
{
	NSString *fullName = [NSString stringWithFormat:@"%@.%@", _fullName, name];
	return [_file.pool descriptorNamed:fullName withType:[PBEnumDescriptor class]];
}

@end