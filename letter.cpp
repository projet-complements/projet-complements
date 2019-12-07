#include "letter.h"
/* POUR COMPILER (on compile d'abord le fichier de la classe, puis on compile tout ensemble pour pouvoir les utiliser entre eux!)
 * g++ letter.cpp -c
 * g++ letter.o match.cpp -o match
 * */


Letter::Letter(string n){ //constructeur de la classe
	name = n;
}

int8_t Letter::binary_conversion(){
	//function returning the binary number associated to the letter given in parameter
	int8_t n; //on cree la variable ou on stocke le nombre binaire
	if(name=="A"){
		n=1; //0b c'est pour transformer en binaire
	}
	else if(name=="B"){
		n=2;
	}
	else if(name=="C"){
		n=3;
	}
	else if(name=="D"){
		n=4;
	}
	else if(name=="E"){
		n=5;
	}
	else if(name=="F"){
		n=6;
	}
	else if(name=="G"){
		n=7;
	}
	else if(name=="H"){
		n=8;
	}
	else if(name=="I"){
		n=9;
	}
	else if(name=="J"){
		n=27;
	}
	else if(name=="K"){
		n=10;
	}
	else if(name=="L"){
		n=11;
	}
	else if(name=="M"){
		n=12;
	}
	else if(name=="N"){
		n=13;
	}
	else if(name=="O"){
		n=26;
	}
	else if(name=="P"){
		n=14;
	}
	else if(name=="Q"){
		n=15;
	}
	else if(name=="R"){
		n=16;
	}
	else if(name=="S"){
		n=17;
	}
	else if(name=="T"){
		n=18;
	}
	else if(name=="U"){
		n=24;
	}
	else if(name=="V"){
		n=19;
	}
	else if(name=="W"){
		n=20;
	}
	else if(name=="X"){
		n=21;
	}
	else if(name=="Y"){
		n=22;
	}
	else if(name=="Z"){
		n=25;
	}
	return n; //renvoie le binaire
}



