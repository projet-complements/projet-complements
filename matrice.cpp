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
	for(int i = 0; i < N; i++) {
		matrice[i] = new int[N];
		for(int j = 0; j < N; j++)
		    matrice[i][j] = -1;
	}
	string str="";
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
			cout << "test matrice2" << endl;
			int i;
			int chiffre;
			int coordX=-1;
			int coordY;
			string s;
			int neg = 0;
			int dec = 0;
			//avec l'hypothese que les nombres à 2 chiffres vont jusqu'à 29 max et sont tjs postiifs
			for(i=2; i<74; i++){ //les prochains éléments sont les valeurs à mettre dans la matrice, dans le fichier allant de élém 2 à 74 incluant les espaces, les signes et les chiffres
				if(str[i]==' '){
				}
				else if(str[i]=='-'){
					neg = 1;
				}
				else if(str[i]=='1' && str[i+1] != ' '){
					dec = 1;
				}
				else if(str[i]=='2' && str[i+1] != ' '){
					dec = 2;
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
						if(dec==1){ //avec l'hypothèse qu'on a que des nombres à 2 chiffres positifs
							chiffre = chiffre+10;
						}
						else if(dec==2){
							chiffre = chiffre+20;
						}
						else{
							chiffre = chiffre;
						}
					}
					coordX=coordX+1;
					cout << "coordX " << coordX << endl;
					coordY=j;	 //coord Y est la même que celle de la ligne
					cout << "coordY " << coordY << endl;
					matrice[coordX][coordY]=chiffre; //à la position (X,Y) de la matrice on place la valeur
					neg=0; //on reinitialise le neg à 0
					dec=0;
					cout << "chiffre" << matrice[coordX][coordY] << endl;
				}
			}
		}	
	}
	return matrice;
}
