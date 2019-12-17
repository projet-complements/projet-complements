#include <string>
#include <iostream>
using namespace std;

class Matrice
{
private:
	string matrice_file; //file giving the matrix BLOSUM
	
public:
	Matrice(string matrice_file);
	int** matrice_score();
};
