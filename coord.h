#include <string>
#include <iostream>

using namespace std;

class Coord
{
private:
	int8_t letter1; //argument of 2 letters giving the position
	int8_t letter2;
	int** matrice; //file giving the BLOSUM matrix

public:
	Coord(int8_t letter1, int8_t letter2, int** arg);
	int coord_conversionX();
	int coord_conversionY();
	int score();
};
