#include <string>
#include <iostream>
using namespace std;

class Matrice
{
private:
	string matrice_file; //fichier donnant la matrice BLOSUM
	
public:
	Matrice(string matrice_file); //constructeur
	int** matrice_score();
};
