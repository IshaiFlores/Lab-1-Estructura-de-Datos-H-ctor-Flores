#pragma once
#include <string>
#include <list>
#include "Score.h"

using namespace std;

class Apartment
{ 
	//Atributos
	
	list<string> Business;

	Score puntaje;

	public:

		//Constructor
		Apartment(list<string>& businesses);
			
		Apartment();

		list<string> getBusiness() { return Business; }
	
		Score getPuntaje() { return puntaje; }

		void setPuntaje(Score Puntos) { puntaje = Puntos; }


};

