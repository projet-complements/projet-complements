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
	int** matrice=new int*[N];; //creating the substitution matrix by reading the BLOSUM matrix
	for(int i = 0; i < N; i++) {
		matrice[i] = new int[N];
		for(int j = 0; j < N; j++)
		    matrice[i][j] = -1;
	}
	string str="";
	int j;
	for(j=30; j>-1; j--){ //there are 30 lines in a file and coordY goes from 23 to 0 by reading from the top to bottom
		std::getline(fichier, str);
		if(str[0]=='#') //lines beginning with # are ignored
		{
			str.clear();
		}
		else if(str[0]==' '){ //lines beginning with a white space are ignored
			str.clear();
		}
		else{ //line beginning with something else: a letter and then the values
			int i;
			int chiffre;
			int coordX=-1;
			int coordY;
			string s;
			int neg = 0;
			int dec = 0;
			//assumption that all numbers with 2 digits go maximum to 29 and are always positive
			for(i=2; i<74; i++){ //next elements are the values to put in the matrix from the file going from element 2 to 74 including spaces, signes and digits
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
				else{ //normally we now have a digit
					s = str[i];
					stringstream geek(s); //object from the class stringstream with the value of s
					if(neg==1){
						geek >> chiffre; //chiffre becomes negative if neg=1
						chiffre = -chiffre;
					}
					else{
						geek >> chiffre; //stream the object geek to integer chiffre
						if(dec==1){ //with the assumption that we only have positive 2-digit numbers
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
					coordY=j;	 //coord Y is equal to the considered line
					matrice[coordX][coordY]=chiffre; //we put the value at the position(X,Y) of the matrix
					neg=0;
					dec=0;
				}
			}
		}	
	}
	return matrice;
}
