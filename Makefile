all: match

letter: letter.o match.o
	g++ -c match letter.o match.o

letter.o: letter.cpp
	g++ -c letter.cpp

match: match.cpp letter.o
	g++ -O3 -o match match.cpp letter.o
