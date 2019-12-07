#include "coord.h"
/* POUR COMPILER (on compile d'abord le fichier de la classe, puis on compile tout ensemble pour pouvoir les utiliser entre eux!)
 * g++ coord.cpp -c
 * g++ coord.o match.cpp -o match
 * */
 
Coord::Coord(string coordX, string coordY){
	letter1=coordX;
	letter2=coordY;
}

int Coord::coord_conversionX(){
	//function returning the coordinate X associated to the letter given in parameter
	int coordX;
	if(letter1=="A"){
		coordX=0;
	}
	else if(letter1=="R"){
		coordX=1;
	}
	else if(letter1=="N"){
		coordX=2;
	}
	else if(letter1=="D"){
		coordX=3;
	}
	else if(letter1=="C"){
		coordX=4;
	}
	else if(letter1=="Q"){
		coordX=5;
	}
	else if(letter1=="E"){
		coordX=6;
	}
	else if(letter1=="G"){
		coordX=7;
	}
	else if(letter1=="H"){
		coordX=8;
	}
	else if(letter1=="I"){
		coordX=9;
	}
	else if(letter1=="L"){
		coordX=10;
	}
	else if(letter1=="K"){
		coordX=11;
	}
	else if(letter1=="M"){
		coordX=12;
	}
	else if(letter1=="F"){
		coordX=13;
	}
	else if(letter1=="P"){
		coordX=14;
	}
	else if(letter1=="S"){
		coordX=15;
	}
	else if(letter1=="T"){
		coordX=16;
	}
	else if(letter1=="W"){
		coordX=17;
	}
	else if(letter1=="Y"){
		coordX=18;
	}
	else if(letter1=="V"){
		coordX=19;
	}
	else if(letter1=="B"){
		coordX=20;
	}
	else if(letter1=="Z"){
		coordX=21;
	}
	else if(letter1=="X"){
		coordX=22;
	}
	else if(letter1=="*"){
		coordX=23;
	}
	return coordX;
}

int Coord::coord_conversionY(){
	//function returning the coordinate Y associated to the letter given in parameter
	int coordY;
	if(letter2=="A"){
		coordY=23;
	}
	else if(letter2=="R"){
		coordY=22;
	}
	else if(letter2=="N"){
		coordY=21;
	}
	else if(letter2=="D"){
		coordY=20;
	}
	else if(letter2=="C"){
		coordY=19;
	}
	else if(letter2=="Q"){
		coordY=18;
	}
	else if(letter2=="E"){
		coordY=17;
	}
	else if(letter2=="G"){
		coordY=16;
	}
	else if(letter2=="H"){
		coordY=15;
	}
	else if(letter2=="I"){
		coordY=14;
	}
	else if(letter2=="L"){
		coordY=13;
	}
	else if(letter2=="K"){
		coordY=12;
	}
	else if(letter2=="M"){
		coordY=11;
	}
	else if(letter2=="F"){
		coordY=10;
	}
	else if(letter2=="P"){
		coordY=9;
	}
	else if(letter2=="S"){
		coordY=8;
	}
	else if(letter2=="T"){
		coordY=7;
	}
	else if(letter2=="W"){
		coordY=6;
	}
	else if(letter2=="Y"){
		coordY=5;
	}
	else if(letter2=="V"){
		coordY=4;
	}
	else if(letter2=="B"){
		coordY=3;
	}
	else if(letter2=="Z"){
		coordY=2;
	}
	else if(letter2=="X"){
		coordY=1;
	}
	else if(letter2=="*"){
		coordY=0;
	}
	return coordY;
}
