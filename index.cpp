#include "index.h"


Index::Index(vector<char> tit,vector<char> time,vector<int32_t> vh, vector<int32_t> vs){ //constructeur de la classe
	version=0;
	database_type=0;
	title_length=0;
	title=tit;
	timestp_length=0;
	timestp=time;
	nbseq=0;
	residuecount=0;
	maxseq=0;
	header_offset=vh;
	sequence_offset=vs;
}




