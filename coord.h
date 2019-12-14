#include <string>
#include <iostream>

using namespace std;

class Coord
{
private:
	int8_t letter1; //attribut des 2 lettres donnant la position
	int8_t letter2;
	int** matrice; //fichier donnant la matrice BLOSUM

public:
	Coord(int8_t letter1, int8_t letter2, int** arg); //constructeur
	int coord_conversionX(); //convertisseur
	int coord_conversionY();
	int score();
};
