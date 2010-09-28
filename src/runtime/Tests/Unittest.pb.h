#import "ProtocolBuffers.h"

#import "UnittestImport.pb.h"

@class BarRequest;
@class BarRequest_Builder;
@class BarResponse;
@class BarResponse_Builder;
@class FooRequest;
@class FooRequest_Builder;
@class FooResponse;
@class FooResponse_Builder;
@class ForeignMessage;
@class ForeignMessage_Builder;
@class ImportMessage;
@class ImportMessage_Builder;
@class OneBytes;
@class OneBytes_Builder;
@class OneString;
@class OneString_Builder;
@class OptionalGroup_extension;
@class OptionalGroup_extension_Builder;
@class RepeatedGroup_extension;
@class RepeatedGroup_extension_Builder;
@class TestAllExtensions;
@class TestAllExtensions_Builder;
@class TestAllTypes;
@class TestAllTypes_Builder;
@class TestAllTypes_NestedMessage;
@class TestAllTypes_NestedMessage_Builder;
@class TestAllTypes_OptionalGroup;
@class TestAllTypes_OptionalGroup_Builder;
@class TestAllTypes_RepeatedGroup;
@class TestAllTypes_RepeatedGroup_Builder;
@class TestCamelCaseFieldNames;
@class TestCamelCaseFieldNames_Builder;
@class TestDupFieldNumber;
@class TestDupFieldNumber_Bar;
@class TestDupFieldNumber_Bar_Builder;
@class TestDupFieldNumber_Builder;
@class TestDupFieldNumber_Foo;
@class TestDupFieldNumber_Foo_Builder;
@class TestEmptyMessage;
@class TestEmptyMessageWithExtensions;
@class TestEmptyMessageWithExtensions_Builder;
@class TestEmptyMessage_Builder;
@class TestExtremeDefaultValues;
@class TestExtremeDefaultValues_Builder;
@class TestFieldOrderings;
@class TestFieldOrderings_Builder;
@class TestForeignNested;
@class TestForeignNested_Builder;
@class TestMutualRecursionA;
@class TestMutualRecursionA_Builder;
@class TestMutualRecursionB;
@class TestMutualRecursionB_Builder;
@class TestNestedExtension;
@class TestNestedExtension_Builder;
@class TestNestedMessageHasBits;
@class TestNestedMessageHasBits_Builder;
@class TestNestedMessageHasBits_NestedMessage;
@class TestNestedMessageHasBits_NestedMessage_Builder;
@class TestPackedExtensions;
@class TestPackedExtensions_Builder;
@class TestPackedTypes;
@class TestPackedTypes_Builder;
@class TestReallyLargeTagNumber;
@class TestReallyLargeTagNumber_Builder;
@class TestRecursiveMessage;
@class TestRecursiveMessage_Builder;
@class TestRequired;
@class TestRequiredForeign;
@class TestRequiredForeign_Builder;
@class TestRequired_Builder;
typedef enum {
  ForeignEnumForeignFoo = 4,
  ForeignEnumForeignBar = 5,
  ForeignEnumForeignBaz = 6,
} ForeignEnum;

BOOL ForeignEnumIsValidValue(ForeignEnum value);

typedef enum {
  TestEnumWithDupValueFoo1 = 1,
  TestEnumWithDupValueBar1 = 2,
  TestEnumWithDupValueBaz = 3,
} TestEnumWithDupValue;

BOOL TestEnumWithDupValueIsValidValue(TestEnumWithDupValue value);

typedef enum {
  TestSparseEnumSparseA = 123,
  TestSparseEnumSparseB = 62374,
  TestSparseEnumSparseC = 12589234,
  TestSparseEnumSparseD = -15,
  TestSparseEnumSparseE = -53452,
  TestSparseEnumSparseF = 0,
  TestSparseEnumSparseG = 2,
} TestSparseEnum;

BOOL TestSparseEnumIsValidValue(TestSparseEnum value);

typedef enum {
  TestAllTypes_NestedEnumFoo = 1,
  TestAllTypes_NestedEnumBar = 2,
  TestAllTypes_NestedEnumBaz = 3,
} TestAllTypes_NestedEnum;

BOOL TestAllTypes_NestedEnumIsValidValue(TestAllTypes_NestedEnum value);


@interface UnittestRoot : NSObject {
}
+ (PBExtensionRegistry*) extensionRegistry;
+ (void) registerAllExtensions:(PBMutableExtensionRegistry*) registry;
+ (id<PBExtensionField>) optionalInt32Extension;
+ (id<PBExtensionField>) optionalInt64Extension;
+ (id<PBExtensionField>) optionalUint32Extension;
+ (id<PBExtensionField>) optionalUint64Extension;
+ (id<PBExtensionField>) optionalSint32Extension;
+ (id<PBExtensionField>) optionalSint64Extension;
+ (id<PBExtensionField>) optionalFixed32Extension;
+ (id<PBExtensionField>) optionalFixed64Extension;
+ (id<PBExtensionField>) optionalSfixed32Extension;
+ (id<PBExtensionField>) optionalSfixed64Extension;
+ (id<PBExtensionField>) optionalFloatExtension;
+ (id<PBExtensionField>) optionalDoubleExtension;
+ (id<PBExtensionField>) optionalBoolExtension;
+ (id<PBExtensionField>) optionalStringExtension;
+ (id<PBExtensionField>) optionalBytesExtension;
+ (id<PBExtensionField>) optionalGroupExtension;
+ (id<PBExtensionField>) optionalNestedMessageExtension;
+ (id<PBExtensionField>) optionalForeignMessageExtension;
+ (id<PBExtensionField>) optionalImportMessageExtension;
+ (id<PBExtensionField>) optionalNestedEnumExtension;
+ (id<PBExtensionField>) optionalForeignEnumExtension;
+ (id<PBExtensionField>) optionalImportEnumExtension;
+ (id<PBExtensionField>) optionalStringPieceExtension;
+ (id<PBExtensionField>) optionalCordExtension;
+ (id<PBExtensionField>) repeatedInt32Extension;
+ (id<PBExtensionField>) repeatedInt64Extension;
+ (id<PBExtensionField>) repeatedUint32Extension;
+ (id<PBExtensionField>) repeatedUint64Extension;
+ (id<PBExtensionField>) repeatedSint32Extension;
+ (id<PBExtensionField>) repeatedSint64Extension;
+ (id<PBExtensionField>) repeatedFixed32Extension;
+ (id<PBExtensionField>) repeatedFixed64Extension;
+ (id<PBExtensionField>) repeatedSfixed32Extension;
+ (id<PBExtensionField>) repeatedSfixed64Extension;
+ (id<PBExtensionField>) repeatedFloatExtension;
+ (id<PBExtensionField>) repeatedDoubleExtension;
+ (id<PBExtensionField>) repeatedBoolExtension;
+ (id<PBExtensionField>) repeatedStringExtension;
+ (id<PBExtensionField>) repeatedBytesExtension;
+ (id<PBExtensionField>) repeatedGroupExtension;
+ (id<PBExtensionField>) repeatedNestedMessageExtension;
+ (id<PBExtensionField>) repeatedForeignMessageExtension;
+ (id<PBExtensionField>) repeatedImportMessageExtension;
+ (id<PBExtensionField>) repeatedNestedEnumExtension;
+ (id<PBExtensionField>) repeatedForeignEnumExtension;
+ (id<PBExtensionField>) repeatedImportEnumExtension;
+ (id<PBExtensionField>) repeatedStringPieceExtension;
+ (id<PBExtensionField>) repeatedCordExtension;
+ (id<PBExtensionField>) defaultInt32Extension;
+ (id<PBExtensionField>) defaultInt64Extension;
+ (id<PBExtensionField>) defaultUint32Extension;
+ (id<PBExtensionField>) defaultUint64Extension;
+ (id<PBExtensionField>) defaultSint32Extension;
+ (id<PBExtensionField>) defaultSint64Extension;
+ (id<PBExtensionField>) defaultFixed32Extension;
+ (id<PBExtensionField>) defaultFixed64Extension;
+ (id<PBExtensionField>) defaultSfixed32Extension;
+ (id<PBExtensionField>) defaultSfixed64Extension;
+ (id<PBExtensionField>) defaultFloatExtension;
+ (id<PBExtensionField>) defaultDoubleExtension;
+ (id<PBExtensionField>) defaultBoolExtension;
+ (id<PBExtensionField>) defaultStringExtension;
+ (id<PBExtensionField>) defaultBytesExtension;
+ (id<PBExtensionField>) defaultNestedEnumExtension;
+ (id<PBExtensionField>) defaultForeignEnumExtension;
+ (id<PBExtensionField>) defaultImportEnumExtension;
+ (id<PBExtensionField>) defaultStringPieceExtension;
+ (id<PBExtensionField>) defaultCordExtension;
+ (id<PBExtensionField>) myExtensionString;
+ (id<PBExtensionField>) myExtensionInt;
+ (id<PBExtensionField>) packedInt32Extension;
+ (id<PBExtensionField>) packedInt64Extension;
+ (id<PBExtensionField>) packedUint32Extension;
+ (id<PBExtensionField>) packedUint64Extension;
+ (id<PBExtensionField>) packedSint32Extension;
+ (id<PBExtensionField>) packedSint64Extension;
+ (id<PBExtensionField>) packedFixed32Extension;
+ (id<PBExtensionField>) packedFixed64Extension;
+ (id<PBExtensionField>) packedSfixed32Extension;
+ (id<PBExtensionField>) packedSfixed64Extension;
+ (id<PBExtensionField>) packedFloatExtension;
+ (id<PBExtensionField>) packedDoubleExtension;
+ (id<PBExtensionField>) packedBoolExtension;
+ (id<PBExtensionField>) packedEnumExtension;
@end

