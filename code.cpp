#include <iostream>
#include <string>
#include <bitset> 
#include <fstream>
#include <vector>
#include <cstdint>
#include <byteswap.h>
#include "letter.h"
#include <stdlib.h>
#include <ctime>   
using namespace std;


/* Program prints the name of the exact sequence in the database:equality test between the query and the whole database
 * Parameter: argv[1]=query (FASTA), argv[2]=database (BLAST)
 * defaut : BLOSUM62, gap open penalty 11,gap extension penalty 1
 * sinon : ajout de paramètres
*/

int main(int argc, char *argv[])
{	clock_t start;
    double duration;
    start = clock();
	
	// verify that we have 3 arguments, the name of the program and the 2 files
	if (argc < 3) {
		printf("Error: need 2 arguments \n");
		return 1;
	}
	
	
	// OPEN THE QUERY
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
	std::vector<int8_t> query; 
		while(query_file >> c)
		{	
			s=c;
			Letter* lettre = new Letter(s);
			int8_t bit;
			bit = lettre->binary_conversion();
			query.push_back(bit); 
		}

	query_file.close();


	// OPEN THE PIN
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

	
	// OPEN THE PSQ
	string argv3 = argv[2];
	argv3+=".psq";
	ifstream database_file (argv3, ios::in | ios::binary);
	if( !database_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}

	//on recopie la database dans un tableau
	database_file.seekg(0,ios_base::end); //on va a la dernière position dans le fichier sequence
	int taille = database_file.tellg(); //on regarde où on est, ce qui nous donne la taille du tableau
	cout << "taille= " << taille << endl;
	database_file.seekg(0,ios_base::beg);
	int8_t *db;
	db= new int8_t [taille]; //cree un tableau de bit
	database_file.read((char*)&db[0], sizeof(int8_t)*(taille));
	

	int index,n,m,res1,res2,res3;
	int8_t b;
	// pour l'instant on prend un penalty gap au hasard
	int penalty_gap = -5;
   // parse the whole database
   for (int i =0; i<(nbseq+1) ;i++){
	   // on stocke la sequence qu'on regarde dans tmp
	   std::vector<int8_t> tmp; 
	   while(b!=0){	
			int increment = 0;
			b = db[sequence_offset[i]+increment];
			tmp.push_back(b);
			increment++;
		}
		n=sizeof(query); // taille de la première sequence
		m=sizeof(tmp); // taille de la seconde sequence
		
		// on initialise la matrice de l'algorithme qui a une taille (n+1)x(m+1)
		int H[n+1][m+1];
		
		//initialise premiere colonne/ligne a 0
		for (int ii = 0; ii<n+1; ii++){
			H[ii][0]=0;
		}
		for (int jj = 0; jj<m+1; jj++){
			H[0][jj]=0;
		}
		
		//donne la valeur pour le reste de la matrice
		for (int i = 1; i < n+1 ; i++){
			for (int j = 1; j < m+1 ; j++){
				// on cree un Coord qui va prendre les 2 int8_t dans les sequences pour en renvoyer le score
				Coord* coord = new Coord(query[i],tmp[j]);
				int x = coord->coord_conversionX;
				int y = coord->coord_conversionY;
				res1=H[i][j-1]+penalty_gap;
				res2=H[i-1][j-1]+score(x,y);
				res3=H[i-1][j]+penalty_gap;
				//H[i][j]=max(res1, res2, res3,0);
			}
		}
		//score de tmp=max dans toute la matrice.
	}
	
	
	database_file.close();



	//OPEN THE HEADER
	string argv4 = argv[2];
	argv4+=".phr";
	ifstream header_file (argv4, ios::in | ios::binary);
	if( !header_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
		return 1;
	}
	int8_t reading;
	//takes index as argument and looks for the position of the beginning of the title,start with 1A
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
	duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"duration of algorithm : "<< duration << endl;

	return 0;
}
