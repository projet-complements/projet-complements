#include <iostream>
#include <string>
#include <bitset> 
#include <fstream>
#include <vector>
#include <cstdint>
#include <byteswap.h>
#include "letter.h"
#include <stdlib.h>
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
		return 1;
	}
	string str;
	// ignore first line
    std::getline(query_file, str);
    str.clear();
    
    
    // c is the character in the file, s is the name of the Letter created, query is a vector containing the binary form of each letter
	char c;
	string s = "";
	std::vector< bitset<8> > query; 
		while(query_file >> c)
		{	
			s=c;
			Letter* lettre = new Letter(s);
			std::bitset<8> bit;
			bit = lettre->binary_conversion();
			query.push_back(bit); 
		}

	query_file.close();


	// open the index file to find the title position of the sequence
	string argv2 = argv[2];
	argv2+=".pin";
	ifstream index_file (argv2, ios::in | ios::binary);
	if( !index_file.is_open() )
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
	
	
	// open the sequence file
	
	string argv3 = argv[2];
	argv3+=".psq";
	ifstream database_file (argv3, ios::in | ios::binary);
	if( !database_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}

	
	// b is the bit of the current letter read in the database, tmp is the current sequence read in the database
	
   std::bitset<8> b = 0b10000000;
   int index;

   // parse the whole database
   for (int i =0; i<(nbseq+1) ;i++){
	   database_file.seekg(sequence_offset[i]);
	   int breaking_out = 0;
	   for (int j = 0;j < query.size() ; j++){
		b = database_file.get();
		if (b!=query[j]){
			break;
		}
		if (j == (query.size()-1)){
			cout << "Found the sequence!"<< endl;
			index=i;
			breaking_out=1;
			break;
		}
	   }
	   
	   if (breaking_out==1){
		   break;
		}

	}

	database_file.close();


	string argv4 = argv[2];
	argv4+=".phr";
	ifstream header_file (argv4, ios::in | ios::binary);
	if( !header_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	int8_t reading;
	/*takes index as argument and looks for the position of the beginning of the title,
                start with 1A*/
	header_file.seekg(header_offset[index]);
	header_file.read((char*)&reading, sizeof(uint8_t));
	while(reading!=uint8_t(0x1A)){
		header_file.read((char*)&reading, sizeof(uint8_t));
	}
	header_file.read((char*)&reading, sizeof(uint8_t));
	//look for the end position of the title, ends with 0000
	while(reading!=uint8_t(0x0000)){
		header_file.read((char*)&reading, sizeof(uint8_t));
		cout << reading;
	}
	cout << endl;
	
	return 0;
}
