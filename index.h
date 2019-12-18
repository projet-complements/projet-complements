#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

class Index
{

public:
	int32_t version;
	int32_t database_type;
	int32_t title_length;
	char* title;
	int32_t timestp_length;
	char* timestp;
	int32_t nbseq;
	int64_t residuecount;
	int32_t maxseq;
	int32_t* header_offset;
	int32_t* sequence_offset;
	Index(std::string argv2); //constructor	
	
};
