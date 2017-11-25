
CFLAGS = -g -O0

build: bitwriter.o bitreader.o
	g++ bitwriter.o bitreader.o main.cpp $(CFLAGS)

bitwriter.o: bitwriter.cpp bitwriter.hpp
	g++ bitwriter.cpp -c $(CFLAGS)

bitreader.o: bitreader.cpp bitreader.hpp
	g++ bitreader.cpp -c $(CFLAGS)

