// Protocol Buffers for Objective C
//
// Copyright 2010 Booyah Inc.
// Copyright 2008 Cyrus Najmabadi
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

#import "WireFormatTests.h"

#import "TestUtilities.h"
#import "Unittest.pb.h"
#import "UnittestMset.pb.h"

@implementation WireFormatTests

- (void) testSerialization {
  TestAllTypes* message = [TestUtilities allSet];

  NSData* rawBytes = message.data;
  STAssertTrue(rawBytes.length == message.serializedSize, @"");

  TestAllTypes* message2 = [TestAllTypes parseFromData:rawBytes];

  [TestUtilities assertAllFieldsSet:message2];
}

- (void) testSerializationPacked {
  TestPackedTypes* message = [TestUtilities packedSet];

  NSData* rawBytes = message.data;
  STAssertTrue(rawBytes.length == message.serializedSize, @"");

  TestPackedTypes* message2 = [TestPackedTypes parseFromData:rawBytes];

  [TestUtilities assertPackedFieldsSet:message2];
}


- (void) testSerializeExtensions {
  // TestAllTypes and TestAllExtensions should have compatible wire formats,
  // so if we serealize a TestAllExtensions then parse it as TestAllTypes
  // it should work.

  TestAllExtensions* message = [TestUtilities allExtensionsSet];
  NSData* rawBytes = message.data;
  STAssertTrue(rawBytes.length == message.serializedSize, @"");

  TestAllTypes* message2 = [TestAllTypes parseFromData:rawBytes];

  [TestUtilities assertAllFieldsSet:message2];
}


- (void) testSerializePackedExtensions {
  // TestPackedTypes and TestPackedExtensions should have compatible wire
  // formats; check that they serialize to the same string.
  TestPackedExtensions* message = [TestUtilities packedExtensionsSet];
  NSData* rawBytes = message.data;

  TestPackedTypes* message2 = [TestUtilities packedSet];
  NSData* rawBytes2 = message2.data;

  STAssertEqualObjects(rawBytes, rawBytes2, @"");
}


- (void) testParseExtensions {
  // TestAllTypes and TestAllExtensions should have compatible wire formats,
  // so if we serealize a TestAllTypes then parse it as TestAllExtensions
  // it should work.

  TestAllTypes* message = [TestUtilities allSet];
  NSData* rawBytes = message.data;

  PBMutableExtensionRegistry* registry = [PBMutableExtensionRegistry registry];
  [TestUtilities registerAllExtensions:registry];

  TestAllExtensions* message2 =
  [TestAllExtensions parseFromData:rawBytes extensionRegistry:registry];

  [TestUtilities assertAllExtensionsSet:message2];
}


- (void) testExtensionsSerializedSize {
  STAssertTrue([TestUtilities allSet].serializedSize == [TestUtilities allExtensionsSet].serializedSize, @"");
}


- (void) testParsePackedExtensions {
  // Ensure that packed extensions can be properly parsed.
  TestPackedExtensions* message = [TestUtilities packedExtensionsSet];
  NSData* rawBytes = message.data;

  PBExtensionRegistry* registry = [TestUtilities extensionRegistry];

  TestPackedExtensions* message2 =
  [TestPackedExtensions parseFromData:rawBytes extensionRegistry:registry];

  [TestUtilities assertPackedExtensionsSet:message2];
}


- (void) assertFieldsInOrder:(NSData*) data {
  PBCodedInputStream* input = [PBCodedInputStream streamWithData:data];
  int32_t previousTag = 0;

  while (YES) {
    int32_t tag = [input readTag];
    if (tag == 0) {
      break;
    }

    STAssertTrue(tag > previousTag, @"");
    [input skipField:tag];
  }
}

@end
