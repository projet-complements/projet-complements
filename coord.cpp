#include "coord.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <sstream> 
using namespace std;

 
Coord::Coord(int8_t coordX, int8_t coordY, string fichier){
	letter1=coordX;
	letter2=coordY;
	matrice_file=fichier;
}

int Coord::coord_conversionX(){
	//function returning the coordinate X associated to the letter given in parameter as an int8
	int coordX;
	if(letter1==1){
		coordX=0;
	}
	else if(letter1==16){
		coordX=1;
	}
	else if(letter1==13){
		coordX=2;
	}
	else if(letter1==4){
		coordX=3;
	}
	else if(letter1==3){
		coordX=4;
	}
	else if(letter1==15){
		coordX=5;
	}
	else if(letter1==5){
		coordX=6;
	}
	else if(letter1==7){
		coordX=7;
	}
	else if(letter1==8){
		coordX=8;
	}
	else if(letter1==9){
		coordX=9;
	}
	else if(letter1==11){
		coordX=10;
	}
	else if(letter1==10){
		coordX=11;
	}
	else if(letter1==12){
		coordX=12;
	}
	else if(letter1==6){
		coordX=13;
	}
	else if(letter1==14){
		coordX=14;
	}
	else if(letter1==17){
		coordX=15;
	}
	else if(letter1==18){
		coordX=16;
	}
	else if(letter1==20){
		coordX=17;
	}
	else if(letter1==22){
		coordX=18;
	}
	else if(letter1==19){
		coordX=19;
	}
	else if(letter1==2){
		coordX=20;
	}
	else if(letter1==23){
		coordX=21;
	}
	else if(letter1==21){
		coordX=22;
	}
	else if(letter1==25){
		coordX=23;
	}
	return coordX;
}

int Coord::coord_conversionY(){
	//function returning the coordinate Y associated to the letter given in parameter
	int coordY;
	if(letter2==1){
		coordY=23;
	}
	else if(letter2==16){
		coordY=22;
	}
	else if(letter2==13){
		coordY=21;
	}
	else if(letter2==4){
		coordY=20;
	}
	else if(letter2==3){
		coordY=19;
	}
	else if(letter2==15){
		coordY=18;
	}
	else if(letter2==5){
		coordY=17;
	}
	else if(letter2==7){
		coordY=16;
	}
	else if(letter2==8){
		coordY=15;
	}
	else if(letter2==9){
		coordY=14;
	}
	else if(letter2==11){
		coordY=13;
	}
	else if(letter2==10){
		coordY=12;
	}
	else if(letter2==12){
		coordY=11;
	}
	else if(letter2==6){
		coordY=10;
	}
	else if(letter2==14){
		coordY=9;
	}
	else if(letter2==17){
		coordY=8;
	}
	else if(letter2==18){
		coordY=7;
	}
	else if(letter2==20){
		coordY=6;
	}
	else if(letter2==22){
		coordY=5;
	}
	else if(letter2==19){
		coordY=4;
	}
	else if(letter2==2){
		coordY=3;
	}
	else if(letter2==23){
		coordY=2;
	}
	else if(letter2==21){
		coordY=1;
	}
	else if(letter2==25){
		coordY=0;
	}
	return coordY;
}


int Coord::score() //function the returning the score found in the substitution matrix
{	
	//open the txt file with the matrix
	ifstream fichier(matrice_file);
	if(!fichier.is_open())
	{
		cout << "Impossible to open the file" << endl;
		return 0;
	}
	
	int tailleX(24);
	int tailleY(24);
	int matrice[tailleX][tailleY]; //d'abord on crée la matrice de substitution en lisant la matrice BLOSUM reçu en argument
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
	
	int coordX = coord_conversionX(); //on applique les fonctions de conversion pour convertir les coord en int8 en coord de int tout simple
	int coordY = coord_conversionY();
	int score = matrice[coordX][coordY]; //le score est la valeur trouvée à la position donnée par les coord dans la matrice de substitution
	
	return score;

}
