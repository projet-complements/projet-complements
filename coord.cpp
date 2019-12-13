#include "coord.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <sstream> 
using namespace std;

 
Coord::Coord(int8_t coordX, int8_t coordY, Matrice matrice){
	letter1=coordX;
	letter2=coordY;
	matrice=matrice;
}

int Coord::coord_conversionX(){
	cout << "coord X" << endl;
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
	cout << "coordY" << endl;
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
	int coordX = coord_conversionX(); //on applique les fonctions de conversion pour convertir les coord en int8 en coord de int tout simple
	int coordY = coord_conversionY();
	int score = matrice[coordX][coordY]; //le score est la valeur trouvée à la position donnée par les coord dans la matrice de substitution
	
	return score;

}
