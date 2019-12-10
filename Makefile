all: letter.o coord.o algo.o match.cpp
	g++ -o match match.cpp letter.o coord.o algo.o -O3

##letter: coord.o algo.o letter.o match.o$
	##g++ -c match coord.o algo.o letter.o match.o
letter.o: letter.cpp
	g++ -c letter.cpp

algo.o: algo.cpp
	g++ -c algo.cpp

coord.o: coord.cpp
	g++ -c coord.cpp

##match: match.cpp letter.o coord.o algo.o
	##g++ -O3 -o match match.cpp letter.o coord.o algo.o


