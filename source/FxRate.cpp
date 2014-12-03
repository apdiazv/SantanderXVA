#include "headerFiles.h"
#include "FxRate.h"


FxRate::FxRate(string nombre, double valor)
{
	_nombre = nombre;
	_valor = valor;
}

FxRate::FxRate(string nombre, double valor, string nombreCurvaDebil, string nombreCurvaFuerte)
{
	_nombre = nombre;
	_valor = valor;
	_curvaDebil = nombreCurvaDebil;
	_curvaFuerte = nombreCurvaFuerte;
}

double FxRate::valor()
{
	return _valor;
}

string FxRate::monedaFuerte()
{
	return _nombre.substr(0, 3);
}
	
string FxRate::monedaDebil()
{
	return _nombre.substr(3, 3);
}
	
string FxRate::curvaDebil()
{
	return _curvaDebil; 
}

string FxRate::curvaFuerte()
{
	return _curvaFuerte; 
}

FxRate::FxRate(void)
{
}

FxRate::~FxRate(void)
{
}
