#include "letter.h" //faut inclure le fichier .h pour avoir la declaration de toute la classe!
/* POUR COMPILER (on compile d'abord le fichier de la classe, puis on compile tout ensemble pour pouvoir les utiliser entre eux!)
 * g++ letter.cpp -c
 * g++ letter.o match.cpp -o match
 * mais enft avec le tp6 j'ai vu qu'on pouvait faire un dictionnaire (avec map) et pe que c'est plus rapide
 * et efficace que pleins de if ...
 * */


Letter::Letter(string n){ //constructeur de la classe
	name = n;
}

std::bitset<8> Letter::binary_conversion(){
	//function returning the binary number associated to the letter given in parameter
	std::bitset<8> n; //on cree la variable ou on stocke le nombre binaire
	if(name=="A"){
		n=0b00000001; //0b c'est pour transformer en binaire
	}
	else if(name=="B"){
		n=0b00000010;
	}
	else if(name=="C"){
		n=0b00000011;
	}
	else if(name=="D"){
		n=0b00000100;
	}
	else if(name=="E"){
		n=0b00000101;
	}
	else if(name=="F"){
		n=0b00000110;
	}
	else if(name=="G"){
		n=0b00000111;
	}
	else if(name=="H"){
		n=0b00001000;
	}
	else if(name=="I"){
		n=0b00001001;
	}
	else if(name=="J"){
		n=0b00011011;
	}
	else if(name=="K"){
		n=0b00001010;
	}
	else if(name=="L"){
		n=0b00001011;
	}
	else if(name=="M"){
		n=0b00001100;
	}
	else if(name=="N"){
		n=0b00001101;
	}
	else if(name=="O"){
		n=0b00011010;
	}
	else if(name=="P"){
		n=0b00001110;
	}
	else if(name=="Q"){
		n=0b00001111;
	}
	else if(name=="R"){
		n=0b00010000;
	}
	else if(name=="S"){
		n=0b00010001;
	}
	else if(name=="T"){
		n=0b00010011;
	}
	else if(name=="U"){
		n=0b00011000;
	}
	else if(name=="V"){
		n=0b00010011;
	}
	else if(name=="W"){
		n=0b00010100;
	}
	else if(name=="X"){
		n=0b00010101;
	}
	else if(name=="Y"){
		n=0b00010110;
	}
	else if(name=="Z"){
		n=0b00010111;
	}
	return n; //renvoie le binaire
}



