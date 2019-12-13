#include "matrice.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <sstream> 
using namespace std;

Matrice::Matrice(string fichier){
	matrice_file=fichier;
}

int** Matrice::matrice_score(){
	//open the txt file with the matrix
	ifstream fichier(matrice_file);
	if(!fichier.is_open())
	{
		cout << "Impossible to open the file of the matrix" << endl;
		return 0;
	}
	const int N=24;
	int** matrice=new int*[N];; //d'abord on crée la matrice de substitution en lisant la matrice BLOSUM reçu en argument
	string str="";
	while(!fichier.eof())
	{
		int j;
		for(j=30; j>-1; j--){ //il y a 30 lignes dans le fichier, les coord Y vont de 23->0 lisant du haut vers le bas
		std::getline(fichier, str);
		if(str[0]=='#') //les lignes commencant par # sont ignorées
		{
			str.clear();
		}
		else if(str[0]==' '){ //les lignes commencant par un blanc sont ignorées 
			str.clear();
		}
		else{ //ligne commencant par autre chose donc normalement une lettre et puis les valeurs
			int i;
			int chiffre;
			int coordX=-1;
			int coordY;
			string s;
			int neg = 0;
				for(i=2; i<74; i++) //les prochains éléments sont les valeurs à mettre dans la matrice, dans le fichier allant de élém 2 à 74 incluant les espaces, les signes et les chiffres
				cout << "test matrice" << endl;
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
						matrice[coordX][coordY]=chiffre; //à la position (X,Y) de la matrice on place la valeur
						neg=0; //on reinitialise le neg à 0
					}
		}
		}
		break;
	}
	return matrice;
		
}
