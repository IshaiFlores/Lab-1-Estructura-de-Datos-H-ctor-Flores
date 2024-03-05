#pragma once
#include "Build.h"

using namespace std;

class House:Build
{
	string zone;

	public:

	House();

	House(string address, double precio, string phone, string id, string zona);
};

