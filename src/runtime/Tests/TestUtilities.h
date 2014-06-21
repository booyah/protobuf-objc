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

#import <XCTest/XCTest.h>

@class TestAllExtensions;
@class TestAllExtensionsBuilder;
@class TestAllTypes;
@class TestAllTypesBuilder;
@class TestPackedTypes;
@class TestPackedTypesBuilder;
@class TestPackedExtensions;
@class TestPackedExtensionsBuilder;
@class PBExtensionRegistry;
@class PBMutableExtensionRegistry;

@interface TestUtilities : XCTestCase {
}

+ (void) setAllFields:(TestAllTypesBuilder*) message;
+ (void) setAllExtensions:(TestAllExtensionsBuilder*) message;
+ (void) setPackedFields:(TestPackedTypesBuilder*) message;
+ (void) setPackedExtensions:(TestPackedExtensionsBuilder*) message;
+ (void) registerAllExtensions:(PBMutableExtensionRegistry*) registry;

+ (TestAllTypes*) allSet;
+ (TestAllExtensions*) allExtensionsSet;
+ (TestPackedTypes*) packedSet;
+ (TestPackedExtensions*) packedExtensionsSet;

+ (void) assertAllFieldsSet:(TestAllTypes*) message;
+ (void) assertAllExtensionsSet:(TestAllExtensions*) message;
+ (void) assertRepeatedExtensionsModified:(TestAllExtensions*) message;
+ (void) assertExtensionsClear:(TestAllExtensions*) message;
+ (void) assertPackedFieldsSet:(TestPackedTypes*) message;
+ (void) assertPackedExtensionsSet:(TestPackedExtensions*) message;

+ (void) modifyRepeatedExtensions:(TestAllExtensionsBuilder*) message;

+ (PBExtensionRegistry*) extensionRegistry;

+ (NSData*) goldenData;

@end
