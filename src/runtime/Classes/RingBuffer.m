#import "RingBuffer.h"

@implementation RingBuffer

- (id)initWithData:(NSMutableData*)data {
  if ((self = [super init])) {
    buffer = [data retain];
  }
	return self;
}


- (unsigned long)freeSpace {
	return (position < tail ? tail - position : (buffer.length - position) + tail) - (tail ? 1 : 0);
}


- (BOOL)appendByte:(uint8_t)byte {
	if (self.freeSpace < 1) return NO;
	((uint8_t*)buffer.mutableBytes)[position++] = byte;
	return YES;
}


- (long)appendData:(const NSData*)value offset:(long)offset length:(long)length {
	long totalWritten = 0;
	const uint8_t *input = value.bytes;
	uint8_t *data = buffer.mutableBytes;
	
	if (position >= tail) {
		totalWritten = MIN(buffer.length - position, length);
		memcpy(data + position, input + offset, totalWritten);
		position += totalWritten;
		if (totalWritten == length) return length;
		length -= totalWritten;
		offset += totalWritten;
	}
	
	unsigned long freeSpace = self.freeSpace;
	if (!freeSpace) return totalWritten;
	
	if (position == buffer.length) {
		position = 0;
	}
	
	// position < tail
	long written = MIN(freeSpace, length);
	memcpy(data + position, input + offset, written);
	position += written;
	totalWritten += written;
	
	return totalWritten;
}


- (long)flushToOutputStream:(NSOutputStream*)stream {
	long totalWritten = 0;
	const uint8_t *data = buffer.bytes;
	
	if (tail > position) {
		long written = [stream write:data + tail maxLength:buffer.length - tail];
        if (written <= 0) return totalWritten;
        totalWritten += written;
		tail += written;
		if (tail == buffer.length) {
			tail = 0;
		}
	}

	if (tail < position) {
		long written = [stream write:data + tail maxLength:position - tail];
		if (written <= 0) return totalWritten;
		totalWritten += written;
		tail += written;
	}

    if (tail == position) {
        tail = position = 0;
    }

    if (position == buffer.length && tail > 0) {
        position = 0;
    }

    if (tail == buffer.length) {
        tail = 0;
    }
	
	return totalWritten;
}


- (void)dealloc {
	[buffer release];
	[super dealloc];
}

@end
