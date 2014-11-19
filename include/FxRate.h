
#ifndef FX_RATE_H
#define FX_RATE_H

#include<string>

using namespace std;

class FxRate
{
private:
	std::string _nombre;
	double _valor;
	std::string _curvaDebil;
	std::string _curvaFuerte;
	int _d;
	int _f;

public:
	FxRate(std::string nombre, double valor);
	FxRate(string nombre, double valor, string nombreCurvaDebil, string nombreCurvaFuerte);
	double valor();
	std::string monedaFuerte();
	std::string monedaDebil();
	std::string curvaDebil();
	std::string curvaFuerte();
	FxRate(void);
	~FxRate(void);
};
#endif