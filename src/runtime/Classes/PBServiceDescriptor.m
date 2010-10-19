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
#import "PBDescriptorPool.h"
#import "PBFileDescriptor.h"
#import "PBMethodDescriptor.h"

@implementation PBServiceDescriptor

@synthesize index = _index;
@synthesize proto = _proto;
@synthesize fullName = _fullName;
@synthesize file = _file;
@synthesize methods = _methods;
@dynamic name;
@dynamic options;

- (void)dealloc
{
	[_proto release];
	[_fullName release];
	[_file release];
	[_methods release];
	[super dealloc];
}

- (NSString *)name
{
	return _proto.name;
}

- (PBServiceOptions *)options
{
	return _proto.options;
}

- (PBMethodDescriptor *)methodNamed:(NSString *)name
{
	NSString *symbol = [NSString stringWithFormat:@"%@.%@", _fullName, name];
	return [_file.pool descriptorNamed:symbol withType:[PBMethodDescriptor class]];
}

@end