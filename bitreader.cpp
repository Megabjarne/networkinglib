#include "bitreader.hpp"

/*
class bitreader {
private:
	uint8_t* buffer;
	int buffersize;
	uint16_t scratch;
	int scratchbits;
	int bufferpos;
*/

bitreader::bitreader(uint8_t *buff, int buffsize){
	buffer = buff;
	buffersize = buffsize;
	scratch = 0;
	scratchbits = 0;
	bufferpos = 0;
}

bool bitreader::readbits(void* v, unsigned int bits){
	uint8_t *p = (uint8_t*)v;
	
	if (bits > 8){
		int n=0;
		while (n*8 < bits){
			if (!this->readbits( p+n, ((bits - n*8) > 8)? 8 : (bits - n*8) ))
				return false;
			n++;
		}
	} else {
		if (scratchbits<bits){
			scratch |= (buffer[bufferpos] << scratchbits);
			bufferpos++;
			scratchbits += 8;
		}
		uint8_t mask = ~((uint8_t)0);
		mask >>= (8-bits);
		p[0] = scratch & mask;
		scratch >>= bits;
		scratchbits -= bits;
	}
	return true;
}

