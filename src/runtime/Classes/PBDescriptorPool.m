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

#import "PBDescriptorPool+Internal.h"

#import "PBDescriptor.h"
#import "PBEnumDescriptor.h"
#import "PBExceptions.h"
#import "PBFieldDescriptor.h"
#import "PBFileDescriptor.h"
#import "PBGenericDescriptor.h"

// Represents a package in the symbol table.
@interface PBPackageDescriptor : NSObject <PBGenericDescriptor>
{
@private
	NSString *			_name;
	NSString *			_fullName;
	PBFileDescriptor *	_file;
}

@property (nonatomic,retain,readonly)	PBGeneratedMessage *	proto;
@property (nonatomic,retain)			NSString *				name;
@property (nonatomic,retain)			NSString *				fullName;
@property (nonatomic,retain)			PBFileDescriptor *		file;

@end

@implementation PBPackageDescriptor

@dynamic proto;
@synthesize name = _name;
@synthesize fullName = _fullName;
@synthesize file = _file;

- (void)dealloc
{
	[_name release];
	[_fullName release];
	[_file release];
	[super dealloc];
}

- (PBGeneratedMessage *)getProto
{
	return (PBGeneratedMessage *)_file.proto;
}

@end

#pragma mark -

@implementation PBDescriptorPool

@synthesize fields = _fields;
@synthesize enumValues = _enumValues;

- (void)dealloc
{
	[_dependencies release];
	[_descriptors release];
	[_fields release];
	[_enumValues release];
	[super dealloc];
}

+ (NSException *)exceptionWithDescriptor:(id<PBGenericDescriptor>)descriptor andReason:(NSString *)reason
{
	return [NSException exceptionWithName:PBInvalidDescriptorException
								   reason:reason
								 userInfo:[NSDictionary dictionaryWithObject:descriptor
																	  forKey:@"descriptor"]];
}

+ (void)validateSymbol:(id<PBGenericDescriptor>)descriptor
{
	const char *p = [descriptor.name UTF8String];
	if (!p || !*p)
	{
		@throw [PBDescriptorPool exceptionWithDescriptor:descriptor andReason:@"Missing name."];
	}

	// The first character must be a letter, digit, or underscore (_).
	BOOL valid = isalnum(*p) || (*p == '_');

	// All characters must be ASCII and letters or digits.
	for (; *p && valid; p++)
	{
		const unsigned char c = *p;
		if (c >= 128 || !isalnum(c))
		{
			valid = NO;
		}
	}

	if (!valid)
	{
		NSString *reason = [NSString stringWithFormat:@"'%@' is not a valid identifier", descriptor.name];
		@throw [PBDescriptorPool exceptionWithDescriptor:descriptor andReason:reason];
	}
}

- (void)addSymbol:(id<PBGenericDescriptor>)descriptor
{
	[PBDescriptorPool validateSymbol:descriptor];

	NSString * const fullName = descriptor.fullName;
	const NSRange dot = [fullName rangeOfString:@"."];
	
	id<PBGenericDescriptor> old = [_descriptors objectForKey:fullName];
	if (old)
	{
		NSString *reason;

		// TODO: Correct to compare these objects using isEqual?
		if (![descriptor.file isEqual:old.file])
		{
			reason = [NSString stringWithFormat:@"'%@' is already defined in file '%@'.",
					  fullName, old.file.name];
		}
		else if (dot.length > 0)
		{
			reason = [NSString stringWithFormat:@"'%@' is already defined in file '%@'.",
					  [fullName substringToIndex:dot.location + 1], old.file.name];
		}
		else
		{
			reason = [NSString stringWithFormat:@"'%@' is already defined", fullName];
		}

		@throw [PBDescriptorPool exceptionWithDescriptor:descriptor andReason:reason];
	}
}

- (void)addPackage:(PBFileDescriptor *)file withName:(NSString *)fullName
{
	NSString *name = fullName;

	// If our package has multiple components, add the parents, too.
	NSRange dot = [fullName rangeOfString:@"."];
	if (dot.length > 0)
	{
		[self addPackage:file withName:[fullName substringToIndex:dot.location]];
		name = [fullName substringFromIndex:dot.location + 1];
	}

	// Add the package to the symbol table.  If a package of the same name
	// already exists, we're good, but if a non-package has been registered
	// using our name, we throw an example.
	id<PBGenericDescriptor> old = [_descriptors objectForKey:name];
	if (old == nil)
	{
		PBPackageDescriptor *package = [[PBPackageDescriptor alloc] init];
		if (package)
		{
			package.name = name;
			package.fullName = fullName;
			package.file = file;
			[_descriptors setObject:package forKey:fullName];
			[package release];
		}
	}
	else if (![old isKindOfClass:[PBPackageDescriptor class]])
	{
		[NSException raise:PBInvalidDescriptorException
					format:@"'%@' is already defined (as something other than a package) in file '%@'.",
						name, old.file.name];
	}
}

