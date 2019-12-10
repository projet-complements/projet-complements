all: letter.o coord.o algo.o match.cpp
	g++ -o match match.cpp letter.o coord.o algo.o -O3


letter.o: letter.cpp
	g++ -c letter.cpp

algo.o: algo.cpp
	g++ -c algo.cpp

coord.o: coord.cpp
	g++ -c coord.cpp

clear:
	rm *.o
