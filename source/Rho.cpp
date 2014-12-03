#include "headerFiles.h"
#include "Rho.h"


Rho::Rho(string nombre, double valor)
{
	_nombre = nombre;
	_valor = valor;
	_largo = nombre.length();
	_factor1 = _nombre.substr(0, _nombre.find("$") - 1);
	_factor2 = _nombre.substr(_nombre.find("$") + 1, _largo - 1 - _nombre.find("$"));
}
string Rho::factor1()
{
	return _factor1;
}
string Rho::factor2()
{
	return _factor2;
}
//Agrega un método que devuelve el valor
double Rho::valor()
{
	return _valor;
}

Rho::Rho(void)
{
}

Rho::~Rho(void)
{
}
