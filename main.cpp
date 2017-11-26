#include <iostream>
#include "bitwriter.hpp"
#include "bitreader.hpp"
#include <stdint.h>
#include "serialize.hpp"


int main(){
	
	bitwriter writer(64);
	
	int32_t t = 1234;
	int32_t k = -4321;
	int32_t p = 87923;
	char s[] = "hello to you there";
	float o = 911.31415;
	
	/*
	writer.writebits(&t, 9);
	writer.writebits(&k, 25);
	writer.writebits(&p, 30);
	*/
	
	serialize_int<0,2000>(writer, t);
	serialize_int<-5000,5000>(writer, k);
	serialize_int<500,100000>(writer, p);
	serialize_array<64>(writer, s, sizeof(s));
	serialize_float(writer, o);
	serialize_float<-1000, 1000, 1000>(writer, o);
	
	uint8_t buff[64];
	writer.getdata(buff);
	
	bitreader reader(buff, 32);
	
	int32_t t2=0, k2=0, p2=0, len=0;
	char s2[128];
	float o1, o2;
	
	serialize_int<0,2000>(reader, t2);
	serialize_int<-5000,5000>(reader, k2);
	serialize_int<500,100000>(reader, p2);
	serialize_array<64>(reader, s2);
	serialize_float(reader, o1);
	serialize_float<-1000, 1000, 1000>(reader, o2);
	
	std::cout<<writer.bits()<<" b\n";
	std::cout<<t<<" "<<k<<" "<<p<<"\n";
	std::cout<<t2<<" "<<k2<<" "<<p2<<"\n";
	std::cout<<s<<"\n";
	std::cout<<s2<<"\n";
	std::cout<<o<<" "<<o1<<" "<<o2<<"\n";
	
	return 0;
}

