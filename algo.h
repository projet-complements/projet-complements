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
	int* score;
	int32_t* offset;
	int n;
	int size;
	string arg_blosum;
	
public:
	Algo(int8_t db[],vector<int8_t> query,int size_score, int psq_offset[], string arg); //constructeur	
	void sw();
};
