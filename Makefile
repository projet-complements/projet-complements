all: letter.o coord.o algo.o matrice.o index.o match.cpp
	g++ -o match match.cpp letter.o coord.o algo.o matrice.o index.o -O3


letter.o: letter.cpp
	g++ -c letter.cpp

algo.o: algo.cpp
	g++ -c algo.cpp

coord.o: coord.cpp
	g++ -c coord.cpp

matrice.o: matrice.cpp
	g++ -c matrice.cpp
	
index.o: index.cpp
	g++ -c index.cpp

clear:
	rm *.o
