#include <string>
#include <iostream>
using namespace std;

class Letter
{
private:
	string name; //attribut de letter
	
public:
	Letter(string name); //constructeur	
	int8_t binary_conversion(); //convertisseur
};
