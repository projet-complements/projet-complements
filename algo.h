#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "coord.h"
using namespace std;

class Algo {
private:
	vector<int8_t> query;
	int8_t* db;
	int32_t* offset;
	int n;
	int size;
	int** arg_blosum;
	int open;
	int ext;
	
public:
	Algo(int8_t* db,vector<int8_t> query,int size_score, int32_t* psq_offset,int** arg, int open, int ext); //constructeur	
	void sw();
	int* score;
};
