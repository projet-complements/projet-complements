#include <iostream>
#include <string>
#include <fstream>
using namespace std; //on peut?


// Program prints the name of the exact sequence in the database:equality test between the query and the whole database
// NB:the query can have a fake name, makefile to do too
// Parameter: argv[1]=query (FASTA), argv[2]=database (BLAST)
// compile : g++ match.cpp -o match -Wall
// execute : ./match fichier1 fichier2

int main(int argc, char *argv[])
{
	
	
	// verify that we have 3 arguments, the name of the program and the 2 files
	if (argc < 4) {
		printf("Error: need 2 arguments \n");
		return 1;
	}
	
	set<string> database; //set of all the sequences from the database
	string query;
	
	
	// FASTA: la requete est donnee sous forme fasta cad qu'on a >l'identifiant, le commentaire puis toute la séquence
	// doit donc ignorer l'identifiant car peut être faux
	// 80 charact par ligne? à verifier
	ifstream query_file (argv[1], ios::in | ios::binary);
	if( query_file.is_open() )
	{
		//. . .
		query_file.close();
	}
	else{
		cout << "Impossible d'ouvrir le fichier" << endl;
		return 1;//retourne 1 en cas d'erreur
	}



	//BLAST: index=info on database, sequence=info on residues, header=info on header of sequence
	ifstream database_file (argv[2], ios::in | ios::binary);
	if( database_file.is_open() )
	{
		//. . .
		database_file.close();
	}
	else{
		cout << "Impossible d'ouvrir le fichier" << endl;
		return 1;
	}
	
	
	return 0;
}
