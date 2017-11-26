#ifndef _serialize_hpp
#define _serialize_hpp

//	LOG2 code from
//	https://gafferongames.com/post/reading_and_writing_packets/
template <uint32_t x> struct PopCount
{
    enum { a = x - ( ( x >> 1 ) & 0x55555555 ),
           b = ( ( ( a >> 2 ) & 0x33333333 ) + ( a & 0x33333333 ) ),
           c = ( ( ( b >> 4 ) + b ) & 0x0f0f0f0f ),
           d = c + ( c >> 8 ),
           e = d + ( d >> 16 ),
    result = e & 0x0000003f }; 
};

template <uint32_t x> struct Log2
{
    enum { a = x | ( x >> 1 ),
           b = a | ( a >> 2 ),
           c = b | ( b >> 4 ),
           d = c | ( c >> 8 ),
           e = d | ( d >> 16 ),
           f = e >> 1,
    result = PopCount<f>::result };
};

template <int64_t min, int64_t max> struct BitsRequired
{
    static const uint32_t result = 
        ( min == max ) ? 0 : ( Log2<uint32_t(max-min)>::result + 1 );
};

#define BITS_REQUIRED( min, max ) BitsRequired<min,max>::result

bool IS_BIG_ENDIAN(){uint16_t i=1<<8;return *(uint8_t*)&i;}

// COMPRESSED INT WRITE
template<int min, int max> bool serialize_int(bitwriter& stream, int32_t v){
	uint32_t _v = v-min;
	return stream.writebits( &_v , BITS_REQUIRED(min, max) );
}

// COMPRESSED INT READ
template<int min, int max> bool serialize_int(bitreader& stream, int32_t& v){
	v=0;
	bool res = stream.readbits(&v, BITS_REQUIRED(min,max));
	v+= res?min:0;
	return res;
}

//INT WRITE
bool serialize_int(bitwriter& stream, int32_t v){
	return stream.writebits(&v, 32);
}

//INT READ
bool serialize_int(bitreader& stream, int32_t& v){
	return stream.readbits(&v, 32);
}

// BYTE/STRING WRITE
template <int maxlength> bool serialize_array(bitwriter& stream, void* buffer, int length){
	bool res = true;
	res &= serialize_int<0, maxlength>(stream, length);
	res &= stream.writebits(buffer, length*8);
	return res;
}

// BYTE/STRING READ
template <int maxlength> bool serialize_array(bitreader& stream, void* buffer){
	bool res = true;
	int length;
	res &= serialize_int<0, maxlength>(stream, length);
	return stream.readbits(buffer, length*8);
}

// FLOAT WRITE
bool serialize_float(bitwriter& stream, float v){
	return serialize_int(stream, *(int32_t*)&v);
}

// FLOAT READ
bool serialize_float(bitreader& stream, float& v){
	return serialize_int(stream, *(int32_t*)&v);
}

// COMPRESSED FLOAT WRITE
template <int min, int max, int resolution>
bool serialize_float(bitwriter& stream, float v){
	v *= resolution;
	return serialize_int<min*resolution, max*resolution>(stream, (int32_t)v);
}

// COMPRESSED FLOAT READ
template <int min, int max, int resolution>
bool serialize_float(bitreader& stream, float& v){
	int32_t tv;
	bool res = true;
	res &= serialize_int<min*resolution, max*resolution>(stream, tv);
	v = tv;
	v /= resolution;
	return res;
}

#endif

