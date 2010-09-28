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
  STAssertEquals(4, (int)sizeof(int), nil);	
  #ifdef __x86_64__	
    STAssertEquals(8, (int)sizeof(long), nil);
  #else
    STAssertEquals(4, (int)sizeof(long), nil);
  #endif
  STAssertEquals(8, (int)sizeof(long long), nil);
  STAssertEquals(4, (int)sizeof(int32_t), nil);
  STAssertEquals(8, (int)sizeof(int64_t), nil);
  STAssertEquals(4, (int)sizeof(Float32), nil);
  STAssertEquals(8, (int)sizeof(Float64), nil);
  STAssertEquals(0, !!0, nil);
  STAssertEquals(1, !!1, nil);
  STAssertEquals(1, !!2, nil);
}

@end
