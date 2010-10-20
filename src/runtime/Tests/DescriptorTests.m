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

#import "DescriptorTests.h"

#import "Descriptor.pb.h"
#import "PBExceptions.h"
#import "PBFileDescriptor.h"
#import "PBTypes.h"

@implementation DescriptorTests

- (void)testFieldTypeEnumMapping
{
	STAssertEquals(PBTypeDouble, PBFieldDescriptorProto_TypeTypeDouble, @"Type values are out of sync");
	STAssertEquals(PBTypeSInt64, PBFieldDescriptorProto_TypeTypeSint64, @"Type values are out of sync");
}

- (void)testInvalidDescriptorException
{
	PBFieldDescriptorProto *field = [[[[[[[PBFieldDescriptorProto builder]
										setLabel:PBFieldDescriptorProto_LabelLabelOptional]
										setType:PBFieldDescriptorProto_TypeTypeInt32]
										setName:@"foo"]
										setNumber:-1]
										setDefaultValue:@"invalid"]
									 build];

	PBDescriptorProto *messageType = [[[[PBDescriptorProto builder]
										setName:@"Foo"]
										addField:field]
									  build];

	PBFileDescriptorProto *file = [[[[PBFileDescriptorProto builder]
										setName:@"foo.proto"]
										addMessageType:messageType]
								   build];

	STAssertThrowsSpecificNamed([PBFileDescriptor buildFrom:file dependencies:[NSArray array]],
								NSException, PBInvalidDescriptorException, nil);
}

@end