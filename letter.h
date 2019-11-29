#include <string>
#include <iostream>
#include <bitset>
using namespace std;
//converter
class Letter
{
private:
	string name;
	
public:
	Letter(string name); 
	std::bitset<8> binary_conversion(); 
};
