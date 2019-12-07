#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include "coord.h"
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <sstream> 
using namespace std;


//prend comme argument la matrice par exemple BLOSUM62
int main(int argc, char *argv[])
{
	// verify that we have 2 arguments, the name of the program and the 1 file
	if (argc < 2) {
		printf("Error: need 1 arguments \n");
		return 1;
	}
	
	//open the txt file with the matrix
	ifstream matrice_file (argv[1]);
	if(!matrice_file.is_open())
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	
	int tailleX(24);
	int tailleY(24);
	int matrice[tailleX][tailleY];
	string str="";
	while(!matrice_file.eof())
	{
		int j;
		for(j=30; j>-1; j--){ //il y a 30 lignes dans le fichier, les coord Y vont de 23->0 lisant du haut vers le bas
		std::getline(matrice_file, str);
		if(str[0]=='#') //les lignes commencant par # sont ignorées
		{
			str.clear();
			cout << "test1" << endl;
		}
		else if(str[0]==' '){ //les lignes commencant par un blanc sont ignorées 
			str.clear();
			cout << "test2" << endl;
		}
		else{ //ligne commencant par autre chose donc normalement une lettre et puis les valeurs
			int i;
			int chiffre;
			int coordX=-1;
			int coordY;
			string s;
			int neg = 0;
				for(i=2; i<74; i++) //les prochains éléments sont les valeurs à mettre dans la matrice, dans le fichier allant de élém 2 à 74 incluant les espaces, les signes et les chiffres
					if(str[i]==' '){
					}
					else if(str[i]=='-'){
						neg = 1;
					}
					else{ //normalement on tombe sur un chiffre
						s = str[i];
						stringstream geek(s); //object from the class stringstream with the value of s
						if(neg==1){
							geek >> chiffre; //on ajoute le signe négatif si neg=1
							chiffre = -chiffre;
						}
						else{
							geek >> chiffre; //stream the object geek to integer chiffre
						}
						coordX=coordX+1;
						coordY=j;	 //coord Y est la même que celle de la ligne
						//cout << "coordX " << coordX << endl;
						//cout << "coordY " << coordY << endl;
						matrice[coordX][coordY]=chiffre; //à la position (X,Y) de la matrice on place la valeur
						//cout << "chiffre " << matrice[coordX][coordY] << endl;
						neg=0; //on reinitialise le neg à 0
					}
		}
		}
		break;
	}
	//cout << "position (4,23) " << matrice[4][23] << endl; //donne 0
	//cout << "position (0,0) " << matrice[0][0] << endl; //donne -4
	//cout << "position (2,3) " << matrice[2][3] << endl; //donne 3
	
	string s1 = "N";
	string s2 = "B";
	int score;
	//matrice[s1][s2];
	Coord* coord = new Coord(s1,s2);
	int coordX;
	coordX = coord->coord_conversionX();
	int coordY;
	coordY = coord->coord_conversionY();
	score = matrice[coordX][coordY];
	cout << "position (2,3) " << score << endl; //donne 3


	return 0;


}
