
#import "NSObject+MKBlockTimer.h"


@implementation NSObject (MKBlockTimer)

+(void) logTime:(void (^)(void)) block withPrefix:(NSString*) prefixString {
	
	double a = CFAbsoluteTimeGetCurrent();
	block();
	double b = CFAbsoluteTimeGetCurrent();
	
	unsigned int m = ((b-a) * 1000.0f); // convert from seconds to milliseconds
	
    NSString *log = [NSString stringWithFormat:@"%@: %d ms", prefixString ? prefixString : @"Time taken", m ];
	NSLog(@"LOG TIMER: %@", log);
//    POP_ALERT(log);
}


-(void) logTimeMethod:(void (^)(void)) block withPrefix:(NSString*) prefixString {
	[NSObject logTime:block withPrefix:prefixString];
}
@end
