#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <byteswap.h>
#include "letter.h"
#include "algo.h"
#include "matrice.h"
#include <stdlib.h>
#include <ctime>   
using namespace std;


/* Program prints the name of the exact sequence in the database:equality test between the query and the whole database
 * Parameter: argv[1]=query (FASTA), argv[2]=database (BLAST)
 * defaut : BLOSUM62, gap open penalty 11,gap extension penalty 1
 * sinon : ajout de paramètres
*/

int8_t* setInArray(string fichier){
	
	ifstream database_file (fichier, ios::in | ios::binary);

	//on recopie la database dans un tableau
	database_file.seekg(0,ios_base::end); //on va a la dernière position dans le fichier sequence
	int taille = database_file.tellg(); //on regarde où on est, ce qui nous donne la taille du tableau
	database_file.seekg(0,ios_base::beg);
	int8_t *db;
	db= new int8_t [taille]; //cree un tableau de bit
	database_file.read((char*)&db[0], sizeof(int8_t)*(taille));
	database_file.close();

	
	return db;
}


int main(int argc, char *argv[])
{	
	clock_t start;
    double duration;
    start = clock();
	
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
		return 1;
	}
	string str;
	// ignore first line
    std::getline(query_file, str);
    str.clear();
    
    // c is the character in the file, s is the name of the Letter created, query is a vector containing the binary form of each letter
	char c;
	string s = "";
	std::vector<int8_t> queryv; 
	while(query_file >> c)
	{	
		s=c;
		Letter* lettre = new Letter(s);
		int8_t bit;
		bit = lettre->binary_conversion();
		queryv.push_back(bit); 
	}
	
	int8_t* query = &queryv[0]; //si pas ancien enlever
	query_file.close();

	// open the index file to find the title position of the sequence
	string argv2 = argv[2];
	argv2+=".pin";
	ifstream index_file (argv2, ios::in | ios::binary);
	if(!index_file.is_open())
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	
	// initialize the variables to save the information
	int32_t version,database_type, title_length, timestp_length,nbseq, maxseq;
	int64_t residuecount;

	// read the version
	index_file.read((char*)&version, sizeof(int32_t));
	version = __bswap_32(version);
	
	// read the databasetype
	index_file.read((char*)&database_type, sizeof(int32_t));
	database_type= __bswap_32(database_type);
	
	// read the title length
	index_file.read((char*)&title_length, sizeof(int32_t));
	title_length =__bswap_32(title_length);
	
	// read title
	char title[title_length];
	index_file.read((char*)title, sizeof(char)*(title_length));
	title[title_length]=0;
	
	// read the timestamp length
	index_file.read((char*)&timestp_length, sizeof(int32_t));
	timestp_length=__bswap_32(timestp_length);
	
	// read the timestamp 
	char timestp[timestp_length];
	index_file.read((char*)timestp, sizeof(char)*(timestp_length));
	timestp[timestp_length]=0;

	
	// read the number of sequences (N)
	index_file.read((char*)&nbseq, sizeof(int32_t));
	nbseq=__bswap_32(nbseq);
	
	// read the residue count
	index_file.read((char*)&residuecount, sizeof(int64_t));
	
	// read the maximum sequence
	index_file.read((char*)&maxseq, sizeof(int32_t));
	maxseq=__bswap_32(maxseq);
	
	// read the offsets
	int32_t header_offset[nbseq+1];
	int32_t sequence_offset[nbseq+1];

	index_file.read((char*)&header_offset[0], sizeof(int32_t)*(nbseq+1));
	index_file.read((char*)&sequence_offset[0], sizeof(int32_t)*(nbseq+1));
	for(int i = 0; i < nbseq+1; i++){
		header_offset[i] = __bswap_32(header_offset[i]);
		sequence_offset[i] = __bswap_32(sequence_offset[i]);
	}
	index_file.close();

	// OPEN THE PSQ
	//à faire : verifier que tout s'est bien passé
	string argv3 = argv[2];
	argv3+=".psq";
	int8_t *db;
	try {
		db=setInArray(argv3);
	} catch(std::bad_alloc & a) {
		cout << "erreur bad alloc" << endl;
	}
	
	//verifie s'il y a un argument, sinon prend celui par défaut
	string arg_blosum;
	if (argc<4){
		arg_blosum="BLOSUM62.txt";
	}
	else {
		arg_blosum=argv[3];
	}
	
	int open_penalty;
	if (argc<5){
		open_penalty=11;
	}
	else {
		open_penalty=atoi(argv[4]);
	}
	
	int ext_penalty;
	if (argc<6){
		ext_penalty=1;
	}
	else {
		ext_penalty=atoi(argv[5]);
	}
	
	Matrice* matrix = new Matrice(arg_blosum);
	int** M = matrix->matrice_score();
	cout << "matrice crée" << endl;
	Algo* algo = new Algo(db, query, nbseq, sequence_offset, M , open_penalty, ext_penalty); //nbseq+1 queryv
	// we do the Watermann Smith algorithm
	int* tableau = algo->sw();
	cout << "l'algo est fini"<<endl;
	
	ofstream result;
	result.open("results.txt");
	result << "Database name: ";
	for(int i=0;i<title_length;i++){
		result << " " << title[i];
	}
	result << endl;
	result << "Database time: ";
	for(int i=0; i<timestp_length-2; i++){
		result << " "<< timestp[i];
	}
	result << endl;
	result << "Query name: " << argv[1] << endl;
	result << "Query size: " << algo->n << endl;
	
	string argv4 = argv[2];
	argv4+=".phr";
	ifstream header_file (argv4, ios::in | ios::binary);
	if( !header_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	//boucle pour trouver les 30 premiers max dans le tableau score défini dans algo
	//int* tableau = {algo->score};
	//int* tableau[taille] = {*tableau_score}; // !!JAI DU METTRE DANS ALGO TYPE DU SCORE À INT AU LIEU DE INT* ET EN PUBLIC AU LIEU DE PRIVATE
	
	int taille(nbseq); //nbseq+1
	
	for(int nbremax=0; nbremax<30;){ //on veut les 30 premiers max
		int max = 0; //on pose le max étant le 1er élément du tableau
		int position=0;
		int8_t reading;
		for (int i=0; i < taille; i++){ //on parcourt tout le tableau
			if(max < tableau[i]){ //si on trouve un nouveau max
				max = tableau[i]; //max est cet élément-là
				position = i; //la position du max est donc la position de cet élément
			}
		}
		nbremax ++;
		cout << endl << "maximum" << nbremax << ":" << max << " à la position " << position << endl;
		tableau[position] = 0; //on met l'élément à cette position à 0 pour ne plus le considérer dans la suite
		//avec les positions des max on retrouve les protéines dans le fichier
		//takes position of the maxima as argument and looks for the position of the beginning of the title,start with 1A
		header_file.seekg(header_offset[position]);
		header_file.read((char*)&reading, sizeof(uint8_t));
		while(reading!=uint8_t(0x1A)){
			header_file.read((char*)&reading, sizeof(uint8_t));
		}
		header_file.read((char*)&reading, sizeof(uint8_t));
		//look for the end position of the title, ends with 0000
		while(reading!=uint8_t(0x0000)){
			header_file.read((char*)&reading, sizeof(uint8_t));
			cout << reading;
			//result << reading;
		}
	}
	cout << endl;
	result << endl;
	duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"duration of algorithm : "<< duration << endl;

	return 0;
}
