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

#import "PBFieldDescriptor+Internal.h"

#import "Descriptor.pb.h"
#import "PBDescriptor.h"
#import "PBDescriptorPool+Internal.h"
#import "PBEnumDescriptor.h"
#import "PBExceptions.h"
#import "PBFileDescriptor.h"

@implementation PBFieldDescriptor (PBFieldDescriptorCreation)

- (id)initWithProto:(PBFieldDescriptorProto *)proto
			   file:(PBFileDescriptor *)file
			 parent:(PBDescriptor *)parent
			  index:(NSInteger)index
	    isExtension:(BOOL)isExtension
{
	if (self = [super init])
	{
		_index = index;
		_proto = [proto retain];
		_file = [file retain];

		_fullName = [PBComputeFullName(file, parent, proto.name) retain];
		
		if ([proto hasType])
		{
			// TODO: Check how the values line up with our enum in PBTypes.h
			_type = _proto.type;
		}
		
		if (self.number <= 0)
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"Field numbers must be positive integers."];
		}
		
		// Only repeated primitive fields may be packed.
		if (proto.options.packed && !self.packable)
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"[packed = true] can only be specified for repeated primitive fields."];
		}
		
		if (self.extension)
		{
			if (![proto hasExtendee])
			{
				[NSException raise:PBInvalidDescriptorException
							format:@"FieldDescriptorProto.extendee not set for extension field."];
			}

			_containingType = nil;
			_extensionScope = (parent) ? [parent retain] : nil;
		}
		else
		{
			if ([proto hasExtendee])
			{
				[NSException raise:PBInvalidDescriptorException
							format:@"FieldDescriptorProto.extendee set for non-extension field."];
			}
			
			_containingType = [parent retain];
			_extensionScope = nil;
		}

		[file.pool addSymbol:self];
	}

	return self;
}

- (void)crossLink
{
	if ([_proto hasExtendee])
	{
		id<PBGenericDescriptor> extendee = [_file.pool descriptorNamed:_proto.extendee relativeTo:self];
		if (![extendee isKindOfClass:[PBDescriptor class]])
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"'%@' is not a message type.", _proto.extendee];
		}
		
		self.containingType = extendee;
		
		if (![_containingType isExtensionNumber:self.number])
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"'%@' does not declare %d as an extension number.",
							_containingType.fullName, self.number];
		}
	}
	
	if ([_proto hasTypeName])
	{
		id<PBGenericDescriptor> typeDescriptor = [_file.pool descriptorNamed:_proto.typeName relativeTo:self];

		if (![_proto hasType])
		{
			if ([typeDescriptor isKindOfClass:[PBDescriptor class]])
			{
				_type = PBTypeMessage;
			}
			else if ([typeDescriptor isKindOfClass:[PBEnumDescriptor class]])
			{
				_type = PBTypeEnum;
			}
			else
			{
				[NSException raise:PBInvalidDescriptorException
							format:@"'%@' is not a type.", _proto.typeName];
			}
		}

		if (self.nativeType == PBObjCTypeMessage)
		{
			if (![typeDescriptor isKindOfClass:[PBDescriptor class]])
			{
				[NSException raise:PBInvalidDescriptorException format:@"'%@' is not a message type.", _proto.typeName];
			}

			self.messageType = typeDescriptor;
			
			if ([_proto hasDefaultValue])
			{
				[NSException raise:PBInvalidDescriptorException format:@"Messages cannot have default values."];
			}
		}
		else if (self.nativeType == PBObjCTypeEnum)
		{
			if (![typeDescriptor isKindOfClass:[PBEnumDescriptor class]])
			{
				[NSException raise:PBInvalidDescriptorException format:@"'%@' is not an enum type.", _proto.typeName];
			}

			self.enumType = typeDescriptor;
		}
		else
		{
			[NSException raise:PBInvalidDescriptorException format:@"Field with primitive type has type_name."];
		}
	}
	else
	{
		if (self.nativeType == PBObjCTypeMessage || self.nativeType == PBObjCTypeEnum)
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"Field with message or enum type is missing type_enum."];
		}
	}
	
	// We don't attempt to parse the default value until this point because,
	// for enums, we first need the enum type's descriptor.
	if ([_proto hasDefaultValue])
	{
		if (self.repeated)
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"Repeated fields cannot have default values."];
		}
		
		// TODO: Parse and assign the default value.
	}
	else
	{
		if (self.repeated)
		{
			self.defaultValue = [[NSArray alloc] init];
		}
		else
		{
			switch (self.nativeType)
			{
				case PBObjCTypeEnum:
					// Enums always have at least one value.
					self.defaultValue = [self.enumType.values objectAtIndex:0];
					break;
					
				case PBObjCTypeMessage:
					self.defaultValue = nil;
					break;
					
				default:
					self.defaultValue = PBDefaultValue(self.nativeType);
					break;
			}
		}
	}
	
	if (!self.extension)
	{
		// TODO: Add field by number.
		[_file.pool addField:self];
	}
	
	if (self.containingType && self.containingType.options.messageSetWireFormat)
	{
		if (self.extension)
		{
			if (!self.optional || self.type != PBTypeMessage)
			{
				[NSException raise:PBInvalidDescriptorException
							format:@"Extensions of MessageSets must be optional messages."];
			}
		}
		else
		{
			[NSException raise:PBInvalidDescriptorException
						format:@"MessageSets cannot have fields, only extensions."];
		}
	}
}

@end