#include <iostream>
#include "bitwriter.hpp"
#include "bitreader.hpp"
#include <stdint.h>

int main(){
	
	bitwriter writer(64);
	
	uint32_t t = 213;
	uint32_t k = 23589702;
	uint32_t p = 1234879;
	
	
	writer.writebits(&t, 9);
	writer.writebits(&k, 25);
	writer.writebits(&p, 30);
	
	uint8_t buff[16];
	writer.getdata(buff);
	
	bitreader reader(buff, 5);
	
	uint32_t t2=0, k2=0, p2=0;
	
	reader.readbits(&t2, 9);
	reader.readbits(&k2, 25);
	reader.readbits(&p2, 30);
	
	std::cout<<t<<" "<<k<<" "<<p<<"\n";
	
	std::cout<<t2<<" "<<k2<<" "<<p2<<"\n";
	
	return 0;
}

