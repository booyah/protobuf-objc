#import <Foundation/Foundation.h>

@interface RingBuffer : NSObject {
	NSMutableData *buffer;
	long position;
	long tail;
}
@property (nonatomic, readonly) unsigned long freeSpace;

- (id)initWithData:(NSMutableData*)data;

// Returns false if there is not enough free space in buffer
- (BOOL)appendByte:(uint8_t)byte;

// Returns number of bytes written
- (long)appendData:(const NSData*)value offset:(long)offset length:(long)length;

// Returns number of bytes written
- (long)flushToOutputStream:(NSOutputStream*)stream;

@end
