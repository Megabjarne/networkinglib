#ifndef _bitreader_hpp
#define _bitreader_hpp
#include <stdint.h>	//uint8_t, uint16_t

class bitreader {
private:
	uint8_t* buffer;
	int buffersize;
	uint16_t scratch;
	int scratchbits;
	int bufferpos;
	
public:
	enum {isWriting = 0};
	enum {isReading = 1};
	
	bitreader(uint8_t *buff, int buffsize);
	
	bool readbits(void* v, unsigned int bits);
	
};

#endif