- (void)addField:(PBFieldDescriptor *)field
{
	PBDescriptorPoolCompositeKey *key = [[PBDescriptorPoolCompositeKey alloc]
										 initWithDescriptor:field.containingType andNumber:field.number];
	if (key)
	{
		// Add the field to the table using our custom key.  If a field with the
		// same containing type and number already exists, we throw an exception.
		id<PBGenericDescriptor> old = [_fields objectForKey:key];
		if (old == nil)
		{
			[_fields setObject:field forKey:key];
		}
		else
		{
			NSString *reason = [NSString stringWithFormat:
								@"Field number %d has already been used in '%@' by field '%@'.",
								field.number, field.containingType.fullName, old.name];

			@throw [PBDescriptorPool exceptionWithDescriptor:field andReason:reason];
		}

		[key release];
	}
}

- (void)addEnumValue:(PBEnumValueDescriptor *)enumValue
{
	PBDescriptorPoolCompositeKey *key = [[PBDescriptorPoolCompositeKey alloc]
										 initWithDescriptor:enumValue.type andNumber:enumValue.number];
	if (key)
	{
		// If an existing value with the same type and number already exists,
		// we don't do anything.  This is permitted, and the first value takes
		// precedence.
		id<PBGenericDescriptor> old = [_enumValues objectForKey:key];
		if (old == nil)
		{
			[_enumValues setObject:enumValue forKey:key];
		}

		[key release];
	}
}

- (id<PBGenericDescriptor>)descriptorNamed:(NSString *)fullName
{
	// Look for the descriptor in our local map.
	id<PBGenericDescriptor> descriptor = [_descriptors objectForKey:fullName];
	if (descriptor != nil)
	{
		return descriptor;
	}

	// Also check all of our dependencies.
	for (PBDescriptorPool *pool in _dependencies)
	{
		descriptor = [pool descriptorNamed:fullName];
		if (descriptor != nil)
		{
			return descriptor;
		}
	}

	return nil;
}

- (id<PBGenericDescriptor>)descriptorNamed:(NSString *)fullName withType:(Class)type
{
	id<PBGenericDescriptor> descriptor = [self descriptorNamed:fullName];
	if ([descriptor isKindOfClass:type])
	{
		return descriptor;
	}

	return nil;
}

- (id<PBGenericDescriptor>)descriptorNamed:(NSString *)fullName relativeTo:(id<PBGenericDescriptor>)parent
{
	id<PBGenericDescriptor> descriptor = nil;

	if ([fullName hasPrefix:@"."])
	{
		descriptor = [self descriptorNamed:[fullName substringFromIndex:1]];
	}
	else
	{
		// If "name" is a compound identifier, search from the first component of it.
		NSRange firstDot = [fullName rangeOfString:@"."];
		NSString *firstPart = (firstDot.length == 0) ? fullName : [fullName substringToIndex:firstDot.location];
		
		// Search each parent scope looking for the symbol.
		NSMutableString *scope = [[NSMutableString alloc] initWithString:parent.fullName];

		for (;;)
		{
			const NSRange dot = [scope rangeOfString:@"."];
			if (dot.length == 0)
			{
				descriptor = [self descriptorNamed:fullName];
				break;
			}

			// TODO: Double-check this
			[scope deleteCharactersInRange:NSMakeRange(dot.location + 1, scope.length - dot.location - 1)];
			[scope appendString:firstPart];

			descriptor = [self descriptorNamed:scope];

			if (descriptor)
			{
				// We only found the first part of the symbol.  Now we need to
				// look for the whole thing.  If this fails, we don't want to
				// keep searching parent scopes.
				if (firstDot.length > 0)
				{
					[scope deleteCharactersInRange:NSMakeRange(dot.location + 1, scope.length - dot.location - 1)];
					[scope appendString:fullName];
					descriptor = [self descriptorNamed:scope];
				}
				break;
			}

			// TODO: Double check this
			[scope deleteCharactersInRange:NSMakeRange(dot.location, scope.length - dot.location)];
		}

		[scope release];
	}
	
	if (descriptor == nil)
	{
		NSString *reason = [NSString stringWithFormat:@"'%@' is not defined", fullName];
		@throw [PBDescriptorPool exceptionWithDescriptor:parent andReason:reason];
	}

	return descriptor;
}

@end

#pragma mark -

@implementation PBDescriptorPoolCompositeKey

- (id)initWithDescriptor:(id <PBGenericDescriptor>)descriptor andNumber:(NSInteger)number
{
	if (self = [super init])
	{
		_descriptor = [descriptor retain];
		_number = number;
	}
	
	return self;
}

- (void)dealloc
{
	[_descriptor release];
	[super dealloc];
}

- (id)copyWithZone:(NSZone *)zone
{
	PBDescriptorPoolCompositeKey *copy = [[PBDescriptorPoolCompositeKey allocWithZone:zone] init];
	copy->_descriptor = _descriptor;
	copy->_number = _number;
	return copy;
}

- (BOOL)isEqual:(id)anObject
{
	if (![anObject isKindOfClass:[PBDescriptorPoolCompositeKey class]])
	{
		return NO;
	}
	
	PBDescriptorPoolCompositeKey *other = (PBDescriptorPoolCompositeKey *)anObject;
	return [_descriptor isEqual:other->_descriptor] && (_number == other->_number);
}

- (NSUInteger)hash
{
	// TODO: Make sure PBGenericDescriptor implements -hash appropriately.
	return [_descriptor hash] * ((1 << 16) - 1) + _number;
}

@end