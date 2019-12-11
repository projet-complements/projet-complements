#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Index
{
private:
	int32_t version;
	int32_t database_type;
	int32_t title_length;
	vector<char> title;
	int32_t timestp_length;
	vector<char> timestp;
	int32_t nbseq;
	int64_t residuecount;
	int32_t maxseq;
	vector<int32_t> header_offset;
	vector<int32_t> sequence_offset;
	std::string argv2;
	int32_t header_offset[nbseq+1];
	int32_t sequence_offset[nbseq+1];
	char title[title_length];
	char timestp[timestp_length];
public:
	Index(std::string argv2,int32_t version,int32_t database_type,int64_t residuecount,int32_t nbseq,int32_t maxseq); //constructor	
	
};
