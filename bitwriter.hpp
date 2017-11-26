#ifndef _bitwriter_hpp
#define _bitwriter_hpp
#include <stdint.h>	//uint8_t, uint16_t
#include <cstdlib>	//malloc(), free()
#include <iostream>

class bitwriter {
private:
	uint8_t* buffer;
	int buffersize;
	uint16_t scratch;
	int scratchbits;
	int bufferedbytes;
	
	
public:
	
	enum {isWriting = 1};
	enum {isReading = 0};
	
	bitwriter(int buffsize);
	~bitwriter();
	
	bool writebits(void* v, unsigned int bits);
	
	unsigned int size();
	
	unsigned int bits();
	
	void getdata(void* buff);
	
};

#endif

