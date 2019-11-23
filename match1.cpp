#include <iostream>
#include <string>
#include <bitset> 
#include <fstream>
#include <set>
#include "letter.h"
#include <vector>
using namespace std;


/* Program prints the name of the exact sequence in the database:equality test between the query and the whole database
 * NB:the query can have a fake name, makefile to do too
 * Parameter: argv[1]=query (FASTA), argv[2]=database (BLAST)
*/

int main(int argc, char *argv[])
{
	
	
	// verify that we have 3 arguments, the name of the program and the 2 files
	if (argc < 3) {
		printf("Error: need 2 arguments \n");
		return 1;
	}
	
	
	// open the fasta file with the query
	ifstream query_file (argv[1]);
	if(!query_file.is_open())
	{
		cout << "Impossible to open the file" << endl;
		return 1;//retourne 1 en cas d'erreur
	}
	string str;
	// ignore first line
    std::getline(query_file, str);
    str.clear();
    
    
    // c is the character in the file, s is the name of the Letter created, query is a vector containing the binary form of each letter
	char c;
	string s = "";
	std::vector< bitset<8> > query; //crée un tableau de type bitset<8> vide
		while(query_file >> c)
		{	
			s=c;
			Letter* lettre = new Letter(s);
			std::bitset<8> bit;
			bit = lettre->binary_conversion();
			query.push_back(bit); //rajoute tous les chiffres en binaire dans le tableau
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

	
	// b is the bit of the current letter read in the database, tmp is the current sequence read in the database
	
   std::bitset<8> b = 0b10000000;
   std::vector< bitset<8> > tmp;
   
   // parse the whole database
    while( !database_file.eof() ){
		b = database_file.get();
		// if the bit read isn't null, we add it to the sequence
		if (b != 0b00000000){ 
			tmp.push_back(b);
		}
		
		// b is null, the sequence ended and we can compare the two vectors 
		
		else{
			// check if the two sequences are the same size, else we don't even look
			if (query.size() == tmp.size()){
				// check if every letter is the same
				int breaking_out = 0;
				for (int i = 0 ; (i < tmp.size())&&(query[i] == tmp[i]) ; i++){
					
					//cout << i << tmp.size() << endl;
					// if we are at the end of the vector, every letter is the same and we break the while
					if (i == (tmp.size()-1)){
						cout << "Found the sequence!" << endl;
						breaking_out=1;
						break;
					}
				}
				if(breaking_out==1){
					break;
				}
				// if we didn't found, reset the vector continue the loop
				tmp.clear();
				
			}
			
			else{
				// if the sizes aren't the same, continue the while loop
				tmp.clear();
			}
		}
	}

	database_file.close();

	/* TO DO:
	 * on va faire un compteur pour savoir à quel nombre de bits on est
	 * avec ce nombre de bits, on se repère dans le tableau offset sequence
	 * offset sequence donne, à chaque indice, à cb de bits on est
	 * l'indice dans les deux tableaux offset est le mm
	 * simple title est le nom de la sequence ds le fichier header
	 * */
	 
	 
	 
	/*	CODE POUR OUVRIR LE FICHIER PHR
	string argv3 = argv[2];
	argv3+=".phr";
	ifstream header_file (argv3, ios::in | ios::binary);
	if( !header_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	char t;
	
	while(!header_file.eof())
	{
		t = header_file.get();
		if(!header_file.eof()){
		cout << t;
		}
	}*/
	
	string argv4 = argv[2];
	argv4+=".pin";
	ifstream header_file (argv4, ios::in | ios::binary);
	if( !header_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	std::bitset<32> t;
	
	while(!header_file.eof())
	{
		t = header_file.get();
		if(!header_file.eof()){
		cout << t << endl;
		}
	}
	return 0;
}