@interface TestAllTypes : PBGeneratedMessage {
@private
  BOOL hasOptionalBool_:1;
  BOOL hasDefaultBool_:1;
  BOOL hasOptionalDouble_:1;
  BOOL hasDefaultDouble_:1;
  BOOL hasOptionalFloat_:1;
  BOOL hasDefaultFloat_:1;
  BOOL hasOptionalInt64_:1;
  BOOL hasDefaultInt64_:1;
  BOOL hasOptionalUint64_:1;
  BOOL hasDefaultUint64_:1;
  BOOL hasOptionalInt32_:1;
  BOOL hasDefaultInt32_:1;
  BOOL hasOptionalFixed64_:1;
  BOOL hasDefaultFixed64_:1;
  BOOL hasOptionalFixed32_:1;
  BOOL hasDefaultFixed32_:1;
  BOOL hasOptionalCord_:1;
  BOOL hasDefaultCord_:1;
  BOOL hasDefaultStringPiece_:1;
  BOOL hasDefaultString_:1;
  BOOL hasOptionalString_:1;
  BOOL hasOptionalStringPiece_:1;
  BOOL hasOptionalGroup_:1;
  BOOL hasOptionalForeignMessage_:1;
  BOOL hasOptionalImportMessage_:1;
  BOOL hasOptionalNestedMessage_:1;
  BOOL hasDefaultBytes_:1;
  BOOL hasOptionalBytes_:1;
  BOOL hasOptionalUint32_:1;
  BOOL hasDefaultUint32_:1;
  BOOL hasOptionalNestedEnum_:1;
  BOOL hasOptionalForeignEnum_:1;
  BOOL hasOptionalImportEnum_:1;
  BOOL hasDefaultImportEnum_:1;
  BOOL hasDefaultForeignEnum_:1;
  BOOL hasDefaultNestedEnum_:1;
  BOOL hasDefaultSfixed32_:1;
  BOOL hasOptionalSfixed32_:1;
  BOOL hasOptionalSfixed64_:1;
  BOOL hasDefaultSfixed64_:1;
  BOOL hasOptionalSint32_:1;
  BOOL hasDefaultSint32_:1;
  BOOL hasOptionalSint64_:1;
  BOOL hasDefaultSint64_:1;
  BOOL optionalBool_:1;
  BOOL defaultBool_:1;
  Float64 optionalDouble;
  Float64 defaultDouble;
  Float32 optionalFloat;
  Float32 defaultFloat;
  int64_t optionalInt64;
  int64_t defaultInt64;
  int64_t optionalUint64;
  int64_t defaultUint64;
  int32_t optionalInt32;
  int32_t defaultInt32;
  int64_t optionalFixed64;
  int64_t defaultFixed64;
  int32_t optionalFixed32;
  int32_t defaultFixed32;
  NSString* optionalCord;
  NSString* defaultCord;
  NSString* defaultStringPiece;
  NSString* defaultString;
  NSString* optionalString;
  NSString* optionalStringPiece;
  TestAllTypes_OptionalGroup* optionalGroup;
  ForeignMessage* optionalForeignMessage;
  ImportMessage* optionalImportMessage;
  TestAllTypes_NestedMessage* optionalNestedMessage;
  NSData* defaultBytes;
  NSData* optionalBytes;
  int32_t optionalUint32;
  int32_t defaultUint32;
  TestAllTypes_NestedEnum optionalNestedEnum;
  ForeignEnum optionalForeignEnum;
  ImportEnum optionalImportEnum;
  ImportEnum defaultImportEnum;
  ForeignEnum defaultForeignEnum;
  TestAllTypes_NestedEnum defaultNestedEnum;
  int32_t defaultSfixed32;
  int32_t optionalSfixed32;
  int64_t optionalSfixed64;
  int64_t defaultSfixed64;
  int32_t optionalSint32;
  int32_t defaultSint32;
  int64_t optionalSint64;
  int64_t defaultSint64;
  NSMutableArray* mutableRepeatedBoolList;
  NSMutableArray* mutableRepeatedDoubleList;
  NSMutableArray* mutableRepeatedFloatList;
  NSMutableArray* mutableRepeatedInt64List;
  NSMutableArray* mutableRepeatedUint64List;
  NSMutableArray* mutableRepeatedInt32List;
  NSMutableArray* mutableRepeatedFixed64List;
  NSMutableArray* mutableRepeatedFixed32List;
  NSMutableArray* mutableRepeatedStringList;
  NSMutableArray* mutableRepeatedStringPieceList;
  NSMutableArray* mutableRepeatedCordList;
  NSMutableArray* mutableRepeatedGroupList;
  NSMutableArray* mutableRepeatedNestedMessageList;
  NSMutableArray* mutableRepeatedImportMessageList;
  NSMutableArray* mutableRepeatedForeignMessageList;
  NSMutableArray* mutableRepeatedBytesList;
  NSMutableArray* mutableRepeatedUint32List;
  NSMutableArray* mutableRepeatedImportEnumList;
  NSMutableArray* mutableRepeatedForeignEnumList;
  NSMutableArray* mutableRepeatedNestedEnumList;
  NSMutableArray* mutableRepeatedSfixed32List;
  NSMutableArray* mutableRepeatedSfixed64List;
  NSMutableArray* mutableRepeatedSint32List;
  NSMutableArray* mutableRepeatedSint64List;
}
- (BOOL) hasOptionalInt32;
- (BOOL) hasOptionalInt64;
- (BOOL) hasOptionalUint32;
- (BOOL) hasOptionalUint64;
- (BOOL) hasOptionalSint32;
- (BOOL) hasOptionalSint64;
- (BOOL) hasOptionalFixed32;
- (BOOL) hasOptionalFixed64;
- (BOOL) hasOptionalSfixed32;
- (BOOL) hasOptionalSfixed64;
- (BOOL) hasOptionalFloat;
- (BOOL) hasOptionalDouble;
- (BOOL) hasOptionalBool;
- (BOOL) hasOptionalString;
- (BOOL) hasOptionalBytes;
- (BOOL) hasOptionalGroup;
- (BOOL) hasOptionalNestedMessage;
- (BOOL) hasOptionalForeignMessage;
- (BOOL) hasOptionalImportMessage;
- (BOOL) hasOptionalNestedEnum;
- (BOOL) hasOptionalForeignEnum;
- (BOOL) hasOptionalImportEnum;
- (BOOL) hasOptionalStringPiece;
- (BOOL) hasOptionalCord;
- (BOOL) hasDefaultInt32;
- (BOOL) hasDefaultInt64;
- (BOOL) hasDefaultUint32;
- (BOOL) hasDefaultUint64;
- (BOOL) hasDefaultSint32;
- (BOOL) hasDefaultSint64;
- (BOOL) hasDefaultFixed32;
- (BOOL) hasDefaultFixed64;
- (BOOL) hasDefaultSfixed32;
- (BOOL) hasDefaultSfixed64;
- (BOOL) hasDefaultFloat;
- (BOOL) hasDefaultDouble;
- (BOOL) hasDefaultBool;
- (BOOL) hasDefaultString;
- (BOOL) hasDefaultBytes;
- (BOOL) hasDefaultNestedEnum;
- (BOOL) hasDefaultForeignEnum;
- (BOOL) hasDefaultImportEnum;
- (BOOL) hasDefaultStringPiece;
- (BOOL) hasDefaultCord;
@property (readonly) int32_t optionalInt32;
@property (readonly) int64_t optionalInt64;
@property (readonly) int32_t optionalUint32;
@property (readonly) int64_t optionalUint64;
@property (readonly) int32_t optionalSint32;
@property (readonly) int64_t optionalSint64;
@property (readonly) int32_t optionalFixed32;
@property (readonly) int64_t optionalFixed64;
@property (readonly) int32_t optionalSfixed32;
@property (readonly) int64_t optionalSfixed64;
@property (readonly) Float32 optionalFloat;
@property (readonly) Float64 optionalDouble;
- (BOOL) optionalBool;
@property (readonly, retain) NSString* optionalString;
@property (readonly, retain) NSData* optionalBytes;
@property (readonly, retain) TestAllTypes_OptionalGroup* optionalGroup;
@property (readonly, retain) TestAllTypes_NestedMessage* optionalNestedMessage;
@property (readonly, retain) ForeignMessage* optionalForeignMessage;
@property (readonly, retain) ImportMessage* optionalImportMessage;
@property (readonly) TestAllTypes_NestedEnum optionalNestedEnum;
@property (readonly) ForeignEnum optionalForeignEnum;
@property (readonly) ImportEnum optionalImportEnum;
@property (readonly, retain) NSString* optionalStringPiece;
@property (readonly, retain) NSString* optionalCord;
@property (readonly) int32_t defaultInt32;
@property (readonly) int64_t defaultInt64;
@property (readonly) int32_t defaultUint32;
@property (readonly) int64_t defaultUint64;
@property (readonly) int32_t defaultSint32;
@property (readonly) int64_t defaultSint64;
@property (readonly) int32_t defaultFixed32;
@property (readonly) int64_t defaultFixed64;
@property (readonly) int32_t defaultSfixed32;
@property (readonly) int64_t defaultSfixed64;
@property (readonly) Float32 defaultFloat;
@property (readonly) Float64 defaultDouble;
- (BOOL) defaultBool;
@property (readonly, retain) NSString* defaultString;
@property (readonly, retain) NSData* defaultBytes;
@property (readonly) TestAllTypes_NestedEnum defaultNestedEnum;
@property (readonly) ForeignEnum defaultForeignEnum;
@property (readonly) ImportEnum defaultImportEnum;
@property (readonly, retain) NSString* defaultStringPiece;
@property (readonly, retain) NSString* defaultCord;
- (NSArray*) repeatedInt32List;
- (int32_t) repeatedInt32AtIndex:(int32_t) index;
- (NSArray*) repeatedInt64List;
- (int64_t) repeatedInt64AtIndex:(int32_t) index;
- (NSArray*) repeatedUint32List;
- (int32_t) repeatedUint32AtIndex:(int32_t) index;
- (NSArray*) repeatedUint64List;
- (int64_t) repeatedUint64AtIndex:(int32_t) index;
- (NSArray*) repeatedSint32List;
- (int32_t) repeatedSint32AtIndex:(int32_t) index;
- (NSArray*) repeatedSint64List;
- (int64_t) repeatedSint64AtIndex:(int32_t) index;
- (NSArray*) repeatedFixed32List;
- (int32_t) repeatedFixed32AtIndex:(int32_t) index;
- (NSArray*) repeatedFixed64List;
- (int64_t) repeatedFixed64AtIndex:(int32_t) index;
- (NSArray*) repeatedSfixed32List;
- (int32_t) repeatedSfixed32AtIndex:(int32_t) index;
- (NSArray*) repeatedSfixed64List;
- (int64_t) repeatedSfixed64AtIndex:(int32_t) index;
- (NSArray*) repeatedFloatList;
- (Float32) repeatedFloatAtIndex:(int32_t) index;
- (NSArray*) repeatedDoubleList;
- (Float64) repeatedDoubleAtIndex:(int32_t) index;
- (NSArray*) repeatedBoolList;
- (BOOL) repeatedBoolAtIndex:(int32_t) index;
- (NSArray*) repeatedStringList;
- (NSString*) repeatedStringAtIndex:(int32_t) index;
- (NSArray*) repeatedBytesList;
- (NSData*) repeatedBytesAtIndex:(int32_t) index;
- (NSArray*) repeatedGroupList;
- (TestAllTypes_RepeatedGroup*) repeatedGroupAtIndex:(int32_t) index;
- (NSArray*) repeatedNestedMessageList;
- (TestAllTypes_NestedMessage*) repeatedNestedMessageAtIndex:(int32_t) index;
- (NSArray*) repeatedForeignMessageList;
- (ForeignMessage*) repeatedForeignMessageAtIndex:(int32_t) index;
- (NSArray*) repeatedImportMessageList;
- (ImportMessage*) repeatedImportMessageAtIndex:(int32_t) index;
- (NSArray*) repeatedNestedEnumList;
- (TestAllTypes_NestedEnum) repeatedNestedEnumAtIndex:(int32_t) index;
- (NSArray*) repeatedForeignEnumList;
- (ForeignEnum) repeatedForeignEnumAtIndex:(int32_t) index;
- (NSArray*) repeatedImportEnumList;
- (ImportEnum) repeatedImportEnumAtIndex:(int32_t) index;
- (NSArray*) repeatedStringPieceList;
- (NSString*) repeatedStringPieceAtIndex:(int32_t) index;
- (NSArray*) repeatedCordList;
- (NSString*) repeatedCordAtIndex:(int32_t) index;

+ (TestAllTypes*) defaultInstance;
- (TestAllTypes*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestAllTypes_Builder*) builder;
+ (TestAllTypes_Builder*) builder;
+ (TestAllTypes_Builder*) builderWithPrototype:(TestAllTypes*) prototype;

