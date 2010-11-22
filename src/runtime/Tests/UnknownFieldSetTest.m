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

#import "UnknownFieldSetTest.h"

#import "TestUtilities.h"
#import "Unittest.pb.h"

@implementation UnknownFieldSetTest

@synthesize allFields;
@synthesize allFieldsData;
@synthesize emptyMessage;
@synthesize unknownFields;

- (void) dealloc {
  self.allFields = nil;
  self.allFieldsData = nil;
  self.emptyMessage = nil;
  self.unknownFields = nil;
  [super dealloc];
}


- (void) setUp {
  self.allFields = [TestUtilities allSet];
  self.allFieldsData = [allFields data];
  self.emptyMessage = [TestEmptyMessage parseFromData:allFieldsData];
  self.unknownFields = emptyMessage.unknownFields;
}


- (id) init {
  if ((self = [super init])) {
    [self setUp];
  }
  return self;
}


- (PBField*) getField:(int32_t) number {
  return [unknownFields getField:number];
}


// Constructs a protocol buffer which contains fields with all the same
// numbers as allFieldsData except that each field is some other wire
// type.
- (NSData*) getBizarroData {
  PBUnknownFieldSet_Builder* bizarroFields = [PBUnknownFieldSet builder];

  PBField* varintField = [[PBMutableField field] addVarint:1];
  PBField* fixed32Field = [[PBMutableField field] addFixed32:1];

  for (NSNumber* key in unknownFields.fields) {
    PBField* field = [unknownFields.fields objectForKey:key];
    if (field.varintArray.count == 0) {
      // Original field is not a varint, so use a varint.
      [bizarroFields addField:varintField forNumber:key.intValue];
    } else {
      // Original field *is* a varint, so use something else.
      [bizarroFields addField:fixed32Field forNumber:key.intValue];
    }
  }

  return [[bizarroFields build] data];
}


- (void) testSerialize {
  // Check that serializing the UnknownFieldSet produces the original data
  // again.
  NSData* data = [emptyMessage data];
  STAssertEqualObjects(allFieldsData, data, @"");
}


- (void) testCopyFrom {
  TestEmptyMessage* message =
  [[[TestEmptyMessage builder] mergeFrom:emptyMessage] build];

  STAssertEqualObjects(emptyMessage.data, message.data, @"");
}


- (void) testMergeFrom {
  PBUnknownFieldSet* set1 =
  [[[[PBUnknownFieldSet builder]
     addField:[[PBMutableField field] addVarint:2] forNumber:2]
    addField:[[PBMutableField field] addVarint:4] forNumber:3] build];

  PBUnknownFieldSet* set2 =
  [[[[PBUnknownFieldSet builder]
     addField:[[PBMutableField field] addVarint:1] forNumber:1]
    addField:[[PBMutableField field] addVarint:3] forNumber:3] build];

  PBUnknownFieldSet* set3 =
  [[[[PBUnknownFieldSet builder]
     addField:[[PBMutableField field] addVarint:1] forNumber:1]
    addField:[[PBMutableField field] addVarint:4] forNumber:3] build];

  PBUnknownFieldSet* set4 =
  [[[[PBUnknownFieldSet builder]
     addField:[[PBMutableField field] addVarint:2] forNumber:2]
    addField:[[PBMutableField field] addVarint:3] forNumber:3] build];

  TestEmptyMessage* source1 = (id)[[[TestEmptyMessage builder] setUnknownFields:set1] build];
  TestEmptyMessage* source2 = (id)[[[TestEmptyMessage builder] setUnknownFields:set2] build];
  TestEmptyMessage* source3 = (id)[[[TestEmptyMessage builder] setUnknownFields:set3] build];
  TestEmptyMessage* source4 = (id)[[[TestEmptyMessage builder] setUnknownFields:set4] build];

  TestEmptyMessage* destination1 = (id)[[[[TestEmptyMessage builder] mergeFrom:source1] mergeFrom:source2] build];
  TestEmptyMessage* destination2 = (id)[[[[TestEmptyMessage builder] mergeFrom:source3] mergeFrom:source4] build];

  STAssertEqualObjects(destination1.data, destination2.data, @"");
}


- (void) testClear {
  PBUnknownFieldSet* fields =
  [[[[PBUnknownFieldSet builder] mergeUnknownFields:unknownFields] clear] build];
  STAssertEquals(fields.fields.count, (NSUInteger) 0, @"");
}


- (void) testClearMessage {
  TestEmptyMessage* message =
  [[[[TestEmptyMessage builder] mergeFrom:emptyMessage] clear] build];
  STAssertTrue(0 == message.serializedSize, @"");
}


- (void) testParseKnownAndUnknown {
  // Test mixing known and unknown fields when parsing.

  PBUnknownFieldSet* fields =
  [[[PBUnknownFieldSet builderWithUnknownFields:unknownFields] addField:[[PBMutableField field] addVarint:654321]
                                                              forNumber:123456] build];

  NSData* data = fields.data;
  TestAllTypes* destination = [TestAllTypes parseFromData:data];

  [TestUtilities assertAllFieldsSet:destination];
  STAssertTrue(1 == destination.unknownFields.fields.count, @"");

  PBField* field = [destination.unknownFields getField:123456];
  STAssertTrue(1 == field.varintArray.count, @"");
  STAssertTrue(654321 == [field.varintArray int64AtIndex:0], @"");
}


- (void) testWrongTypeTreatedAsUnknown {
  // Test that fields of the wrong wire type are treated like unknown fields
  // when parsing.

  NSData* bizarroData = [self getBizarroData];
  TestAllTypes* allTypesMessage = [TestAllTypes parseFromData:bizarroData];
  TestEmptyMessage* emptyMessage_ = [TestEmptyMessage parseFromData:bizarroData];

  // All fields should have been interpreted as unknown, so the debug strings
  // should be the same.
  STAssertEqualObjects(emptyMessage_.data, allTypesMessage.data, @"");
}


- (void) testUnknownExtensions {
  // Make sure fields are properly parsed to the UnknownFieldSet even when
  // they are declared as extension numbers.

  TestEmptyMessageWithExtensions* message =
  [TestEmptyMessageWithExtensions parseFromData:allFieldsData];

  STAssertTrue(unknownFields.fields.count ==  message.unknownFields.fields.count, @"");
  STAssertEqualObjects(allFieldsData, message.data, @"");
}


- (void) testWrongExtensionTypeTreatedAsUnknown {
  // Test that fields of the wrong wire type are treated like unknown fields
  // when parsing extensions.

  NSData* bizarroData = [self getBizarroData];
  TestAllExtensions* allExtensionsMessage = [TestAllExtensions parseFromData:bizarroData];
  TestEmptyMessage* emptyMessage_ = [TestEmptyMessage parseFromData:bizarroData];

  // All fields should have been interpreted as unknown, so the debug strings
  // should be the same.
  STAssertEqualObjects(emptyMessage_.data, allExtensionsMessage.data, @"");
}


- (void) testLargeVarint {
  NSData* data =
  [[[[PBUnknownFieldSet builder] addField:[[PBMutableField field] addVarint:0x7FFFFFFFFFFFFFFFL]
                                forNumber:1] build] data];

  PBUnknownFieldSet* parsed = [PBUnknownFieldSet parseFromData:data];
  PBField* field = [parsed getField:1];
  STAssertTrue(1 == field.varintArray.count, @"");
  STAssertTrue(0x7FFFFFFFFFFFFFFFL == [field.varintArray int64AtIndex:0], @"");
}

@end
