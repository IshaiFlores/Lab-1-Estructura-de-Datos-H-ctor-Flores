#pragma once
#include <string>
#include <list>

using namespace std;

class Apartment
{ 
	//Atributos
	
	list<string> Business;


	public:

		//Constructor
		Apartment(list<string>& businesses);
			
		Apartment();


		list<string> getBusiness() { return Business; }
	


};

