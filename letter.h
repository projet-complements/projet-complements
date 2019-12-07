#include <string>
#include <iostream>
#include <bitset>
using namespace std;

class Letter
{
private:
	string name; //attribut de letter
	
public:
	Letter(string name); //constructeur	
	int8_t binary_conversion(); //convertisseur
};
