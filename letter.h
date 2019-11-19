#include <string>
#include <iostream>
#include <bitset> 

class Letter
{
private:
	string Name;
	
public:
	Letter(); //constructeur	
	std::bitset<8> binary_conversion(Letter name);

};
