#include <iostream>
#include <string>
#include <bitset> 
#include <fstream>
#include <set>
#include "letter.h"
using namespace std;


/* Program prints the name of the exact sequence in the database:equality test between the query and the whole database
 * NB:the query can have a fake name, makefile to do too
 * Parameter: argv[1]=query (FASTA), argv[2]=database (BLAST)
 * pour compiler : g++ match.cpp -o match -Wall
 * pour executer : ./match fichier1 fichier2*/

int main(int argc, char *argv[])
{
	
	
	// verify that we have 3 arguments, the name of the program and the 2 files
	if (argc < 3) {
		printf("Error: need 2 arguments \n");
		return 1;
	}
	

	
	/*TO DO:
	 * on ignore la première ligne
	 * on lit ligne par ligne, puis divise en caractère
	 * grâce a la classe 'Letter', qui a pour attribut 'Name', on utilise une fonction 'BinaryConversion(Letter)'
	 * renvoie un bitset<8>, cad la forme binaire de la lettre
	 * on stocke chaque binaire dans query (vecteur)
	*/
	
	
	// open the fasta file with the query
	ifstream query_file (argv[1]);
	if( !query_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;//retourne 1 en cas d'erreur
	}
	string str;
	
	// ignore first line
    std::getline(query_file, str);
    
    // c is the character in the file, s is the name of the Letter created
	char c;
	string s = "";
		while(query_file >> c)
		{	
			s=c;
			Letter* lettre = new Letter(s);
			std::bitset<8> bit;
			// bit is the binary number associated to the letter read
			bit = lettre->binary_conversion();
			
			// STOCKER DANS UN VECTEUR CONTENANT DES BITS (std::bitset<8) TOUS LES BITS
		}
	query_file.close();



	// open the sequence BLAST file
	string argv2 = argv[2];
	argv2+=".psq";
	ifstream database_file (argv2, ios::in | ios::binary);
	if( !database_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}

	/* on a stocké la query, maintenant on lit ligne par ligne le fichier .psq pour comparer avec la query
	 * une fois qu'on trouve la bonne sequence, on ouvre le fichier index et on en retire l'offset
	 * (comprendre comment on manipule les offsets/comment le fichier index est fait)
	 * puis, avec offset header, on trouve le nom de la proteine dans le fichier header
	 * (comprendre comment est constitué le fichier header)
	 * */
	 
   std::bitset<8> b;
    while(!database_file.eof())
		{
			b = database_file.get();
			if(!database_file.eof())
			//cout << b; imprimer toute la database
			//il faut couper la sequence quand on a un bit nul cad 00000000 (8 bits)
			//comparer la sequence coupee avec la query transformee en binaire

        
        
	/*CODE POUR BOUCLE DE COMPARAISON (pas encore testé):
	std::bitset<8> c;
	while(!database_file.eof() && database_file.get()!=query)
		{
			c = database_file.get();
			if(!database_file.eof()){
				// manip avec offset etc.
			}
		}
	*/
		
		
	/*	CODE POUR OUVRIR LE FICHIER PHR
	char c;
	while(!database_file.eof())
	{
		c = database_file.get();
		if(!database_file.eof()){
		cout << c;
		}
	}*/
	
	
	
	database_file.close();
	return 0;
	
}
