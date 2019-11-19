#include <iostream>
#include <string>
#include <bitset> 
#include <fstream>
#include <set>
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
	 * on lit ligne par ligne, puis divise en caractère [CEDRIC]
	 * (pour ça, deux solutions : soit on lit lettre par lettre, soit on envoie une ligne à la fonction, qui découpe elle-même
	 * lettre par lettre)
	 * grâce a la classe 'Letter', qui a pour attribut 'Name', on utilise une fonction 'BinaryConversion(Letter)'[HA MY]
	 * renvoie un bitset<8>, cad la forme binaire de la lettre[HA MY]
	 * on stocke chaque binaire dans query (vecteur? tableau?)[CEDRIC]
	*/
	
	
	// open the fasta file with the query
	ifstream query_file (argv[1]);
	if( !query_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;//retourne 1 en cas d'erreur
	}

	/* CODE POUR LIRE LE FICHIER FASTA LIGNE PAR LIGNE
	string line, name, content;
    while( getline(query_file,line).good() ){ //lire ligne par ligne
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
	 
   std::bitset<8> c;
    while(!database_file.eof())
		{
			c = database_file.get();
			if(!database_file.eof())
			//cout << c; imprimer toute la database
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
