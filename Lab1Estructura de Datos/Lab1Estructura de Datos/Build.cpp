#include "Build.h"

Build::Build()
{
}

Build::Build(string direccion, double precio, string phone, string id):address(direccion), price(precio), Phone(phone), ID(id)
{
	this->address = direccion;
	this->price = precio;
	this->Phone = phone;
	this->ID = id;
}
