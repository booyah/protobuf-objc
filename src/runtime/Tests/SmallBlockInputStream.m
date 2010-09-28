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

#import "SmallBlockInputStream.h"


@implementation SmallBlockInputStream

@synthesize underlyingStream;

- (void) dealloc {
  self.underlyingStream = nil;
  [super dealloc];
}


- (id) initWithData:(NSData*) data_
          blockSize:(int32_t) blockSize_ {
  if ((self = [super init])) {
    self.underlyingStream = [NSInputStream inputStreamWithData:data_];
    blockSize = blockSize_;
  }

  return self;
}


+ (SmallBlockInputStream*) streamWithData:(NSData*) data
                                blockSize:(int32_t) blockSize {
  return [[[SmallBlockInputStream alloc] initWithData:data
                                            blockSize:blockSize] autorelease];
}

- (void)open {
  [underlyingStream open];
}


- (void) close {
  [underlyingStream close];
}


- (NSInteger) read:(uint8_t*) buffer
         maxLength:(NSUInteger) len {
  return [underlyingStream read:buffer maxLength:MIN(len, blockSize)];
}


- (BOOL) getBuffer:(uint8_t**) buffer length:(NSUInteger*)len {
  return [underlyingStream getBuffer:buffer length:len];
}


- (BOOL) hasBytesAvailable {
  return underlyingStream.hasBytesAvailable;
}

@end
