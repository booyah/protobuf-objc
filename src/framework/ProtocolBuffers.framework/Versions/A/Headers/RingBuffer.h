#import <Foundation/Foundation.h>

@interface RingBuffer : NSObject {
	NSMutableData *buffer;
	NSInteger position;
	NSInteger tail;
}
@property (nonatomic, readonly) NSUInteger freeSpace;

- (id)initWithData:(NSMutableData*)data;

// Returns false if there is not enough free space in buffer
- (BOOL)appendByte:(uint8_t)byte;

// Returns number of bytes written
- (NSInteger)appendData:(const NSData*)value offset:(NSInteger)offset length:(NSInteger)length;

// Returns number of bytes written
- (NSInteger)flushToOutputStream:(NSOutputStream*)stream;

@end