+ (TestAllTypes*) parseFromData:(NSData*) data;
+ (TestAllTypes*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes*) parseFromInputStream:(NSInputStream*) input;
+ (TestAllTypes*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestAllTypes*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestAllTypes_NestedMessage : PBGeneratedMessage {
@private
  BOOL hasBb_:1;
  int32_t bb;
}
- (BOOL) hasBb;
@property (readonly) int32_t bb;

+ (TestAllTypes_NestedMessage*) defaultInstance;
- (TestAllTypes_NestedMessage*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestAllTypes_NestedMessage_Builder*) builder;
+ (TestAllTypes_NestedMessage_Builder*) builder;
+ (TestAllTypes_NestedMessage_Builder*) builderWithPrototype:(TestAllTypes_NestedMessage*) prototype;

+ (TestAllTypes_NestedMessage*) parseFromData:(NSData*) data;
+ (TestAllTypes_NestedMessage*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes_NestedMessage*) parseFromInputStream:(NSInputStream*) input;
+ (TestAllTypes_NestedMessage*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes_NestedMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestAllTypes_NestedMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestAllTypes_NestedMessage_Builder : PBGeneratedMessage_Builder {
@private
  TestAllTypes_NestedMessage* result;
}

- (TestAllTypes_NestedMessage*) defaultInstance;

- (TestAllTypes_NestedMessage_Builder*) clear;
- (TestAllTypes_NestedMessage_Builder*) clone;

- (TestAllTypes_NestedMessage*) build;
- (TestAllTypes_NestedMessage*) buildPartial;

- (TestAllTypes_NestedMessage_Builder*) mergeFrom:(TestAllTypes_NestedMessage*) other;
- (TestAllTypes_NestedMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestAllTypes_NestedMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasBb;
- (int32_t) bb;
- (TestAllTypes_NestedMessage_Builder*) setBb:(int32_t) value;
- (TestAllTypes_NestedMessage_Builder*) clearBb;
@end

@interface TestAllTypes_OptionalGroup : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  int32_t a;
}
- (BOOL) hasA;
@property (readonly) int32_t a;

+ (TestAllTypes_OptionalGroup*) defaultInstance;
- (TestAllTypes_OptionalGroup*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestAllTypes_OptionalGroup_Builder*) builder;
+ (TestAllTypes_OptionalGroup_Builder*) builder;
+ (TestAllTypes_OptionalGroup_Builder*) builderWithPrototype:(TestAllTypes_OptionalGroup*) prototype;

+ (TestAllTypes_OptionalGroup*) parseFromData:(NSData*) data;
+ (TestAllTypes_OptionalGroup*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes_OptionalGroup*) parseFromInputStream:(NSInputStream*) input;
+ (TestAllTypes_OptionalGroup*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes_OptionalGroup*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestAllTypes_OptionalGroup*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestAllTypes_OptionalGroup_Builder : PBGeneratedMessage_Builder {
@private
  TestAllTypes_OptionalGroup* result;
}

- (TestAllTypes_OptionalGroup*) defaultInstance;

- (TestAllTypes_OptionalGroup_Builder*) clear;
- (TestAllTypes_OptionalGroup_Builder*) clone;

- (TestAllTypes_OptionalGroup*) build;
- (TestAllTypes_OptionalGroup*) buildPartial;

- (TestAllTypes_OptionalGroup_Builder*) mergeFrom:(TestAllTypes_OptionalGroup*) other;
- (TestAllTypes_OptionalGroup_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestAllTypes_OptionalGroup_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (TestAllTypes_OptionalGroup_Builder*) setA:(int32_t) value;
- (TestAllTypes_OptionalGroup_Builder*) clearA;
@end

@interface TestAllTypes_RepeatedGroup : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  int32_t a;
}
- (BOOL) hasA;
@property (readonly) int32_t a;

+ (TestAllTypes_RepeatedGroup*) defaultInstance;
- (TestAllTypes_RepeatedGroup*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestAllTypes_RepeatedGroup_Builder*) builder;
+ (TestAllTypes_RepeatedGroup_Builder*) builder;
+ (TestAllTypes_RepeatedGroup_Builder*) builderWithPrototype:(TestAllTypes_RepeatedGroup*) prototype;

+ (TestAllTypes_RepeatedGroup*) parseFromData:(NSData*) data;
+ (TestAllTypes_RepeatedGroup*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes_RepeatedGroup*) parseFromInputStream:(NSInputStream*) input;
+ (TestAllTypes_RepeatedGroup*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllTypes_RepeatedGroup*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestAllTypes_RepeatedGroup*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestAllTypes_RepeatedGroup_Builder : PBGeneratedMessage_Builder {
@private
  TestAllTypes_RepeatedGroup* result;
}

- (TestAllTypes_RepeatedGroup*) defaultInstance;

- (TestAllTypes_RepeatedGroup_Builder*) clear;
- (TestAllTypes_RepeatedGroup_Builder*) clone;

- (TestAllTypes_RepeatedGroup*) build;
- (TestAllTypes_RepeatedGroup*) buildPartial;

- (TestAllTypes_RepeatedGroup_Builder*) mergeFrom:(TestAllTypes_RepeatedGroup*) other;
- (TestAllTypes_RepeatedGroup_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestAllTypes_RepeatedGroup_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (TestAllTypes_RepeatedGroup_Builder*) setA:(int32_t) value;
- (TestAllTypes_RepeatedGroup_Builder*) clearA;
@end

@interface TestAllTypes_Builder : PBGeneratedMessage_Builder {
@private
  TestAllTypes* result;
}

- (TestAllTypes*) defaultInstance;

- (TestAllTypes_Builder*) clear;
- (TestAllTypes_Builder*) clone;

- (TestAllTypes*) build;
- (TestAllTypes*) buildPartial;

- (TestAllTypes_Builder*) mergeFrom:(TestAllTypes*) other;
- (TestAllTypes_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestAllTypes_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasOptionalInt32;
- (int32_t) optionalInt32;
- (TestAllTypes_Builder*) setOptionalInt32:(int32_t) value;
- (TestAllTypes_Builder*) clearOptionalInt32;

- (BOOL) hasOptionalInt64;
- (int64_t) optionalInt64;
- (TestAllTypes_Builder*) setOptionalInt64:(int64_t) value;
- (TestAllTypes_Builder*) clearOptionalInt64;

- (BOOL) hasOptionalUint32;
- (int32_t) optionalUint32;
- (TestAllTypes_Builder*) setOptionalUint32:(int32_t) value;
- (TestAllTypes_Builder*) clearOptionalUint32;

- (BOOL) hasOptionalUint64;
- (int64_t) optionalUint64;
- (TestAllTypes_Builder*) setOptionalUint64:(int64_t) value;
- (TestAllTypes_Builder*) clearOptionalUint64;

- (BOOL) hasOptionalSint32;
- (int32_t) optionalSint32;
- (TestAllTypes_Builder*) setOptionalSint32:(int32_t) value;
- (TestAllTypes_Builder*) clearOptionalSint32;

- (BOOL) hasOptionalSint64;
- (int64_t) optionalSint64;
- (TestAllTypes_Builder*) setOptionalSint64:(int64_t) value;
- (TestAllTypes_Builder*) clearOptionalSint64;

- (BOOL) hasOptionalFixed32;
- (int32_t) optionalFixed32;
- (TestAllTypes_Builder*) setOptionalFixed32:(int32_t) value;
- (TestAllTypes_Builder*) clearOptionalFixed32;

- (BOOL) hasOptionalFixed64;
- (int64_t) optionalFixed64;
- (TestAllTypes_Builder*) setOptionalFixed64:(int64_t) value;
- (TestAllTypes_Builder*) clearOptionalFixed64;

- (BOOL) hasOptionalSfixed32;
- (int32_t) optionalSfixed32;
- (TestAllTypes_Builder*) setOptionalSfixed32:(int32_t) value;
- (TestAllTypes_Builder*) clearOptionalSfixed32;

- (BOOL) hasOptionalSfixed64;
- (int64_t) optionalSfixed64;
- (TestAllTypes_Builder*) setOptionalSfixed64:(int64_t) value;
- (TestAllTypes_Builder*) clearOptionalSfixed64;

- (BOOL) hasOptionalFloat;
- (Float32) optionalFloat;
- (TestAllTypes_Builder*) setOptionalFloat:(Float32) value;
- (TestAllTypes_Builder*) clearOptionalFloat;

- (BOOL) hasOptionalDouble;
- (Float64) optionalDouble;
- (TestAllTypes_Builder*) setOptionalDouble:(Float64) value;
- (TestAllTypes_Builder*) clearOptionalDouble;

- (BOOL) hasOptionalBool;
- (BOOL) optionalBool;
- (TestAllTypes_Builder*) setOptionalBool:(BOOL) value;
- (TestAllTypes_Builder*) clearOptionalBool;

- (BOOL) hasOptionalString;
- (NSString*) optionalString;
- (TestAllTypes_Builder*) setOptionalString:(NSString*) value;
- (TestAllTypes_Builder*) clearOptionalString;

- (BOOL) hasOptionalBytes;
- (NSData*) optionalBytes;
- (TestAllTypes_Builder*) setOptionalBytes:(NSData*) value;
- (TestAllTypes_Builder*) clearOptionalBytes;

- (BOOL) hasOptionalGroup;
- (TestAllTypes_OptionalGroup*) optionalGroup;
- (TestAllTypes_Builder*) setOptionalGroup:(TestAllTypes_OptionalGroup*) value;
- (TestAllTypes_Builder*) setOptionalGroupBuilder:(TestAllTypes_OptionalGroup_Builder*) builderForValue;
- (TestAllTypes_Builder*) mergeOptionalGroup:(TestAllTypes_OptionalGroup*) value;
- (TestAllTypes_Builder*) clearOptionalGroup;

- (BOOL) hasOptionalNestedMessage;
- (TestAllTypes_NestedMessage*) optionalNestedMessage;
- (TestAllTypes_Builder*) setOptionalNestedMessage:(TestAllTypes_NestedMessage*) value;
- (TestAllTypes_Builder*) setOptionalNestedMessageBuilder:(TestAllTypes_NestedMessage_Builder*) builderForValue;
- (TestAllTypes_Builder*) mergeOptionalNestedMessage:(TestAllTypes_NestedMessage*) value;
- (TestAllTypes_Builder*) clearOptionalNestedMessage;

- (BOOL) hasOptionalForeignMessage;
- (ForeignMessage*) optionalForeignMessage;
- (TestAllTypes_Builder*) setOptionalForeignMessage:(ForeignMessage*) value;
- (TestAllTypes_Builder*) setOptionalForeignMessageBuilder:(ForeignMessage_Builder*) builderForValue;
- (TestAllTypes_Builder*) mergeOptionalForeignMessage:(ForeignMessage*) value;
- (TestAllTypes_Builder*) clearOptionalForeignMessage;

- (BOOL) hasOptionalImportMessage;
- (ImportMessage*) optionalImportMessage;
- (TestAllTypes_Builder*) setOptionalImportMessage:(ImportMessage*) value;
- (TestAllTypes_Builder*) setOptionalImportMessageBuilder:(ImportMessage_Builder*) builderForValue;
- (TestAllTypes_Builder*) mergeOptionalImportMessage:(ImportMessage*) value;
- (TestAllTypes_Builder*) clearOptionalImportMessage;

- (BOOL) hasOptionalNestedEnum;
- (TestAllTypes_NestedEnum) optionalNestedEnum;
- (TestAllTypes_Builder*) setOptionalNestedEnum:(TestAllTypes_NestedEnum) value;
- (TestAllTypes_Builder*) clearOptionalNestedEnum;

- (BOOL) hasOptionalForeignEnum;
- (ForeignEnum) optionalForeignEnum;
- (TestAllTypes_Builder*) setOptionalForeignEnum:(ForeignEnum) value;
- (TestAllTypes_Builder*) clearOptionalForeignEnum;

- (BOOL) hasOptionalImportEnum;
- (ImportEnum) optionalImportEnum;
- (TestAllTypes_Builder*) setOptionalImportEnum:(ImportEnum) value;
- (TestAllTypes_Builder*) clearOptionalImportEnum;

- (BOOL) hasOptionalStringPiece;
- (NSString*) optionalStringPiece;
- (TestAllTypes_Builder*) setOptionalStringPiece:(NSString*) value;
- (TestAllTypes_Builder*) clearOptionalStringPiece;

- (BOOL) hasOptionalCord;
- (NSString*) optionalCord;
- (TestAllTypes_Builder*) setOptionalCord:(NSString*) value;
- (TestAllTypes_Builder*) clearOptionalCord;

- (NSArray*) repeatedInt32List;
- (int32_t) repeatedInt32AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedInt32AtIndex:(int32_t) index with:(int32_t) value;
- (TestAllTypes_Builder*) addRepeatedInt32:(int32_t) value;
- (TestAllTypes_Builder*) addAllRepeatedInt32:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedInt32List;

- (NSArray*) repeatedInt64List;
- (int64_t) repeatedInt64AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedInt64AtIndex:(int32_t) index with:(int64_t) value;
- (TestAllTypes_Builder*) addRepeatedInt64:(int64_t) value;
- (TestAllTypes_Builder*) addAllRepeatedInt64:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedInt64List;

- (NSArray*) repeatedUint32List;
- (int32_t) repeatedUint32AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedUint32AtIndex:(int32_t) index with:(int32_t) value;
- (TestAllTypes_Builder*) addRepeatedUint32:(int32_t) value;
- (TestAllTypes_Builder*) addAllRepeatedUint32:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedUint32List;

- (NSArray*) repeatedUint64List;
- (int64_t) repeatedUint64AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedUint64AtIndex:(int32_t) index with:(int64_t) value;
- (TestAllTypes_Builder*) addRepeatedUint64:(int64_t) value;
- (TestAllTypes_Builder*) addAllRepeatedUint64:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedUint64List;

- (NSArray*) repeatedSint32List;
- (int32_t) repeatedSint32AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedSint32AtIndex:(int32_t) index with:(int32_t) value;
- (TestAllTypes_Builder*) addRepeatedSint32:(int32_t) value;
- (TestAllTypes_Builder*) addAllRepeatedSint32:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedSint32List;

- (NSArray*) repeatedSint64List;
- (int64_t) repeatedSint64AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedSint64AtIndex:(int32_t) index with:(int64_t) value;
- (TestAllTypes_Builder*) addRepeatedSint64:(int64_t) value;
- (TestAllTypes_Builder*) addAllRepeatedSint64:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedSint64List;

- (NSArray*) repeatedFixed32List;
- (int32_t) repeatedFixed32AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedFixed32AtIndex:(int32_t) index with:(int32_t) value;
- (TestAllTypes_Builder*) addRepeatedFixed32:(int32_t) value;
- (TestAllTypes_Builder*) addAllRepeatedFixed32:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedFixed32List;

- (NSArray*) repeatedFixed64List;
- (int64_t) repeatedFixed64AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedFixed64AtIndex:(int32_t) index with:(int64_t) value;
- (TestAllTypes_Builder*) addRepeatedFixed64:(int64_t) value;
- (TestAllTypes_Builder*) addAllRepeatedFixed64:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedFixed64List;

- (NSArray*) repeatedSfixed32List;
- (int32_t) repeatedSfixed32AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedSfixed32AtIndex:(int32_t) index with:(int32_t) value;
- (TestAllTypes_Builder*) addRepeatedSfixed32:(int32_t) value;
- (TestAllTypes_Builder*) addAllRepeatedSfixed32:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedSfixed32List;

- (NSArray*) repeatedSfixed64List;
- (int64_t) repeatedSfixed64AtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedSfixed64AtIndex:(int32_t) index with:(int64_t) value;
- (TestAllTypes_Builder*) addRepeatedSfixed64:(int64_t) value;
- (TestAllTypes_Builder*) addAllRepeatedSfixed64:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedSfixed64List;

- (NSArray*) repeatedFloatList;
- (Float32) repeatedFloatAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedFloatAtIndex:(int32_t) index with:(Float32) value;
- (TestAllTypes_Builder*) addRepeatedFloat:(Float32) value;
- (TestAllTypes_Builder*) addAllRepeatedFloat:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedFloatList;

- (NSArray*) repeatedDoubleList;
- (Float64) repeatedDoubleAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedDoubleAtIndex:(int32_t) index with:(Float64) value;
- (TestAllTypes_Builder*) addRepeatedDouble:(Float64) value;
- (TestAllTypes_Builder*) addAllRepeatedDouble:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedDoubleList;

- (NSArray*) repeatedBoolList;
- (BOOL) repeatedBoolAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedBoolAtIndex:(int32_t) index with:(BOOL) value;
- (TestAllTypes_Builder*) addRepeatedBool:(BOOL) value;
- (TestAllTypes_Builder*) addAllRepeatedBool:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedBoolList;

- (NSArray*) repeatedStringList;
- (NSString*) repeatedStringAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedStringAtIndex:(int32_t) index with:(NSString*) value;
- (TestAllTypes_Builder*) addRepeatedString:(NSString*) value;
- (TestAllTypes_Builder*) addAllRepeatedString:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedStringList;

- (NSArray*) repeatedBytesList;
- (NSData*) repeatedBytesAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedBytesAtIndex:(int32_t) index with:(NSData*) value;
- (TestAllTypes_Builder*) addRepeatedBytes:(NSData*) value;
- (TestAllTypes_Builder*) addAllRepeatedBytes:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedBytesList;

- (NSArray*) repeatedGroupList;
- (TestAllTypes_RepeatedGroup*) repeatedGroupAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedGroupAtIndex:(int32_t) index with:(TestAllTypes_RepeatedGroup*) value;
- (TestAllTypes_Builder*) addRepeatedGroup:(TestAllTypes_RepeatedGroup*) value;
- (TestAllTypes_Builder*) addAllRepeatedGroup:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedGroupList;

- (NSArray*) repeatedNestedMessageList;
- (TestAllTypes_NestedMessage*) repeatedNestedMessageAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedNestedMessageAtIndex:(int32_t) index with:(TestAllTypes_NestedMessage*) value;
- (TestAllTypes_Builder*) addRepeatedNestedMessage:(TestAllTypes_NestedMessage*) value;
- (TestAllTypes_Builder*) addAllRepeatedNestedMessage:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedNestedMessageList;

- (NSArray*) repeatedForeignMessageList;
- (ForeignMessage*) repeatedForeignMessageAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedForeignMessageAtIndex:(int32_t) index with:(ForeignMessage*) value;
- (TestAllTypes_Builder*) addRepeatedForeignMessage:(ForeignMessage*) value;
- (TestAllTypes_Builder*) addAllRepeatedForeignMessage:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedForeignMessageList;

- (NSArray*) repeatedImportMessageList;
- (ImportMessage*) repeatedImportMessageAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedImportMessageAtIndex:(int32_t) index with:(ImportMessage*) value;
- (TestAllTypes_Builder*) addRepeatedImportMessage:(ImportMessage*) value;
- (TestAllTypes_Builder*) addAllRepeatedImportMessage:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedImportMessageList;

- (NSArray*) repeatedNestedEnumList;
- (TestAllTypes_NestedEnum) repeatedNestedEnumAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedNestedEnumAtIndex:(int32_t) index with:(TestAllTypes_NestedEnum) value;
- (TestAllTypes_Builder*) addRepeatedNestedEnum:(TestAllTypes_NestedEnum) value;
- (TestAllTypes_Builder*) addAllRepeatedNestedEnum:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedNestedEnumList;

- (NSArray*) repeatedForeignEnumList;
- (ForeignEnum) repeatedForeignEnumAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedForeignEnumAtIndex:(int32_t) index with:(ForeignEnum) value;
- (TestAllTypes_Builder*) addRepeatedForeignEnum:(ForeignEnum) value;
- (TestAllTypes_Builder*) addAllRepeatedForeignEnum:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedForeignEnumList;

- (NSArray*) repeatedImportEnumList;
- (ImportEnum) repeatedImportEnumAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedImportEnumAtIndex:(int32_t) index with:(ImportEnum) value;
- (TestAllTypes_Builder*) addRepeatedImportEnum:(ImportEnum) value;
- (TestAllTypes_Builder*) addAllRepeatedImportEnum:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedImportEnumList;

- (NSArray*) repeatedStringPieceList;
- (NSString*) repeatedStringPieceAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedStringPieceAtIndex:(int32_t) index with:(NSString*) value;
- (TestAllTypes_Builder*) addRepeatedStringPiece:(NSString*) value;
- (TestAllTypes_Builder*) addAllRepeatedStringPiece:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedStringPieceList;

- (NSArray*) repeatedCordList;
- (NSString*) repeatedCordAtIndex:(int32_t) index;
- (TestAllTypes_Builder*) replaceRepeatedCordAtIndex:(int32_t) index with:(NSString*) value;
- (TestAllTypes_Builder*) addRepeatedCord:(NSString*) value;
- (TestAllTypes_Builder*) addAllRepeatedCord:(NSArray*) values;
- (TestAllTypes_Builder*) clearRepeatedCordList;

- (BOOL) hasDefaultInt32;
- (int32_t) defaultInt32;
- (TestAllTypes_Builder*) setDefaultInt32:(int32_t) value;
- (TestAllTypes_Builder*) clearDefaultInt32;

- (BOOL) hasDefaultInt64;
- (int64_t) defaultInt64;
- (TestAllTypes_Builder*) setDefaultInt64:(int64_t) value;
- (TestAllTypes_Builder*) clearDefaultInt64;

- (BOOL) hasDefaultUint32;
- (int32_t) defaultUint32;
- (TestAllTypes_Builder*) setDefaultUint32:(int32_t) value;
- (TestAllTypes_Builder*) clearDefaultUint32;

- (BOOL) hasDefaultUint64;
- (int64_t) defaultUint64;
- (TestAllTypes_Builder*) setDefaultUint64:(int64_t) value;
- (TestAllTypes_Builder*) clearDefaultUint64;

- (BOOL) hasDefaultSint32;
- (int32_t) defaultSint32;
- (TestAllTypes_Builder*) setDefaultSint32:(int32_t) value;
- (TestAllTypes_Builder*) clearDefaultSint32;

- (BOOL) hasDefaultSint64;
- (int64_t) defaultSint64;
- (TestAllTypes_Builder*) setDefaultSint64:(int64_t) value;
- (TestAllTypes_Builder*) clearDefaultSint64;

- (BOOL) hasDefaultFixed32;
- (int32_t) defaultFixed32;
- (TestAllTypes_Builder*) setDefaultFixed32:(int32_t) value;
- (TestAllTypes_Builder*) clearDefaultFixed32;

- (BOOL) hasDefaultFixed64;
- (int64_t) defaultFixed64;
- (TestAllTypes_Builder*) setDefaultFixed64:(int64_t) value;
- (TestAllTypes_Builder*) clearDefaultFixed64;

- (BOOL) hasDefaultSfixed32;
- (int32_t) defaultSfixed32;
- (TestAllTypes_Builder*) setDefaultSfixed32:(int32_t) value;
- (TestAllTypes_Builder*) clearDefaultSfixed32;

- (BOOL) hasDefaultSfixed64;
- (int64_t) defaultSfixed64;
- (TestAllTypes_Builder*) setDefaultSfixed64:(int64_t) value;
- (TestAllTypes_Builder*) clearDefaultSfixed64;

- (BOOL) hasDefaultFloat;
- (Float32) defaultFloat;
- (TestAllTypes_Builder*) setDefaultFloat:(Float32) value;
- (TestAllTypes_Builder*) clearDefaultFloat;

- (BOOL) hasDefaultDouble;
- (Float64) defaultDouble;
- (TestAllTypes_Builder*) setDefaultDouble:(Float64) value;
- (TestAllTypes_Builder*) clearDefaultDouble;

- (BOOL) hasDefaultBool;
- (BOOL) defaultBool;
- (TestAllTypes_Builder*) setDefaultBool:(BOOL) value;
- (TestAllTypes_Builder*) clearDefaultBool;

- (BOOL) hasDefaultString;
- (NSString*) defaultString;
- (TestAllTypes_Builder*) setDefaultString:(NSString*) value;
- (TestAllTypes_Builder*) clearDefaultString;

- (BOOL) hasDefaultBytes;
- (NSData*) defaultBytes;
- (TestAllTypes_Builder*) setDefaultBytes:(NSData*) value;
- (TestAllTypes_Builder*) clearDefaultBytes;

- (BOOL) hasDefaultNestedEnum;
- (TestAllTypes_NestedEnum) defaultNestedEnum;
- (TestAllTypes_Builder*) setDefaultNestedEnum:(TestAllTypes_NestedEnum) value;
- (TestAllTypes_Builder*) clearDefaultNestedEnum;

- (BOOL) hasDefaultForeignEnum;
- (ForeignEnum) defaultForeignEnum;
- (TestAllTypes_Builder*) setDefaultForeignEnum:(ForeignEnum) value;
- (TestAllTypes_Builder*) clearDefaultForeignEnum;

- (BOOL) hasDefaultImportEnum;
- (ImportEnum) defaultImportEnum;
- (TestAllTypes_Builder*) setDefaultImportEnum:(ImportEnum) value;
- (TestAllTypes_Builder*) clearDefaultImportEnum;

- (BOOL) hasDefaultStringPiece;
- (NSString*) defaultStringPiece;
- (TestAllTypes_Builder*) setDefaultStringPiece:(NSString*) value;
- (TestAllTypes_Builder*) clearDefaultStringPiece;

- (BOOL) hasDefaultCord;
- (NSString*) defaultCord;
- (TestAllTypes_Builder*) setDefaultCord:(NSString*) value;
- (TestAllTypes_Builder*) clearDefaultCord;
@end

@interface ForeignMessage : PBGeneratedMessage {
@private
  BOOL hasC_:1;
  int32_t c;
}
- (BOOL) hasC;
@property (readonly) int32_t c;

+ (ForeignMessage*) defaultInstance;
- (ForeignMessage*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (ForeignMessage_Builder*) builder;
+ (ForeignMessage_Builder*) builder;
+ (ForeignMessage_Builder*) builderWithPrototype:(ForeignMessage*) prototype;

+ (ForeignMessage*) parseFromData:(NSData*) data;
+ (ForeignMessage*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (ForeignMessage*) parseFromInputStream:(NSInputStream*) input;
+ (ForeignMessage*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (ForeignMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (ForeignMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface ForeignMessage_Builder : PBGeneratedMessage_Builder {
@private
  ForeignMessage* result;
}

- (ForeignMessage*) defaultInstance;

- (ForeignMessage_Builder*) clear;
- (ForeignMessage_Builder*) clone;

- (ForeignMessage*) build;
- (ForeignMessage*) buildPartial;

- (ForeignMessage_Builder*) mergeFrom:(ForeignMessage*) other;
- (ForeignMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (ForeignMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasC;
- (int32_t) c;
- (ForeignMessage_Builder*) setC:(int32_t) value;
- (ForeignMessage_Builder*) clearC;
@end

@interface TestAllExtensions : PBExtendableMessage {
@private
}

+ (TestAllExtensions*) defaultInstance;
- (TestAllExtensions*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestAllExtensions_Builder*) builder;
+ (TestAllExtensions_Builder*) builder;
+ (TestAllExtensions_Builder*) builderWithPrototype:(TestAllExtensions*) prototype;

+ (TestAllExtensions*) parseFromData:(NSData*) data;
+ (TestAllExtensions*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllExtensions*) parseFromInputStream:(NSInputStream*) input;
+ (TestAllExtensions*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestAllExtensions*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestAllExtensions*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestAllExtensions_Builder : PBExtendableMessage_Builder {
@private
  TestAllExtensions* result;
}

- (TestAllExtensions*) defaultInstance;

- (TestAllExtensions_Builder*) clear;
- (TestAllExtensions_Builder*) clone;

- (TestAllExtensions*) build;
- (TestAllExtensions*) buildPartial;

- (TestAllExtensions_Builder*) mergeFrom:(TestAllExtensions*) other;
- (TestAllExtensions_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestAllExtensions_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface OptionalGroup_extension : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  int32_t a;
}
- (BOOL) hasA;
@property (readonly) int32_t a;

+ (OptionalGroup_extension*) defaultInstance;
- (OptionalGroup_extension*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (OptionalGroup_extension_Builder*) builder;
+ (OptionalGroup_extension_Builder*) builder;
+ (OptionalGroup_extension_Builder*) builderWithPrototype:(OptionalGroup_extension*) prototype;

+ (OptionalGroup_extension*) parseFromData:(NSData*) data;
+ (OptionalGroup_extension*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OptionalGroup_extension*) parseFromInputStream:(NSInputStream*) input;
+ (OptionalGroup_extension*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OptionalGroup_extension*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (OptionalGroup_extension*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface OptionalGroup_extension_Builder : PBGeneratedMessage_Builder {
@private
  OptionalGroup_extension* result;
}

- (OptionalGroup_extension*) defaultInstance;

- (OptionalGroup_extension_Builder*) clear;
- (OptionalGroup_extension_Builder*) clone;

- (OptionalGroup_extension*) build;
- (OptionalGroup_extension*) buildPartial;

- (OptionalGroup_extension_Builder*) mergeFrom:(OptionalGroup_extension*) other;
- (OptionalGroup_extension_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (OptionalGroup_extension_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (OptionalGroup_extension_Builder*) setA:(int32_t) value;
- (OptionalGroup_extension_Builder*) clearA;
@end

@interface RepeatedGroup_extension : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  int32_t a;
}
- (BOOL) hasA;
@property (readonly) int32_t a;

+ (RepeatedGroup_extension*) defaultInstance;
- (RepeatedGroup_extension*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (RepeatedGroup_extension_Builder*) builder;
+ (RepeatedGroup_extension_Builder*) builder;
+ (RepeatedGroup_extension_Builder*) builderWithPrototype:(RepeatedGroup_extension*) prototype;

+ (RepeatedGroup_extension*) parseFromData:(NSData*) data;
+ (RepeatedGroup_extension*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (RepeatedGroup_extension*) parseFromInputStream:(NSInputStream*) input;
+ (RepeatedGroup_extension*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (RepeatedGroup_extension*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (RepeatedGroup_extension*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface RepeatedGroup_extension_Builder : PBGeneratedMessage_Builder {
@private
  RepeatedGroup_extension* result;
}

- (RepeatedGroup_extension*) defaultInstance;

- (RepeatedGroup_extension_Builder*) clear;
- (RepeatedGroup_extension_Builder*) clone;

- (RepeatedGroup_extension*) build;
- (RepeatedGroup_extension*) buildPartial;

- (RepeatedGroup_extension_Builder*) mergeFrom:(RepeatedGroup_extension*) other;
- (RepeatedGroup_extension_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (RepeatedGroup_extension_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (RepeatedGroup_extension_Builder*) setA:(int32_t) value;
- (RepeatedGroup_extension_Builder*) clearA;
@end

@interface TestNestedExtension : PBGeneratedMessage {
@private
}

+ (TestNestedExtension*) defaultInstance;
- (TestNestedExtension*) defaultInstance;

+ (id<PBExtensionField>) test;
- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestNestedExtension_Builder*) builder;
+ (TestNestedExtension_Builder*) builder;
+ (TestNestedExtension_Builder*) builderWithPrototype:(TestNestedExtension*) prototype;

+ (TestNestedExtension*) parseFromData:(NSData*) data;
+ (TestNestedExtension*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestNestedExtension*) parseFromInputStream:(NSInputStream*) input;
+ (TestNestedExtension*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestNestedExtension*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestNestedExtension*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestNestedExtension_Builder : PBGeneratedMessage_Builder {
@private
  TestNestedExtension* result;
}

- (TestNestedExtension*) defaultInstance;

- (TestNestedExtension_Builder*) clear;
- (TestNestedExtension_Builder*) clone;

- (TestNestedExtension*) build;
- (TestNestedExtension*) buildPartial;

- (TestNestedExtension_Builder*) mergeFrom:(TestNestedExtension*) other;
- (TestNestedExtension_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestNestedExtension_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestRequired : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  BOOL hasDummy2_:1;
  BOOL hasB_:1;
  BOOL hasDummy4_:1;
  BOOL hasDummy5_:1;
  BOOL hasDummy6_:1;
  BOOL hasDummy7_:1;
  BOOL hasDummy8_:1;
  BOOL hasDummy9_:1;
  BOOL hasDummy10_:1;
  BOOL hasDummy11_:1;
  BOOL hasDummy12_:1;
  BOOL hasDummy13_:1;
  BOOL hasDummy14_:1;
  BOOL hasDummy15_:1;
  BOOL hasDummy16_:1;
  BOOL hasDummy17_:1;
  BOOL hasDummy18_:1;
  BOOL hasDummy19_:1;
  BOOL hasDummy20_:1;
  BOOL hasDummy21_:1;
  BOOL hasDummy22_:1;
  BOOL hasDummy23_:1;
  BOOL hasDummy24_:1;
  BOOL hasDummy25_:1;
  BOOL hasDummy26_:1;
  BOOL hasDummy27_:1;
  BOOL hasDummy28_:1;
  BOOL hasDummy29_:1;
  BOOL hasDummy30_:1;
  BOOL hasDummy31_:1;
  BOOL hasDummy32_:1;
  BOOL hasC_:1;
  int32_t a;
  int32_t dummy2;
  int32_t b;
  int32_t dummy4;
  int32_t dummy5;
  int32_t dummy6;
  int32_t dummy7;
  int32_t dummy8;
  int32_t dummy9;
  int32_t dummy10;
  int32_t dummy11;
  int32_t dummy12;
  int32_t dummy13;
  int32_t dummy14;
  int32_t dummy15;
  int32_t dummy16;
  int32_t dummy17;
  int32_t dummy18;
  int32_t dummy19;
  int32_t dummy20;
  int32_t dummy21;
  int32_t dummy22;
  int32_t dummy23;
  int32_t dummy24;
  int32_t dummy25;
  int32_t dummy26;
  int32_t dummy27;
  int32_t dummy28;
  int32_t dummy29;
  int32_t dummy30;
  int32_t dummy31;
  int32_t dummy32;
  int32_t c;
}
- (BOOL) hasA;
- (BOOL) hasDummy2;
- (BOOL) hasB;
- (BOOL) hasDummy4;
- (BOOL) hasDummy5;
- (BOOL) hasDummy6;
- (BOOL) hasDummy7;
- (BOOL) hasDummy8;
- (BOOL) hasDummy9;
- (BOOL) hasDummy10;
- (BOOL) hasDummy11;
- (BOOL) hasDummy12;
- (BOOL) hasDummy13;
- (BOOL) hasDummy14;
- (BOOL) hasDummy15;
- (BOOL) hasDummy16;
- (BOOL) hasDummy17;
- (BOOL) hasDummy18;
- (BOOL) hasDummy19;
- (BOOL) hasDummy20;
- (BOOL) hasDummy21;
- (BOOL) hasDummy22;
- (BOOL) hasDummy23;
- (BOOL) hasDummy24;
- (BOOL) hasDummy25;
- (BOOL) hasDummy26;
- (BOOL) hasDummy27;
- (BOOL) hasDummy28;
- (BOOL) hasDummy29;
- (BOOL) hasDummy30;
- (BOOL) hasDummy31;
- (BOOL) hasDummy32;
- (BOOL) hasC;
@property (readonly) int32_t a;
@property (readonly) int32_t dummy2;
@property (readonly) int32_t b;
@property (readonly) int32_t dummy4;
@property (readonly) int32_t dummy5;
@property (readonly) int32_t dummy6;
@property (readonly) int32_t dummy7;
@property (readonly) int32_t dummy8;
@property (readonly) int32_t dummy9;
@property (readonly) int32_t dummy10;
@property (readonly) int32_t dummy11;
@property (readonly) int32_t dummy12;
@property (readonly) int32_t dummy13;
@property (readonly) int32_t dummy14;
@property (readonly) int32_t dummy15;
@property (readonly) int32_t dummy16;
@property (readonly) int32_t dummy17;
@property (readonly) int32_t dummy18;
@property (readonly) int32_t dummy19;
@property (readonly) int32_t dummy20;
@property (readonly) int32_t dummy21;
@property (readonly) int32_t dummy22;
@property (readonly) int32_t dummy23;
@property (readonly) int32_t dummy24;
@property (readonly) int32_t dummy25;
@property (readonly) int32_t dummy26;
@property (readonly) int32_t dummy27;
@property (readonly) int32_t dummy28;
@property (readonly) int32_t dummy29;
@property (readonly) int32_t dummy30;
@property (readonly) int32_t dummy31;
@property (readonly) int32_t dummy32;
@property (readonly) int32_t c;

+ (TestRequired*) defaultInstance;
- (TestRequired*) defaultInstance;

+ (id<PBExtensionField>) single;
+ (id<PBExtensionField>) multi;
- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestRequired_Builder*) builder;
+ (TestRequired_Builder*) builder;
+ (TestRequired_Builder*) builderWithPrototype:(TestRequired*) prototype;

+ (TestRequired*) parseFromData:(NSData*) data;
+ (TestRequired*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestRequired*) parseFromInputStream:(NSInputStream*) input;
+ (TestRequired*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestRequired*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestRequired*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestRequired_Builder : PBGeneratedMessage_Builder {
@private
  TestRequired* result;
}

- (TestRequired*) defaultInstance;

- (TestRequired_Builder*) clear;
- (TestRequired_Builder*) clone;

- (TestRequired*) build;
- (TestRequired*) buildPartial;

- (TestRequired_Builder*) mergeFrom:(TestRequired*) other;
- (TestRequired_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestRequired_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (TestRequired_Builder*) setA:(int32_t) value;
- (TestRequired_Builder*) clearA;

- (BOOL) hasDummy2;
- (int32_t) dummy2;
- (TestRequired_Builder*) setDummy2:(int32_t) value;
- (TestRequired_Builder*) clearDummy2;

- (BOOL) hasB;
- (int32_t) b;
- (TestRequired_Builder*) setB:(int32_t) value;
- (TestRequired_Builder*) clearB;

- (BOOL) hasDummy4;
- (int32_t) dummy4;
- (TestRequired_Builder*) setDummy4:(int32_t) value;
- (TestRequired_Builder*) clearDummy4;

- (BOOL) hasDummy5;
- (int32_t) dummy5;
- (TestRequired_Builder*) setDummy5:(int32_t) value;
- (TestRequired_Builder*) clearDummy5;

- (BOOL) hasDummy6;
- (int32_t) dummy6;
- (TestRequired_Builder*) setDummy6:(int32_t) value;
- (TestRequired_Builder*) clearDummy6;

- (BOOL) hasDummy7;
- (int32_t) dummy7;
- (TestRequired_Builder*) setDummy7:(int32_t) value;
- (TestRequired_Builder*) clearDummy7;

- (BOOL) hasDummy8;
- (int32_t) dummy8;
- (TestRequired_Builder*) setDummy8:(int32_t) value;
- (TestRequired_Builder*) clearDummy8;

- (BOOL) hasDummy9;
- (int32_t) dummy9;
- (TestRequired_Builder*) setDummy9:(int32_t) value;
- (TestRequired_Builder*) clearDummy9;

- (BOOL) hasDummy10;
- (int32_t) dummy10;
- (TestRequired_Builder*) setDummy10:(int32_t) value;
- (TestRequired_Builder*) clearDummy10;

- (BOOL) hasDummy11;
- (int32_t) dummy11;
- (TestRequired_Builder*) setDummy11:(int32_t) value;
- (TestRequired_Builder*) clearDummy11;

- (BOOL) hasDummy12;
- (int32_t) dummy12;
- (TestRequired_Builder*) setDummy12:(int32_t) value;
- (TestRequired_Builder*) clearDummy12;

- (BOOL) hasDummy13;
- (int32_t) dummy13;
- (TestRequired_Builder*) setDummy13:(int32_t) value;
- (TestRequired_Builder*) clearDummy13;

- (BOOL) hasDummy14;
- (int32_t) dummy14;
- (TestRequired_Builder*) setDummy14:(int32_t) value;
- (TestRequired_Builder*) clearDummy14;

- (BOOL) hasDummy15;
- (int32_t) dummy15;
- (TestRequired_Builder*) setDummy15:(int32_t) value;
- (TestRequired_Builder*) clearDummy15;

- (BOOL) hasDummy16;
- (int32_t) dummy16;
- (TestRequired_Builder*) setDummy16:(int32_t) value;
- (TestRequired_Builder*) clearDummy16;

- (BOOL) hasDummy17;
- (int32_t) dummy17;
- (TestRequired_Builder*) setDummy17:(int32_t) value;
- (TestRequired_Builder*) clearDummy17;

- (BOOL) hasDummy18;
- (int32_t) dummy18;
- (TestRequired_Builder*) setDummy18:(int32_t) value;
- (TestRequired_Builder*) clearDummy18;

- (BOOL) hasDummy19;
- (int32_t) dummy19;
- (TestRequired_Builder*) setDummy19:(int32_t) value;
- (TestRequired_Builder*) clearDummy19;

- (BOOL) hasDummy20;
- (int32_t) dummy20;
- (TestRequired_Builder*) setDummy20:(int32_t) value;
- (TestRequired_Builder*) clearDummy20;

- (BOOL) hasDummy21;
- (int32_t) dummy21;
- (TestRequired_Builder*) setDummy21:(int32_t) value;
- (TestRequired_Builder*) clearDummy21;

- (BOOL) hasDummy22;
- (int32_t) dummy22;
- (TestRequired_Builder*) setDummy22:(int32_t) value;
- (TestRequired_Builder*) clearDummy22;

- (BOOL) hasDummy23;
- (int32_t) dummy23;
- (TestRequired_Builder*) setDummy23:(int32_t) value;
- (TestRequired_Builder*) clearDummy23;

- (BOOL) hasDummy24;
- (int32_t) dummy24;
- (TestRequired_Builder*) setDummy24:(int32_t) value;
- (TestRequired_Builder*) clearDummy24;

- (BOOL) hasDummy25;
- (int32_t) dummy25;
- (TestRequired_Builder*) setDummy25:(int32_t) value;
- (TestRequired_Builder*) clearDummy25;

- (BOOL) hasDummy26;
- (int32_t) dummy26;
- (TestRequired_Builder*) setDummy26:(int32_t) value;
- (TestRequired_Builder*) clearDummy26;

- (BOOL) hasDummy27;
- (int32_t) dummy27;
- (TestRequired_Builder*) setDummy27:(int32_t) value;
- (TestRequired_Builder*) clearDummy27;

- (BOOL) hasDummy28;
- (int32_t) dummy28;
- (TestRequired_Builder*) setDummy28:(int32_t) value;
- (TestRequired_Builder*) clearDummy28;

- (BOOL) hasDummy29;
- (int32_t) dummy29;
- (TestRequired_Builder*) setDummy29:(int32_t) value;
- (TestRequired_Builder*) clearDummy29;

- (BOOL) hasDummy30;
- (int32_t) dummy30;
- (TestRequired_Builder*) setDummy30:(int32_t) value;
- (TestRequired_Builder*) clearDummy30;

- (BOOL) hasDummy31;
- (int32_t) dummy31;
- (TestRequired_Builder*) setDummy31:(int32_t) value;
- (TestRequired_Builder*) clearDummy31;

- (BOOL) hasDummy32;
- (int32_t) dummy32;
- (TestRequired_Builder*) setDummy32:(int32_t) value;
- (TestRequired_Builder*) clearDummy32;

- (BOOL) hasC;
- (int32_t) c;
- (TestRequired_Builder*) setC:(int32_t) value;
- (TestRequired_Builder*) clearC;
@end

@interface TestRequiredForeign : PBGeneratedMessage {
@private
  BOOL hasDummy_:1;
  BOOL hasOptionalMessage_:1;
  int32_t dummy;
  TestRequired* optionalMessage;
  NSMutableArray* mutableRepeatedMessageList;
}
- (BOOL) hasOptionalMessage;
- (BOOL) hasDummy;
@property (readonly, retain) TestRequired* optionalMessage;
@property (readonly) int32_t dummy;
- (NSArray*) repeatedMessageList;
- (TestRequired*) repeatedMessageAtIndex:(int32_t) index;

+ (TestRequiredForeign*) defaultInstance;
- (TestRequiredForeign*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestRequiredForeign_Builder*) builder;
+ (TestRequiredForeign_Builder*) builder;
+ (TestRequiredForeign_Builder*) builderWithPrototype:(TestRequiredForeign*) prototype;

+ (TestRequiredForeign*) parseFromData:(NSData*) data;
+ (TestRequiredForeign*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestRequiredForeign*) parseFromInputStream:(NSInputStream*) input;
+ (TestRequiredForeign*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestRequiredForeign*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestRequiredForeign*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestRequiredForeign_Builder : PBGeneratedMessage_Builder {
@private
  TestRequiredForeign* result;
}

- (TestRequiredForeign*) defaultInstance;

- (TestRequiredForeign_Builder*) clear;
- (TestRequiredForeign_Builder*) clone;

- (TestRequiredForeign*) build;
- (TestRequiredForeign*) buildPartial;

- (TestRequiredForeign_Builder*) mergeFrom:(TestRequiredForeign*) other;
- (TestRequiredForeign_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestRequiredForeign_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasOptionalMessage;
- (TestRequired*) optionalMessage;
- (TestRequiredForeign_Builder*) setOptionalMessage:(TestRequired*) value;
- (TestRequiredForeign_Builder*) setOptionalMessageBuilder:(TestRequired_Builder*) builderForValue;
- (TestRequiredForeign_Builder*) mergeOptionalMessage:(TestRequired*) value;
- (TestRequiredForeign_Builder*) clearOptionalMessage;

- (NSArray*) repeatedMessageList;
- (TestRequired*) repeatedMessageAtIndex:(int32_t) index;
- (TestRequiredForeign_Builder*) replaceRepeatedMessageAtIndex:(int32_t) index with:(TestRequired*) value;
- (TestRequiredForeign_Builder*) addRepeatedMessage:(TestRequired*) value;
- (TestRequiredForeign_Builder*) addAllRepeatedMessage:(NSArray*) values;
- (TestRequiredForeign_Builder*) clearRepeatedMessageList;

- (BOOL) hasDummy;
- (int32_t) dummy;
- (TestRequiredForeign_Builder*) setDummy:(int32_t) value;
- (TestRequiredForeign_Builder*) clearDummy;
@end

@interface TestForeignNested : PBGeneratedMessage {
@private
  BOOL hasForeignNested_:1;
  TestAllTypes_NestedMessage* foreignNested;
}
- (BOOL) hasForeignNested;
@property (readonly, retain) TestAllTypes_NestedMessage* foreignNested;

+ (TestForeignNested*) defaultInstance;
- (TestForeignNested*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestForeignNested_Builder*) builder;
+ (TestForeignNested_Builder*) builder;
+ (TestForeignNested_Builder*) builderWithPrototype:(TestForeignNested*) prototype;

+ (TestForeignNested*) parseFromData:(NSData*) data;
+ (TestForeignNested*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestForeignNested*) parseFromInputStream:(NSInputStream*) input;
+ (TestForeignNested*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestForeignNested*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestForeignNested*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestForeignNested_Builder : PBGeneratedMessage_Builder {
@private
  TestForeignNested* result;
}

- (TestForeignNested*) defaultInstance;

- (TestForeignNested_Builder*) clear;
- (TestForeignNested_Builder*) clone;

- (TestForeignNested*) build;
- (TestForeignNested*) buildPartial;

- (TestForeignNested_Builder*) mergeFrom:(TestForeignNested*) other;
- (TestForeignNested_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestForeignNested_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasForeignNested;
- (TestAllTypes_NestedMessage*) foreignNested;
- (TestForeignNested_Builder*) setForeignNested:(TestAllTypes_NestedMessage*) value;
- (TestForeignNested_Builder*) setForeignNestedBuilder:(TestAllTypes_NestedMessage_Builder*) builderForValue;
- (TestForeignNested_Builder*) mergeForeignNested:(TestAllTypes_NestedMessage*) value;
- (TestForeignNested_Builder*) clearForeignNested;
@end

@interface TestEmptyMessage : PBGeneratedMessage {
@private
}

+ (TestEmptyMessage*) defaultInstance;
- (TestEmptyMessage*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestEmptyMessage_Builder*) builder;
+ (TestEmptyMessage_Builder*) builder;
+ (TestEmptyMessage_Builder*) builderWithPrototype:(TestEmptyMessage*) prototype;

+ (TestEmptyMessage*) parseFromData:(NSData*) data;
+ (TestEmptyMessage*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestEmptyMessage*) parseFromInputStream:(NSInputStream*) input;
+ (TestEmptyMessage*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestEmptyMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestEmptyMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestEmptyMessage_Builder : PBGeneratedMessage_Builder {
@private
  TestEmptyMessage* result;
}

- (TestEmptyMessage*) defaultInstance;

- (TestEmptyMessage_Builder*) clear;
- (TestEmptyMessage_Builder*) clone;

- (TestEmptyMessage*) build;
- (TestEmptyMessage*) buildPartial;

- (TestEmptyMessage_Builder*) mergeFrom:(TestEmptyMessage*) other;
- (TestEmptyMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestEmptyMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestEmptyMessageWithExtensions : PBExtendableMessage {
@private
}

+ (TestEmptyMessageWithExtensions*) defaultInstance;
- (TestEmptyMessageWithExtensions*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestEmptyMessageWithExtensions_Builder*) builder;
+ (TestEmptyMessageWithExtensions_Builder*) builder;
+ (TestEmptyMessageWithExtensions_Builder*) builderWithPrototype:(TestEmptyMessageWithExtensions*) prototype;

+ (TestEmptyMessageWithExtensions*) parseFromData:(NSData*) data;
+ (TestEmptyMessageWithExtensions*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestEmptyMessageWithExtensions*) parseFromInputStream:(NSInputStream*) input;
+ (TestEmptyMessageWithExtensions*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestEmptyMessageWithExtensions*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestEmptyMessageWithExtensions*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestEmptyMessageWithExtensions_Builder : PBExtendableMessage_Builder {
@private
  TestEmptyMessageWithExtensions* result;
}

- (TestEmptyMessageWithExtensions*) defaultInstance;

- (TestEmptyMessageWithExtensions_Builder*) clear;
- (TestEmptyMessageWithExtensions_Builder*) clone;

- (TestEmptyMessageWithExtensions*) build;
- (TestEmptyMessageWithExtensions*) buildPartial;

- (TestEmptyMessageWithExtensions_Builder*) mergeFrom:(TestEmptyMessageWithExtensions*) other;
- (TestEmptyMessageWithExtensions_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestEmptyMessageWithExtensions_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestReallyLargeTagNumber : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  BOOL hasBb_:1;
  int32_t a;
  int32_t bb;
}
- (BOOL) hasA;
- (BOOL) hasBb;
@property (readonly) int32_t a;
@property (readonly) int32_t bb;

+ (TestReallyLargeTagNumber*) defaultInstance;
- (TestReallyLargeTagNumber*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestReallyLargeTagNumber_Builder*) builder;
+ (TestReallyLargeTagNumber_Builder*) builder;
+ (TestReallyLargeTagNumber_Builder*) builderWithPrototype:(TestReallyLargeTagNumber*) prototype;

+ (TestReallyLargeTagNumber*) parseFromData:(NSData*) data;
+ (TestReallyLargeTagNumber*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestReallyLargeTagNumber*) parseFromInputStream:(NSInputStream*) input;
+ (TestReallyLargeTagNumber*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestReallyLargeTagNumber*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestReallyLargeTagNumber*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestReallyLargeTagNumber_Builder : PBGeneratedMessage_Builder {
@private
  TestReallyLargeTagNumber* result;
}

- (TestReallyLargeTagNumber*) defaultInstance;

- (TestReallyLargeTagNumber_Builder*) clear;
- (TestReallyLargeTagNumber_Builder*) clone;

- (TestReallyLargeTagNumber*) build;
- (TestReallyLargeTagNumber*) buildPartial;

- (TestReallyLargeTagNumber_Builder*) mergeFrom:(TestReallyLargeTagNumber*) other;
- (TestReallyLargeTagNumber_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestReallyLargeTagNumber_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (TestReallyLargeTagNumber_Builder*) setA:(int32_t) value;
- (TestReallyLargeTagNumber_Builder*) clearA;

- (BOOL) hasBb;
- (int32_t) bb;
- (TestReallyLargeTagNumber_Builder*) setBb:(int32_t) value;
- (TestReallyLargeTagNumber_Builder*) clearBb;
@end

@interface TestRecursiveMessage : PBGeneratedMessage {
@private
  BOOL hasI_:1;
  BOOL hasA_:1;
  int32_t i;
  TestRecursiveMessage* a;
}
- (BOOL) hasA;
- (BOOL) hasI;
@property (readonly, retain) TestRecursiveMessage* a;
@property (readonly) int32_t i;

+ (TestRecursiveMessage*) defaultInstance;
- (TestRecursiveMessage*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestRecursiveMessage_Builder*) builder;
+ (TestRecursiveMessage_Builder*) builder;
+ (TestRecursiveMessage_Builder*) builderWithPrototype:(TestRecursiveMessage*) prototype;

+ (TestRecursiveMessage*) parseFromData:(NSData*) data;
+ (TestRecursiveMessage*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestRecursiveMessage*) parseFromInputStream:(NSInputStream*) input;
+ (TestRecursiveMessage*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestRecursiveMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestRecursiveMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestRecursiveMessage_Builder : PBGeneratedMessage_Builder {
@private
  TestRecursiveMessage* result;
}

- (TestRecursiveMessage*) defaultInstance;

- (TestRecursiveMessage_Builder*) clear;
- (TestRecursiveMessage_Builder*) clone;

- (TestRecursiveMessage*) build;
- (TestRecursiveMessage*) buildPartial;

- (TestRecursiveMessage_Builder*) mergeFrom:(TestRecursiveMessage*) other;
- (TestRecursiveMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestRecursiveMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (TestRecursiveMessage*) a;
- (TestRecursiveMessage_Builder*) setA:(TestRecursiveMessage*) value;
- (TestRecursiveMessage_Builder*) setABuilder:(TestRecursiveMessage_Builder*) builderForValue;
- (TestRecursiveMessage_Builder*) mergeA:(TestRecursiveMessage*) value;
- (TestRecursiveMessage_Builder*) clearA;

- (BOOL) hasI;
- (int32_t) i;
- (TestRecursiveMessage_Builder*) setI:(int32_t) value;
- (TestRecursiveMessage_Builder*) clearI;
@end

@interface TestMutualRecursionA : PBGeneratedMessage {
@private
  BOOL hasBb_:1;
  TestMutualRecursionB* bb;
}
- (BOOL) hasBb;
@property (readonly, retain) TestMutualRecursionB* bb;

+ (TestMutualRecursionA*) defaultInstance;
- (TestMutualRecursionA*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestMutualRecursionA_Builder*) builder;
+ (TestMutualRecursionA_Builder*) builder;
+ (TestMutualRecursionA_Builder*) builderWithPrototype:(TestMutualRecursionA*) prototype;

+ (TestMutualRecursionA*) parseFromData:(NSData*) data;
+ (TestMutualRecursionA*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestMutualRecursionA*) parseFromInputStream:(NSInputStream*) input;
+ (TestMutualRecursionA*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestMutualRecursionA*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestMutualRecursionA*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestMutualRecursionA_Builder : PBGeneratedMessage_Builder {
@private
  TestMutualRecursionA* result;
}

- (TestMutualRecursionA*) defaultInstance;

- (TestMutualRecursionA_Builder*) clear;
- (TestMutualRecursionA_Builder*) clone;

- (TestMutualRecursionA*) build;
- (TestMutualRecursionA*) buildPartial;

- (TestMutualRecursionA_Builder*) mergeFrom:(TestMutualRecursionA*) other;
- (TestMutualRecursionA_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestMutualRecursionA_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasBb;
- (TestMutualRecursionB*) bb;
- (TestMutualRecursionA_Builder*) setBb:(TestMutualRecursionB*) value;
- (TestMutualRecursionA_Builder*) setBbBuilder:(TestMutualRecursionB_Builder*) builderForValue;
- (TestMutualRecursionA_Builder*) mergeBb:(TestMutualRecursionB*) value;
- (TestMutualRecursionA_Builder*) clearBb;
@end

@interface TestMutualRecursionB : PBGeneratedMessage {
@private
  BOOL hasOptionalInt32_:1;
  BOOL hasA_:1;
  int32_t optionalInt32;
  TestMutualRecursionA* a;
}
- (BOOL) hasA;
- (BOOL) hasOptionalInt32;
@property (readonly, retain) TestMutualRecursionA* a;
@property (readonly) int32_t optionalInt32;

+ (TestMutualRecursionB*) defaultInstance;
- (TestMutualRecursionB*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestMutualRecursionB_Builder*) builder;
+ (TestMutualRecursionB_Builder*) builder;
+ (TestMutualRecursionB_Builder*) builderWithPrototype:(TestMutualRecursionB*) prototype;

+ (TestMutualRecursionB*) parseFromData:(NSData*) data;
+ (TestMutualRecursionB*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestMutualRecursionB*) parseFromInputStream:(NSInputStream*) input;
+ (TestMutualRecursionB*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestMutualRecursionB*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestMutualRecursionB*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestMutualRecursionB_Builder : PBGeneratedMessage_Builder {
@private
  TestMutualRecursionB* result;
}

- (TestMutualRecursionB*) defaultInstance;

- (TestMutualRecursionB_Builder*) clear;
- (TestMutualRecursionB_Builder*) clone;

- (TestMutualRecursionB*) build;
- (TestMutualRecursionB*) buildPartial;

- (TestMutualRecursionB_Builder*) mergeFrom:(TestMutualRecursionB*) other;
- (TestMutualRecursionB_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestMutualRecursionB_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (TestMutualRecursionA*) a;
- (TestMutualRecursionB_Builder*) setA:(TestMutualRecursionA*) value;
- (TestMutualRecursionB_Builder*) setABuilder:(TestMutualRecursionA_Builder*) builderForValue;
- (TestMutualRecursionB_Builder*) mergeA:(TestMutualRecursionA*) value;
- (TestMutualRecursionB_Builder*) clearA;

- (BOOL) hasOptionalInt32;
- (int32_t) optionalInt32;
- (TestMutualRecursionB_Builder*) setOptionalInt32:(int32_t) value;
- (TestMutualRecursionB_Builder*) clearOptionalInt32;
@end

@interface TestDupFieldNumber : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  BOOL hasFoo_:1;
  BOOL hasBar_:1;
  int32_t a;
  TestDupFieldNumber_Foo* foo;
  TestDupFieldNumber_Bar* bar;
}
- (BOOL) hasA;
- (BOOL) hasFoo;
- (BOOL) hasBar;
@property (readonly) int32_t a;
@property (readonly, retain) TestDupFieldNumber_Foo* foo;
@property (readonly, retain) TestDupFieldNumber_Bar* bar;

+ (TestDupFieldNumber*) defaultInstance;
- (TestDupFieldNumber*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestDupFieldNumber_Builder*) builder;
+ (TestDupFieldNumber_Builder*) builder;
+ (TestDupFieldNumber_Builder*) builderWithPrototype:(TestDupFieldNumber*) prototype;

+ (TestDupFieldNumber*) parseFromData:(NSData*) data;
+ (TestDupFieldNumber*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestDupFieldNumber*) parseFromInputStream:(NSInputStream*) input;
+ (TestDupFieldNumber*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestDupFieldNumber*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestDupFieldNumber*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestDupFieldNumber_Foo : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  int32_t a;
}
- (BOOL) hasA;
@property (readonly) int32_t a;

+ (TestDupFieldNumber_Foo*) defaultInstance;
- (TestDupFieldNumber_Foo*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestDupFieldNumber_Foo_Builder*) builder;
+ (TestDupFieldNumber_Foo_Builder*) builder;
+ (TestDupFieldNumber_Foo_Builder*) builderWithPrototype:(TestDupFieldNumber_Foo*) prototype;

+ (TestDupFieldNumber_Foo*) parseFromData:(NSData*) data;
+ (TestDupFieldNumber_Foo*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestDupFieldNumber_Foo*) parseFromInputStream:(NSInputStream*) input;
+ (TestDupFieldNumber_Foo*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestDupFieldNumber_Foo*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestDupFieldNumber_Foo*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestDupFieldNumber_Foo_Builder : PBGeneratedMessage_Builder {
@private
  TestDupFieldNumber_Foo* result;
}

- (TestDupFieldNumber_Foo*) defaultInstance;

- (TestDupFieldNumber_Foo_Builder*) clear;
- (TestDupFieldNumber_Foo_Builder*) clone;

- (TestDupFieldNumber_Foo*) build;
- (TestDupFieldNumber_Foo*) buildPartial;

- (TestDupFieldNumber_Foo_Builder*) mergeFrom:(TestDupFieldNumber_Foo*) other;
- (TestDupFieldNumber_Foo_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestDupFieldNumber_Foo_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (TestDupFieldNumber_Foo_Builder*) setA:(int32_t) value;
- (TestDupFieldNumber_Foo_Builder*) clearA;
@end

@interface TestDupFieldNumber_Bar : PBGeneratedMessage {
@private
  BOOL hasA_:1;
  int32_t a;
}
- (BOOL) hasA;
@property (readonly) int32_t a;

+ (TestDupFieldNumber_Bar*) defaultInstance;
- (TestDupFieldNumber_Bar*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestDupFieldNumber_Bar_Builder*) builder;
+ (TestDupFieldNumber_Bar_Builder*) builder;
+ (TestDupFieldNumber_Bar_Builder*) builderWithPrototype:(TestDupFieldNumber_Bar*) prototype;

+ (TestDupFieldNumber_Bar*) parseFromData:(NSData*) data;
+ (TestDupFieldNumber_Bar*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestDupFieldNumber_Bar*) parseFromInputStream:(NSInputStream*) input;
+ (TestDupFieldNumber_Bar*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestDupFieldNumber_Bar*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestDupFieldNumber_Bar*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestDupFieldNumber_Bar_Builder : PBGeneratedMessage_Builder {
@private
  TestDupFieldNumber_Bar* result;
}

- (TestDupFieldNumber_Bar*) defaultInstance;

- (TestDupFieldNumber_Bar_Builder*) clear;
- (TestDupFieldNumber_Bar_Builder*) clone;

- (TestDupFieldNumber_Bar*) build;
- (TestDupFieldNumber_Bar*) buildPartial;

- (TestDupFieldNumber_Bar_Builder*) mergeFrom:(TestDupFieldNumber_Bar*) other;
- (TestDupFieldNumber_Bar_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestDupFieldNumber_Bar_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (TestDupFieldNumber_Bar_Builder*) setA:(int32_t) value;
- (TestDupFieldNumber_Bar_Builder*) clearA;
@end

@interface TestDupFieldNumber_Builder : PBGeneratedMessage_Builder {
@private
  TestDupFieldNumber* result;
}

- (TestDupFieldNumber*) defaultInstance;

- (TestDupFieldNumber_Builder*) clear;
- (TestDupFieldNumber_Builder*) clone;

- (TestDupFieldNumber*) build;
- (TestDupFieldNumber*) buildPartial;

- (TestDupFieldNumber_Builder*) mergeFrom:(TestDupFieldNumber*) other;
- (TestDupFieldNumber_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestDupFieldNumber_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasA;
- (int32_t) a;
- (TestDupFieldNumber_Builder*) setA:(int32_t) value;
- (TestDupFieldNumber_Builder*) clearA;

- (BOOL) hasFoo;
- (TestDupFieldNumber_Foo*) foo;
- (TestDupFieldNumber_Builder*) setFoo:(TestDupFieldNumber_Foo*) value;
- (TestDupFieldNumber_Builder*) setFooBuilder:(TestDupFieldNumber_Foo_Builder*) builderForValue;
- (TestDupFieldNumber_Builder*) mergeFoo:(TestDupFieldNumber_Foo*) value;
- (TestDupFieldNumber_Builder*) clearFoo;

- (BOOL) hasBar;
- (TestDupFieldNumber_Bar*) bar;
- (TestDupFieldNumber_Builder*) setBar:(TestDupFieldNumber_Bar*) value;
- (TestDupFieldNumber_Builder*) setBarBuilder:(TestDupFieldNumber_Bar_Builder*) builderForValue;
- (TestDupFieldNumber_Builder*) mergeBar:(TestDupFieldNumber_Bar*) value;
- (TestDupFieldNumber_Builder*) clearBar;
@end

@interface TestNestedMessageHasBits : PBGeneratedMessage {
@private
  BOOL hasOptionalNestedMessage_:1;
  TestNestedMessageHasBits_NestedMessage* optionalNestedMessage;
}
- (BOOL) hasOptionalNestedMessage;
@property (readonly, retain) TestNestedMessageHasBits_NestedMessage* optionalNestedMessage;

+ (TestNestedMessageHasBits*) defaultInstance;
- (TestNestedMessageHasBits*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestNestedMessageHasBits_Builder*) builder;
+ (TestNestedMessageHasBits_Builder*) builder;
+ (TestNestedMessageHasBits_Builder*) builderWithPrototype:(TestNestedMessageHasBits*) prototype;

+ (TestNestedMessageHasBits*) parseFromData:(NSData*) data;
+ (TestNestedMessageHasBits*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestNestedMessageHasBits*) parseFromInputStream:(NSInputStream*) input;
+ (TestNestedMessageHasBits*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestNestedMessageHasBits*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestNestedMessageHasBits*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestNestedMessageHasBits_NestedMessage : PBGeneratedMessage {
@private
  NSMutableArray* mutableNestedmessageRepeatedInt32List;
  NSMutableArray* mutableNestedmessageRepeatedForeignmessageList;
}
- (NSArray*) nestedmessageRepeatedInt32List;
- (int32_t) nestedmessageRepeatedInt32AtIndex:(int32_t) index;
- (NSArray*) nestedmessageRepeatedForeignmessageList;
- (ForeignMessage*) nestedmessageRepeatedForeignmessageAtIndex:(int32_t) index;

+ (TestNestedMessageHasBits_NestedMessage*) defaultInstance;
- (TestNestedMessageHasBits_NestedMessage*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestNestedMessageHasBits_NestedMessage_Builder*) builder;
+ (TestNestedMessageHasBits_NestedMessage_Builder*) builder;
+ (TestNestedMessageHasBits_NestedMessage_Builder*) builderWithPrototype:(TestNestedMessageHasBits_NestedMessage*) prototype;

+ (TestNestedMessageHasBits_NestedMessage*) parseFromData:(NSData*) data;
+ (TestNestedMessageHasBits_NestedMessage*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestNestedMessageHasBits_NestedMessage*) parseFromInputStream:(NSInputStream*) input;
+ (TestNestedMessageHasBits_NestedMessage*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestNestedMessageHasBits_NestedMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestNestedMessageHasBits_NestedMessage*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestNestedMessageHasBits_NestedMessage_Builder : PBGeneratedMessage_Builder {
@private
  TestNestedMessageHasBits_NestedMessage* result;
}

- (TestNestedMessageHasBits_NestedMessage*) defaultInstance;

- (TestNestedMessageHasBits_NestedMessage_Builder*) clear;
- (TestNestedMessageHasBits_NestedMessage_Builder*) clone;

- (TestNestedMessageHasBits_NestedMessage*) build;
- (TestNestedMessageHasBits_NestedMessage*) buildPartial;

- (TestNestedMessageHasBits_NestedMessage_Builder*) mergeFrom:(TestNestedMessageHasBits_NestedMessage*) other;
- (TestNestedMessageHasBits_NestedMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestNestedMessageHasBits_NestedMessage_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (NSArray*) nestedmessageRepeatedInt32List;
- (int32_t) nestedmessageRepeatedInt32AtIndex:(int32_t) index;
- (TestNestedMessageHasBits_NestedMessage_Builder*) replaceNestedmessageRepeatedInt32AtIndex:(int32_t) index with:(int32_t) value;
- (TestNestedMessageHasBits_NestedMessage_Builder*) addNestedmessageRepeatedInt32:(int32_t) value;
- (TestNestedMessageHasBits_NestedMessage_Builder*) addAllNestedmessageRepeatedInt32:(NSArray*) values;
- (TestNestedMessageHasBits_NestedMessage_Builder*) clearNestedmessageRepeatedInt32List;

- (NSArray*) nestedmessageRepeatedForeignmessageList;
- (ForeignMessage*) nestedmessageRepeatedForeignmessageAtIndex:(int32_t) index;
- (TestNestedMessageHasBits_NestedMessage_Builder*) replaceNestedmessageRepeatedForeignmessageAtIndex:(int32_t) index with:(ForeignMessage*) value;
- (TestNestedMessageHasBits_NestedMessage_Builder*) addNestedmessageRepeatedForeignmessage:(ForeignMessage*) value;
- (TestNestedMessageHasBits_NestedMessage_Builder*) addAllNestedmessageRepeatedForeignmessage:(NSArray*) values;
- (TestNestedMessageHasBits_NestedMessage_Builder*) clearNestedmessageRepeatedForeignmessageList;
@end

@interface TestNestedMessageHasBits_Builder : PBGeneratedMessage_Builder {
@private
  TestNestedMessageHasBits* result;
}

- (TestNestedMessageHasBits*) defaultInstance;

- (TestNestedMessageHasBits_Builder*) clear;
- (TestNestedMessageHasBits_Builder*) clone;

- (TestNestedMessageHasBits*) build;
- (TestNestedMessageHasBits*) buildPartial;

- (TestNestedMessageHasBits_Builder*) mergeFrom:(TestNestedMessageHasBits*) other;
- (TestNestedMessageHasBits_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestNestedMessageHasBits_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasOptionalNestedMessage;
- (TestNestedMessageHasBits_NestedMessage*) optionalNestedMessage;
- (TestNestedMessageHasBits_Builder*) setOptionalNestedMessage:(TestNestedMessageHasBits_NestedMessage*) value;
- (TestNestedMessageHasBits_Builder*) setOptionalNestedMessageBuilder:(TestNestedMessageHasBits_NestedMessage_Builder*) builderForValue;
- (TestNestedMessageHasBits_Builder*) mergeOptionalNestedMessage:(TestNestedMessageHasBits_NestedMessage*) value;
- (TestNestedMessageHasBits_Builder*) clearOptionalNestedMessage;
@end

@interface TestCamelCaseFieldNames : PBGeneratedMessage {
@private
  BOOL hasPrimitiveField_:1;
  BOOL hasStringField_:1;
  BOOL hasStringPieceField_:1;
  BOOL hasCordField_:1;
  BOOL hasMessageField_:1;
  BOOL hasEnumField_:1;
  int32_t primitiveField;
  NSString* stringField;
  NSString* stringPieceField;
  NSString* cordField;
  ForeignMessage* messageField;
  ForeignEnum enumField;
  NSMutableArray* mutableRepeatedPrimitiveFieldList;
  NSMutableArray* mutableRepeatedStringFieldList;
  NSMutableArray* mutableRepeatedStringPieceFieldList;
  NSMutableArray* mutableRepeatedCordFieldList;
  NSMutableArray* mutableRepeatedMessageFieldList;
  NSMutableArray* mutableRepeatedEnumFieldList;
}
- (BOOL) hasPrimitiveField;
- (BOOL) hasStringField;
- (BOOL) hasEnumField;
- (BOOL) hasMessageField;
- (BOOL) hasStringPieceField;
- (BOOL) hasCordField;
@property (readonly) int32_t primitiveField;
@property (readonly, retain) NSString* stringField;
@property (readonly) ForeignEnum enumField;
@property (readonly, retain) ForeignMessage* messageField;
@property (readonly, retain) NSString* stringPieceField;
@property (readonly, retain) NSString* cordField;
- (NSArray*) repeatedPrimitiveFieldList;
- (int32_t) repeatedPrimitiveFieldAtIndex:(int32_t) index;
- (NSArray*) repeatedStringFieldList;
- (NSString*) repeatedStringFieldAtIndex:(int32_t) index;
- (NSArray*) repeatedEnumFieldList;
- (ForeignEnum) repeatedEnumFieldAtIndex:(int32_t) index;
- (NSArray*) repeatedMessageFieldList;
- (ForeignMessage*) repeatedMessageFieldAtIndex:(int32_t) index;
- (NSArray*) repeatedStringPieceFieldList;
- (NSString*) repeatedStringPieceFieldAtIndex:(int32_t) index;
- (NSArray*) repeatedCordFieldList;
- (NSString*) repeatedCordFieldAtIndex:(int32_t) index;

+ (TestCamelCaseFieldNames*) defaultInstance;
- (TestCamelCaseFieldNames*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestCamelCaseFieldNames_Builder*) builder;
+ (TestCamelCaseFieldNames_Builder*) builder;
+ (TestCamelCaseFieldNames_Builder*) builderWithPrototype:(TestCamelCaseFieldNames*) prototype;

+ (TestCamelCaseFieldNames*) parseFromData:(NSData*) data;
+ (TestCamelCaseFieldNames*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestCamelCaseFieldNames*) parseFromInputStream:(NSInputStream*) input;
+ (TestCamelCaseFieldNames*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestCamelCaseFieldNames*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestCamelCaseFieldNames*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestCamelCaseFieldNames_Builder : PBGeneratedMessage_Builder {
@private
  TestCamelCaseFieldNames* result;
}

- (TestCamelCaseFieldNames*) defaultInstance;

- (TestCamelCaseFieldNames_Builder*) clear;
- (TestCamelCaseFieldNames_Builder*) clone;

- (TestCamelCaseFieldNames*) build;
- (TestCamelCaseFieldNames*) buildPartial;

- (TestCamelCaseFieldNames_Builder*) mergeFrom:(TestCamelCaseFieldNames*) other;
- (TestCamelCaseFieldNames_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestCamelCaseFieldNames_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasPrimitiveField;
- (int32_t) primitiveField;
- (TestCamelCaseFieldNames_Builder*) setPrimitiveField:(int32_t) value;
- (TestCamelCaseFieldNames_Builder*) clearPrimitiveField;

- (BOOL) hasStringField;
- (NSString*) stringField;
- (TestCamelCaseFieldNames_Builder*) setStringField:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) clearStringField;

- (BOOL) hasEnumField;
- (ForeignEnum) enumField;
- (TestCamelCaseFieldNames_Builder*) setEnumField:(ForeignEnum) value;
- (TestCamelCaseFieldNames_Builder*) clearEnumField;

- (BOOL) hasMessageField;
- (ForeignMessage*) messageField;
- (TestCamelCaseFieldNames_Builder*) setMessageField:(ForeignMessage*) value;
- (TestCamelCaseFieldNames_Builder*) setMessageFieldBuilder:(ForeignMessage_Builder*) builderForValue;
- (TestCamelCaseFieldNames_Builder*) mergeMessageField:(ForeignMessage*) value;
- (TestCamelCaseFieldNames_Builder*) clearMessageField;

- (BOOL) hasStringPieceField;
- (NSString*) stringPieceField;
- (TestCamelCaseFieldNames_Builder*) setStringPieceField:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) clearStringPieceField;

- (BOOL) hasCordField;
- (NSString*) cordField;
- (TestCamelCaseFieldNames_Builder*) setCordField:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) clearCordField;

- (NSArray*) repeatedPrimitiveFieldList;
- (int32_t) repeatedPrimitiveFieldAtIndex:(int32_t) index;
- (TestCamelCaseFieldNames_Builder*) replaceRepeatedPrimitiveFieldAtIndex:(int32_t) index with:(int32_t) value;
- (TestCamelCaseFieldNames_Builder*) addRepeatedPrimitiveField:(int32_t) value;
- (TestCamelCaseFieldNames_Builder*) addAllRepeatedPrimitiveField:(NSArray*) values;
- (TestCamelCaseFieldNames_Builder*) clearRepeatedPrimitiveFieldList;

- (NSArray*) repeatedStringFieldList;
- (NSString*) repeatedStringFieldAtIndex:(int32_t) index;
- (TestCamelCaseFieldNames_Builder*) replaceRepeatedStringFieldAtIndex:(int32_t) index with:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) addRepeatedStringField:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) addAllRepeatedStringField:(NSArray*) values;
- (TestCamelCaseFieldNames_Builder*) clearRepeatedStringFieldList;

- (NSArray*) repeatedEnumFieldList;
- (ForeignEnum) repeatedEnumFieldAtIndex:(int32_t) index;
- (TestCamelCaseFieldNames_Builder*) replaceRepeatedEnumFieldAtIndex:(int32_t) index with:(ForeignEnum) value;
- (TestCamelCaseFieldNames_Builder*) addRepeatedEnumField:(ForeignEnum) value;
- (TestCamelCaseFieldNames_Builder*) addAllRepeatedEnumField:(NSArray*) values;
- (TestCamelCaseFieldNames_Builder*) clearRepeatedEnumFieldList;

- (NSArray*) repeatedMessageFieldList;
- (ForeignMessage*) repeatedMessageFieldAtIndex:(int32_t) index;
- (TestCamelCaseFieldNames_Builder*) replaceRepeatedMessageFieldAtIndex:(int32_t) index with:(ForeignMessage*) value;
- (TestCamelCaseFieldNames_Builder*) addRepeatedMessageField:(ForeignMessage*) value;
- (TestCamelCaseFieldNames_Builder*) addAllRepeatedMessageField:(NSArray*) values;
- (TestCamelCaseFieldNames_Builder*) clearRepeatedMessageFieldList;

- (NSArray*) repeatedStringPieceFieldList;
- (NSString*) repeatedStringPieceFieldAtIndex:(int32_t) index;
- (TestCamelCaseFieldNames_Builder*) replaceRepeatedStringPieceFieldAtIndex:(int32_t) index with:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) addRepeatedStringPieceField:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) addAllRepeatedStringPieceField:(NSArray*) values;
- (TestCamelCaseFieldNames_Builder*) clearRepeatedStringPieceFieldList;

- (NSArray*) repeatedCordFieldList;
- (NSString*) repeatedCordFieldAtIndex:(int32_t) index;
- (TestCamelCaseFieldNames_Builder*) replaceRepeatedCordFieldAtIndex:(int32_t) index with:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) addRepeatedCordField:(NSString*) value;
- (TestCamelCaseFieldNames_Builder*) addAllRepeatedCordField:(NSArray*) values;
- (TestCamelCaseFieldNames_Builder*) clearRepeatedCordFieldList;
@end

@interface TestFieldOrderings : PBExtendableMessage {
@private
  BOOL hasMyFloat_:1;
  BOOL hasMyInt_:1;
  BOOL hasMyString_:1;
  Float32 myFloat;
  int64_t myInt;
  NSString* myString;
}
- (BOOL) hasMyString;
- (BOOL) hasMyInt;
- (BOOL) hasMyFloat;
@property (readonly, retain) NSString* myString;
@property (readonly) int64_t myInt;
@property (readonly) Float32 myFloat;

+ (TestFieldOrderings*) defaultInstance;
- (TestFieldOrderings*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestFieldOrderings_Builder*) builder;
+ (TestFieldOrderings_Builder*) builder;
+ (TestFieldOrderings_Builder*) builderWithPrototype:(TestFieldOrderings*) prototype;

+ (TestFieldOrderings*) parseFromData:(NSData*) data;
+ (TestFieldOrderings*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestFieldOrderings*) parseFromInputStream:(NSInputStream*) input;
+ (TestFieldOrderings*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestFieldOrderings*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestFieldOrderings*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestFieldOrderings_Builder : PBExtendableMessage_Builder {
@private
  TestFieldOrderings* result;
}

- (TestFieldOrderings*) defaultInstance;

- (TestFieldOrderings_Builder*) clear;
- (TestFieldOrderings_Builder*) clone;

- (TestFieldOrderings*) build;
- (TestFieldOrderings*) buildPartial;

- (TestFieldOrderings_Builder*) mergeFrom:(TestFieldOrderings*) other;
- (TestFieldOrderings_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestFieldOrderings_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasMyString;
- (NSString*) myString;
- (TestFieldOrderings_Builder*) setMyString:(NSString*) value;
- (TestFieldOrderings_Builder*) clearMyString;

- (BOOL) hasMyInt;
- (int64_t) myInt;
- (TestFieldOrderings_Builder*) setMyInt:(int64_t) value;
- (TestFieldOrderings_Builder*) clearMyInt;

- (BOOL) hasMyFloat;
- (Float32) myFloat;
- (TestFieldOrderings_Builder*) setMyFloat:(Float32) value;
- (TestFieldOrderings_Builder*) clearMyFloat;
@end

@interface TestExtremeDefaultValues : PBGeneratedMessage {
@private
  BOOL hasSmallInt64_:1;
  BOOL hasLargeUint64_:1;
  BOOL hasSmallInt32_:1;
  BOOL hasUtf8String_:1;
  BOOL hasEscapedBytes_:1;
  BOOL hasLargeUint32_:1;
  int64_t smallInt64;
  int64_t largeUint64;
  int32_t smallInt32;
  NSString* utf8String;
  NSData* escapedBytes;
  int32_t largeUint32;
}
- (BOOL) hasEscapedBytes;
- (BOOL) hasLargeUint32;
- (BOOL) hasLargeUint64;
- (BOOL) hasSmallInt32;
- (BOOL) hasSmallInt64;
- (BOOL) hasUtf8String;
@property (readonly, retain) NSData* escapedBytes;
@property (readonly) int32_t largeUint32;
@property (readonly) int64_t largeUint64;
@property (readonly) int32_t smallInt32;
@property (readonly) int64_t smallInt64;
@property (readonly, retain) NSString* utf8String;

+ (TestExtremeDefaultValues*) defaultInstance;
- (TestExtremeDefaultValues*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestExtremeDefaultValues_Builder*) builder;
+ (TestExtremeDefaultValues_Builder*) builder;
+ (TestExtremeDefaultValues_Builder*) builderWithPrototype:(TestExtremeDefaultValues*) prototype;

+ (TestExtremeDefaultValues*) parseFromData:(NSData*) data;
+ (TestExtremeDefaultValues*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestExtremeDefaultValues*) parseFromInputStream:(NSInputStream*) input;
+ (TestExtremeDefaultValues*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestExtremeDefaultValues*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestExtremeDefaultValues*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestExtremeDefaultValues_Builder : PBGeneratedMessage_Builder {
@private
  TestExtremeDefaultValues* result;
}

- (TestExtremeDefaultValues*) defaultInstance;

- (TestExtremeDefaultValues_Builder*) clear;
- (TestExtremeDefaultValues_Builder*) clone;

- (TestExtremeDefaultValues*) build;
- (TestExtremeDefaultValues*) buildPartial;

- (TestExtremeDefaultValues_Builder*) mergeFrom:(TestExtremeDefaultValues*) other;
- (TestExtremeDefaultValues_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestExtremeDefaultValues_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasEscapedBytes;
- (NSData*) escapedBytes;
- (TestExtremeDefaultValues_Builder*) setEscapedBytes:(NSData*) value;
- (TestExtremeDefaultValues_Builder*) clearEscapedBytes;

- (BOOL) hasLargeUint32;
- (int32_t) largeUint32;
- (TestExtremeDefaultValues_Builder*) setLargeUint32:(int32_t) value;
- (TestExtremeDefaultValues_Builder*) clearLargeUint32;

- (BOOL) hasLargeUint64;
- (int64_t) largeUint64;
- (TestExtremeDefaultValues_Builder*) setLargeUint64:(int64_t) value;
- (TestExtremeDefaultValues_Builder*) clearLargeUint64;

- (BOOL) hasSmallInt32;
- (int32_t) smallInt32;
- (TestExtremeDefaultValues_Builder*) setSmallInt32:(int32_t) value;
- (TestExtremeDefaultValues_Builder*) clearSmallInt32;

- (BOOL) hasSmallInt64;
- (int64_t) smallInt64;
- (TestExtremeDefaultValues_Builder*) setSmallInt64:(int64_t) value;
- (TestExtremeDefaultValues_Builder*) clearSmallInt64;

- (BOOL) hasUtf8String;
- (NSString*) utf8String;
- (TestExtremeDefaultValues_Builder*) setUtf8String:(NSString*) value;
- (TestExtremeDefaultValues_Builder*) clearUtf8String;
@end

@interface OneString : PBGeneratedMessage {
@private
  BOOL hasData_:1;
  NSString* data;
}
- (BOOL) hasData;
@property (readonly, retain) NSString* data;

+ (OneString*) defaultInstance;
- (OneString*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (OneString_Builder*) builder;
+ (OneString_Builder*) builder;
+ (OneString_Builder*) builderWithPrototype:(OneString*) prototype;

+ (OneString*) parseFromData:(NSData*) data;
+ (OneString*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OneString*) parseFromInputStream:(NSInputStream*) input;
+ (OneString*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OneString*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (OneString*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface OneString_Builder : PBGeneratedMessage_Builder {
@private
  OneString* result;
}

- (OneString*) defaultInstance;

- (OneString_Builder*) clear;
- (OneString_Builder*) clone;

- (OneString*) build;
- (OneString*) buildPartial;

- (OneString_Builder*) mergeFrom:(OneString*) other;
- (OneString_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (OneString_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasData;
- (NSString*) data;
- (OneString_Builder*) setData:(NSString*) value;
- (OneString_Builder*) clearData;
@end

@interface OneBytes : PBGeneratedMessage {
@private
  BOOL hasData_:1;
  NSData* data;
}
- (BOOL) hasData;
@property (readonly, retain) NSData* data;

+ (OneBytes*) defaultInstance;
- (OneBytes*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (OneBytes_Builder*) builder;
+ (OneBytes_Builder*) builder;
+ (OneBytes_Builder*) builderWithPrototype:(OneBytes*) prototype;

+ (OneBytes*) parseFromData:(NSData*) data;
+ (OneBytes*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OneBytes*) parseFromInputStream:(NSInputStream*) input;
+ (OneBytes*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (OneBytes*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (OneBytes*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface OneBytes_Builder : PBGeneratedMessage_Builder {
@private
  OneBytes* result;
}

- (OneBytes*) defaultInstance;

- (OneBytes_Builder*) clear;
- (OneBytes_Builder*) clone;

- (OneBytes*) build;
- (OneBytes*) buildPartial;

- (OneBytes_Builder*) mergeFrom:(OneBytes*) other;
- (OneBytes_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (OneBytes_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (BOOL) hasData;
- (NSData*) data;
- (OneBytes_Builder*) setData:(NSData*) value;
- (OneBytes_Builder*) clearData;
@end

@interface TestPackedTypes : PBGeneratedMessage {
@private
  NSMutableArray* mutablePackedBoolList;
  int32_t packedBoolMemoizedSerializedSize;
  NSMutableArray* mutablePackedDoubleList;
  int32_t packedDoubleMemoizedSerializedSize;
  NSMutableArray* mutablePackedFloatList;
  int32_t packedFloatMemoizedSerializedSize;
  NSMutableArray* mutablePackedInt64List;
  int32_t packedInt64MemoizedSerializedSize;
  NSMutableArray* mutablePackedUint64List;
  int32_t packedUint64MemoizedSerializedSize;
  NSMutableArray* mutablePackedInt32List;
  int32_t packedInt32MemoizedSerializedSize;
  NSMutableArray* mutablePackedFixed64List;
  int32_t packedFixed64MemoizedSerializedSize;
  NSMutableArray* mutablePackedFixed32List;
  int32_t packedFixed32MemoizedSerializedSize;
  NSMutableArray* mutablePackedUint32List;
  int32_t packedUint32MemoizedSerializedSize;
  NSMutableArray* mutablePackedEnumList;
  int32_t packedEnumMemoizedSerializedSize;
  NSMutableArray* mutablePackedSfixed32List;
  int32_t packedSfixed32MemoizedSerializedSize;
  NSMutableArray* mutablePackedSfixed64List;
  int32_t packedSfixed64MemoizedSerializedSize;
  NSMutableArray* mutablePackedSint32List;
  int32_t packedSint32MemoizedSerializedSize;
  NSMutableArray* mutablePackedSint64List;
  int32_t packedSint64MemoizedSerializedSize;
}
- (NSArray*) packedInt32List;
- (int32_t) packedInt32AtIndex:(int32_t) index;
- (NSArray*) packedInt64List;
- (int64_t) packedInt64AtIndex:(int32_t) index;
- (NSArray*) packedUint32List;
- (int32_t) packedUint32AtIndex:(int32_t) index;
- (NSArray*) packedUint64List;
- (int64_t) packedUint64AtIndex:(int32_t) index;
- (NSArray*) packedSint32List;
- (int32_t) packedSint32AtIndex:(int32_t) index;
- (NSArray*) packedSint64List;
- (int64_t) packedSint64AtIndex:(int32_t) index;
- (NSArray*) packedFixed32List;
- (int32_t) packedFixed32AtIndex:(int32_t) index;
- (NSArray*) packedFixed64List;
- (int64_t) packedFixed64AtIndex:(int32_t) index;
- (NSArray*) packedSfixed32List;
- (int32_t) packedSfixed32AtIndex:(int32_t) index;
- (NSArray*) packedSfixed64List;
- (int64_t) packedSfixed64AtIndex:(int32_t) index;
- (NSArray*) packedFloatList;
- (Float32) packedFloatAtIndex:(int32_t) index;
- (NSArray*) packedDoubleList;
- (Float64) packedDoubleAtIndex:(int32_t) index;
- (NSArray*) packedBoolList;
- (BOOL) packedBoolAtIndex:(int32_t) index;
- (NSArray*) packedEnumList;
- (ForeignEnum) packedEnumAtIndex:(int32_t) index;

+ (TestPackedTypes*) defaultInstance;
- (TestPackedTypes*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestPackedTypes_Builder*) builder;
+ (TestPackedTypes_Builder*) builder;
+ (TestPackedTypes_Builder*) builderWithPrototype:(TestPackedTypes*) prototype;

+ (TestPackedTypes*) parseFromData:(NSData*) data;
+ (TestPackedTypes*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestPackedTypes*) parseFromInputStream:(NSInputStream*) input;
+ (TestPackedTypes*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestPackedTypes*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestPackedTypes*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestPackedTypes_Builder : PBGeneratedMessage_Builder {
@private
  TestPackedTypes* result;
}

- (TestPackedTypes*) defaultInstance;

- (TestPackedTypes_Builder*) clear;
- (TestPackedTypes_Builder*) clone;

- (TestPackedTypes*) build;
- (TestPackedTypes*) buildPartial;

- (TestPackedTypes_Builder*) mergeFrom:(TestPackedTypes*) other;
- (TestPackedTypes_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestPackedTypes_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;

- (NSArray*) packedInt32List;
- (int32_t) packedInt32AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedInt32AtIndex:(int32_t) index with:(int32_t) value;
- (TestPackedTypes_Builder*) addPackedInt32:(int32_t) value;
- (TestPackedTypes_Builder*) addAllPackedInt32:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedInt32List;

- (NSArray*) packedInt64List;
- (int64_t) packedInt64AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedInt64AtIndex:(int32_t) index with:(int64_t) value;
- (TestPackedTypes_Builder*) addPackedInt64:(int64_t) value;
- (TestPackedTypes_Builder*) addAllPackedInt64:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedInt64List;

- (NSArray*) packedUint32List;
- (int32_t) packedUint32AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedUint32AtIndex:(int32_t) index with:(int32_t) value;
- (TestPackedTypes_Builder*) addPackedUint32:(int32_t) value;
- (TestPackedTypes_Builder*) addAllPackedUint32:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedUint32List;

- (NSArray*) packedUint64List;
- (int64_t) packedUint64AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedUint64AtIndex:(int32_t) index with:(int64_t) value;
- (TestPackedTypes_Builder*) addPackedUint64:(int64_t) value;
- (TestPackedTypes_Builder*) addAllPackedUint64:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedUint64List;

- (NSArray*) packedSint32List;
- (int32_t) packedSint32AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedSint32AtIndex:(int32_t) index with:(int32_t) value;
- (TestPackedTypes_Builder*) addPackedSint32:(int32_t) value;
- (TestPackedTypes_Builder*) addAllPackedSint32:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedSint32List;

- (NSArray*) packedSint64List;
- (int64_t) packedSint64AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedSint64AtIndex:(int32_t) index with:(int64_t) value;
- (TestPackedTypes_Builder*) addPackedSint64:(int64_t) value;
- (TestPackedTypes_Builder*) addAllPackedSint64:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedSint64List;

- (NSArray*) packedFixed32List;
- (int32_t) packedFixed32AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedFixed32AtIndex:(int32_t) index with:(int32_t) value;
- (TestPackedTypes_Builder*) addPackedFixed32:(int32_t) value;
- (TestPackedTypes_Builder*) addAllPackedFixed32:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedFixed32List;

- (NSArray*) packedFixed64List;
- (int64_t) packedFixed64AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedFixed64AtIndex:(int32_t) index with:(int64_t) value;
- (TestPackedTypes_Builder*) addPackedFixed64:(int64_t) value;
- (TestPackedTypes_Builder*) addAllPackedFixed64:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedFixed64List;

- (NSArray*) packedSfixed32List;
- (int32_t) packedSfixed32AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedSfixed32AtIndex:(int32_t) index with:(int32_t) value;
- (TestPackedTypes_Builder*) addPackedSfixed32:(int32_t) value;
- (TestPackedTypes_Builder*) addAllPackedSfixed32:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedSfixed32List;

- (NSArray*) packedSfixed64List;
- (int64_t) packedSfixed64AtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedSfixed64AtIndex:(int32_t) index with:(int64_t) value;
- (TestPackedTypes_Builder*) addPackedSfixed64:(int64_t) value;
- (TestPackedTypes_Builder*) addAllPackedSfixed64:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedSfixed64List;

- (NSArray*) packedFloatList;
- (Float32) packedFloatAtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedFloatAtIndex:(int32_t) index with:(Float32) value;
- (TestPackedTypes_Builder*) addPackedFloat:(Float32) value;
- (TestPackedTypes_Builder*) addAllPackedFloat:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedFloatList;

- (NSArray*) packedDoubleList;
- (Float64) packedDoubleAtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedDoubleAtIndex:(int32_t) index with:(Float64) value;
- (TestPackedTypes_Builder*) addPackedDouble:(Float64) value;
- (TestPackedTypes_Builder*) addAllPackedDouble:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedDoubleList;

- (NSArray*) packedBoolList;
- (BOOL) packedBoolAtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedBoolAtIndex:(int32_t) index with:(BOOL) value;
- (TestPackedTypes_Builder*) addPackedBool:(BOOL) value;
- (TestPackedTypes_Builder*) addAllPackedBool:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedBoolList;

- (NSArray*) packedEnumList;
- (ForeignEnum) packedEnumAtIndex:(int32_t) index;
- (TestPackedTypes_Builder*) replacePackedEnumAtIndex:(int32_t) index with:(ForeignEnum) value;
- (TestPackedTypes_Builder*) addPackedEnum:(ForeignEnum) value;
- (TestPackedTypes_Builder*) addAllPackedEnum:(NSArray*) values;
- (TestPackedTypes_Builder*) clearPackedEnumList;
@end

@interface TestPackedExtensions : PBExtendableMessage {
@private
}

+ (TestPackedExtensions*) defaultInstance;
- (TestPackedExtensions*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (TestPackedExtensions_Builder*) builder;
+ (TestPackedExtensions_Builder*) builder;
+ (TestPackedExtensions_Builder*) builderWithPrototype:(TestPackedExtensions*) prototype;

+ (TestPackedExtensions*) parseFromData:(NSData*) data;
+ (TestPackedExtensions*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestPackedExtensions*) parseFromInputStream:(NSInputStream*) input;
+ (TestPackedExtensions*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (TestPackedExtensions*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (TestPackedExtensions*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface TestPackedExtensions_Builder : PBExtendableMessage_Builder {
@private
  TestPackedExtensions* result;
}

- (TestPackedExtensions*) defaultInstance;

- (TestPackedExtensions_Builder*) clear;
- (TestPackedExtensions_Builder*) clone;

- (TestPackedExtensions*) build;
- (TestPackedExtensions*) buildPartial;

- (TestPackedExtensions_Builder*) mergeFrom:(TestPackedExtensions*) other;
- (TestPackedExtensions_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (TestPackedExtensions_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface FooRequest : PBGeneratedMessage {
@private
}

+ (FooRequest*) defaultInstance;
- (FooRequest*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (FooRequest_Builder*) builder;
+ (FooRequest_Builder*) builder;
+ (FooRequest_Builder*) builderWithPrototype:(FooRequest*) prototype;

+ (FooRequest*) parseFromData:(NSData*) data;
+ (FooRequest*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (FooRequest*) parseFromInputStream:(NSInputStream*) input;
+ (FooRequest*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (FooRequest*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (FooRequest*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface FooRequest_Builder : PBGeneratedMessage_Builder {
@private
  FooRequest* result;
}

- (FooRequest*) defaultInstance;

- (FooRequest_Builder*) clear;
- (FooRequest_Builder*) clone;

- (FooRequest*) build;
- (FooRequest*) buildPartial;

- (FooRequest_Builder*) mergeFrom:(FooRequest*) other;
- (FooRequest_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (FooRequest_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface FooResponse : PBGeneratedMessage {
@private
}

+ (FooResponse*) defaultInstance;
- (FooResponse*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (FooResponse_Builder*) builder;
+ (FooResponse_Builder*) builder;
+ (FooResponse_Builder*) builderWithPrototype:(FooResponse*) prototype;

+ (FooResponse*) parseFromData:(NSData*) data;
+ (FooResponse*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (FooResponse*) parseFromInputStream:(NSInputStream*) input;
+ (FooResponse*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (FooResponse*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (FooResponse*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface FooResponse_Builder : PBGeneratedMessage_Builder {
@private
  FooResponse* result;
}

- (FooResponse*) defaultInstance;

- (FooResponse_Builder*) clear;
- (FooResponse_Builder*) clone;

- (FooResponse*) build;
- (FooResponse*) buildPartial;

- (FooResponse_Builder*) mergeFrom:(FooResponse*) other;
- (FooResponse_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (FooResponse_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface BarRequest : PBGeneratedMessage {
@private
}

+ (BarRequest*) defaultInstance;
- (BarRequest*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (BarRequest_Builder*) builder;
+ (BarRequest_Builder*) builder;
+ (BarRequest_Builder*) builderWithPrototype:(BarRequest*) prototype;

+ (BarRequest*) parseFromData:(NSData*) data;
+ (BarRequest*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (BarRequest*) parseFromInputStream:(NSInputStream*) input;
+ (BarRequest*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (BarRequest*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (BarRequest*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface BarRequest_Builder : PBGeneratedMessage_Builder {
@private
  BarRequest* result;
}

- (BarRequest*) defaultInstance;

- (BarRequest_Builder*) clear;
- (BarRequest_Builder*) clone;

- (BarRequest*) build;
- (BarRequest*) buildPartial;

- (BarRequest_Builder*) mergeFrom:(BarRequest*) other;
- (BarRequest_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (BarRequest_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface BarResponse : PBGeneratedMessage {
@private
}

+ (BarResponse*) defaultInstance;
- (BarResponse*) defaultInstance;

- (BOOL) isInitialized;
- (void) writeToCodedOutputStream:(PBCodedOutputStream*) output;
- (BarResponse_Builder*) builder;
+ (BarResponse_Builder*) builder;
+ (BarResponse_Builder*) builderWithPrototype:(BarResponse*) prototype;

+ (BarResponse*) parseFromData:(NSData*) data;
+ (BarResponse*) parseFromData:(NSData*) data extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (BarResponse*) parseFromInputStream:(NSInputStream*) input;
+ (BarResponse*) parseFromInputStream:(NSInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
+ (BarResponse*) parseFromCodedInputStream:(PBCodedInputStream*) input;
+ (BarResponse*) parseFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end

@interface BarResponse_Builder : PBGeneratedMessage_Builder {
@private
  BarResponse* result;
}

- (BarResponse*) defaultInstance;

- (BarResponse_Builder*) clear;
- (BarResponse_Builder*) clone;

- (BarResponse*) build;
- (BarResponse*) buildPartial;

- (BarResponse_Builder*) mergeFrom:(BarResponse*) other;
- (BarResponse_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input;
- (BarResponse_Builder*) mergeFromCodedInputStream:(PBCodedInputStream*) input extensionRegistry:(PBExtensionRegistry*) extensionRegistry;
@end
