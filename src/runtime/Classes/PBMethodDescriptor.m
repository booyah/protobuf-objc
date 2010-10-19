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

@implementation PBMethodDescriptor

@synthesize index = _index;
@synthesize proto = _proto;
@synthesize fullName = _fullName;
@synthesize file = _file;
@synthesize service = _service;
@synthesize inputType = _inputType;
@synthesize outputType = _outputType;
@dynamic name;
@dynamic options;

- (void)dealloc
{
	[_proto release];
	[_fullName release];
	[_file release];
	[_service release];
	[_inputType release];
	[_outputType release];
	[super dealloc];
}

- (NSString *)name
{
	return _proto.name;
}

- (PBMethodOptions *)options
{
	return _proto.options;
}

@end