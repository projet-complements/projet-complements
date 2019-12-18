#include "index.h"


Index::Index(std::string argv2){

	argv2+=".pin";
	ifstream index_file (argv2, ios::in | ios::binary);
	if( !index_file.is_open() )
	{
		cout << "Impossible to open the file" << endl;
	}
	index_file.read((char*)&version, sizeof(int32_t));
	version = __bswap_32(version);
	// read the databasetype
	index_file.read((char*)&database_type, sizeof(int32_t));
	database_type= __bswap_32(database_type);
	
	// read the title length
	index_file.read((char*)&title_length, sizeof(int32_t));
	title_length =__bswap_32(title_length);
	
	// read title
	title = new char[title_length];
	index_file.read((char*)title, sizeof(char)*(title_length));
	title[title_length]=0;
	
     // read the timestamp length
	index_file.read((char*)&timestp_length, sizeof(int32_t));
	timestp_length=__bswap_32(timestp_length);
	
	// read the timestamp
	timestp = new char[timestp_length];
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
    
    sequence_offset = new int32_t[nbseq+1];
    header_offset = new int32_t[nbseq+1];
    index_file.read((char*)&header_offset[0], sizeof(int32_t)*(nbseq+1));
	index_file.read((char*)&sequence_offset[0], sizeof(int32_t)*(nbseq+1));
	for(int i = 0; i < nbseq+1; i++){
		header_offset[i] = __bswap_32(header_offset[i]);
		sequence_offset[i] = __bswap_32(sequence_offset[i]);
	}
	index_file.close();
	
}
