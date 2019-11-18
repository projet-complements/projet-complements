#include <iostream>
#include <string>
#include <fstream>
#include <set>
using namespace std; //on peut?


// Program prints the name of the exact sequence in the database:equality test between the query and the whole database
// NB:the query can have a fake name, makefile to do too
// Parameter: argv[1]=query (FASTA), argv[2]=database (BLAST)
// pour compiler : g++ match.cpp -o match -Wall
// pour executer : ./match fichier1 fichier2

int main(int argc, char *argv[])
{
	
	
	// verify that we have 3 arguments, the name of the program and the 2 files
	if (argc < 3) {
		printf("Error: need 2 arguments \n");
		return 1;
	}
	
	set<string> database; //set of all the sequences from the database
	string query;
	
	
	// FASTA: la requete est donnee sous forme fasta cad qu'on a >l'identifiant, le commentaire puis toute la séquence
	// doit donc ignorer l'identifiant car peut être faux
	// 80 charact par ligne? à verifier
	// on prend donc ligne par ligne : stocke dans un string?
	ifstream query_file (argv[1]);
	if( !query_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;//retourne 1 en cas d'erreur
	}
	
	// on contient tout dans un string
	/*string line, name, content;
    while( getline(query_file,line).good() ){ 
        if(line.empty() || line[0] == '>' ){ // lecture du fichier 
            if( !name.empty() ){ // lire le fichier 
                cout << name << " : " << content << endl;
                name.clear();
            }
            if( !line.empty() ){
                name = line.substr(1);
            }
            content.clear();
        } else if( !name.empty() ){
            if( line.find(' ') != std::string::npos ){ // en cas d'erreur d'espacement de sequence 
                name.clear();
                content.clear();
            } else {
                content += line;
            }
        }
    }
    if( !name.empty() ){ // Print out les fichies 
		cout << name << " : " << content << endl;
    }*/
	query_file.close();

	string argv2 = argv[2];
	argv2+=".psq";

	// BLAST: index=info on database, sequence=info on residues, header=info on header of sequence
	ifstream database_file (argv2, ios::in | ios::binary);
	if( !database_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	
    char sequence[80];
    char sequenc[80];
    char sequen[80];
    database_file.read(sequence,80);
	database_file.read(sequenc,80);
	database_file.read(sequen,80);
    cout << sequen << endl;
    cout << sequence << endl;
    cout << sequenc << endl;
	database_file.close();
	return 0;
}
