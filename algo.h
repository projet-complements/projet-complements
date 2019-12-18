#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "coord.h"
using namespace std;

class Algo {
private:
	int8_t* query;
	int8_t* db;
	int32_t* offset;
	int size;
	int** arg_blosum;
	int open;
	int ext;
	
public:
	int n;
	Algo(int8_t* db,int8_t* query,int size_score, int32_t* psq_offset,int** arg, int open, int ext);
	int* sw();
};
