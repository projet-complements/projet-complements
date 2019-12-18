#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <byteswap.h>
#include <sstream>
#include "letter.h"
#include "algo.h"
#include "index.h"
#include "matrice.h"
#include <stdlib.h>
#include <ctime>   
using namespace std;

int8_t* setInArray(string fichier){
	
	ifstream database_file (fichier, ios::in | ios::binary);

	// copy the database in an array
	database_file.seekg(0,ios_base::end); // go to the last position
	int taille = database_file.tellg(); // gives the size of the database
	database_file.seekg(0,ios_base::beg);
	int8_t *db;
	db= new int8_t [taille]; //creates array of int8_t
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
	query_file.close();

	// Create index type which will give every information needed in the .pin
	Index* index= new Index(argv[2]);
	int32_t version= index->version;
	int32_t database_type= index->database_type;
	int32_t title_length= index->title_length;
	int32_t timestp_length= index->timestp_length;
	int32_t nbseq= index->nbseq;
	int32_t maxseq= index->maxseq;
	int64_t residuecount= index->residuecount;
	char* title= index->title;
	char* timestp= index->timestp;
	int32_t* header_offset= index->header_offset;
	int32_t* sequence_offset= index->sequence_offset;

	
	// Open the .psq
	string argv3 = argv[2];
	argv3+=".psq";
	int8_t *db;
	// set the database in an Array
	db=setInArray(argv3);
	
	
	// verify if there are arguments, else it takes the default one
	string arg_blosum;
	if (argc<4){
		arg_blosum="BLOSUM62";
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
	
	// creates a matrix type to have the blosum matrix
	Matrice* matrix = new Matrice(arg_blosum);
	int** M = matrix->matrice_score();
	// creates a type algo, with the data needed as attribute
	Algo* algo = new Algo(db, queryv, nbseq, sequence_offset, M , open_penalty, ext_penalty);
	
	// we do the Watermann Smith algorithm
	int* tableau = algo->sw();
	cout << "Algorithm is done"<<endl;
	
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
	
	string argv4 = argv[2];
	argv4+=".phr";
	ifstream header_file (argv4, ios::in | ios::binary);
	if( !header_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	
	
	int taille(nbseq);
	
	for(int nbremax=0; nbremax<10;){ // we want the 10 maximum
		int max = 0; 
		int position=0;
		int8_t reading;
		for (int i=0; i < taille; i++){ 
			if(max < tableau[i]){ // if we find a new max in the score tab
				max = tableau[i]; 
				position = i; // gives the index of the maximum
			}
		}
		nbremax ++;
		cout << endl << "maximum" << nbremax << ":" << max << " at position " << position << endl;
		result << endl << "maximum" << nbremax << " score: " << max << endl;
		tableau[position] = 0; // set the element at 0
		
		//takes position of the maximum as argument and looks for the position of the beginning of the title, starting with 1A
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
			result << (char)(reading);
		}
	}
	cout << endl;
	result << endl;
	duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"duration of algorithm : "<< duration << endl;

	return 0;
}
