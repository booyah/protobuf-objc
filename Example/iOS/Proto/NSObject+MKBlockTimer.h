
#import <Foundation/Foundation.h>

@interface NSObject (MKBlockTimer)
+(void) logTime:(void (^)(void)) block withPrefix:(NSString*) prefixString;
-(void) logTimeMethod:(void (^)(void)) block withPrefix:(NSString*) prefixString;
@end
