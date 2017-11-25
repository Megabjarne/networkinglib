/*#ifndef _bitwriter_hpp
#define _bitwriter_hpp
#include <stdint.h>

class bitwriter {
private:
	uint8_t* buffer;
	int buffersize;
	uint16_t scratch;
	int scratchbits;
	int bufferedwords;
	
	
public:*/

#include "bitwriter.hpp"

#define MIN(a, b) (( (a<b)?b:a ))
#define HEX(a) ((char)( (((a)>=10)?('A'+((a)-10)):('0'+(a))) ))

bitwriter::bitwriter(int buffsize){
	buffer = (uint8_t*) malloc( sizeof(uint8_t)*buffsize );
	buffersize = buffsize;
	scratch = 0;
	scratchbits = 0;
	bufferedbytes = 0;
}

bitwriter::~bitwriter(){
	free(buffer);
}

bool bitwriter::writebits(void* v, unsigned int bits){
	uint8_t *p = (uint8_t*)v;
	//Handle writes too big
	if (bits>8){
		int n=0;
		while (bits > 8*n){
			if ( !this->writebits( p + n, (bits-8*n>8)?8:(bits-8*n) ) )
				return false;
			n++;
		}
	} else {
		scratch |= ((uint16_t)( (*p) & (0xFF>>(8-bits)) ) )<<scratchbits;
		scratchbits += bits;
		if (scratchbits >= 8){
			buffer[bufferedbytes] = scratch & 0xFF ;
			scratch >>= 8;
			bufferedbytes++;
			scratchbits-=8;
		}
	}
	
	return true;
}

unsigned int bitwriter::size(){
	return bufferedbytes + (scratchbits>0)?1:0;
}

unsigned int bitwriter::bits(){
	return bufferedbytes*8 + scratchbits;
}

void bitwriter::getdata(void* buff){
	uint8_t *p = (uint8_t*)buff;
	for (int i=0;i<bufferedbytes;i++){
		p[i] = buffer[i];
	}
	if (scratchbits>0)
		p[bufferedbytes] = scratch & 0xFF;
}

