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
#import "CoreTests.h"

@implementation CoreTests

- (void) testTypeSizes {
  STAssertEquals((size_t)4, sizeof(int), nil);
  #ifdef __x86_64__	
    STAssertEquals((size_t)8, sizeof(long), nil);
  #else
    STAssertEquals((size_t)4, sizeof(long), nil);
  #endif
  STAssertEquals((size_t)8, sizeof(long long), nil);
  STAssertEquals((size_t)4, sizeof(Float32), nil);
  STAssertEquals((size_t)8, sizeof(Float64), nil);
  STAssertEquals(0, !!0, nil);
  STAssertEquals(1, !!1, nil);
  STAssertEquals(1, !!2, nil);
}

@end
