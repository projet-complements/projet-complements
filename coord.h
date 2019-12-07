#include <string>
#include <iostream>
using namespace std;

class Coord
{
private:
	string letter1; //attribut des 2 lettres donnant la position
	string letter2;

public:
	Coord(string letter1, string letter2); //constructeur
	int coord_conversionX(); //convertisseur
	int coord_conversionY();
};
