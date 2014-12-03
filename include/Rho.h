//
//
//

#ifndef RHO_H
#define RHO_H
#include <string>

using namespace std;
class Rho
{
private:
	string _nombre;
	double _valor;
	string _factor1;
	string _factor2;
	int _largo;
public:
	Rho(string nombre, double valor);
	string factor1();
	string factor2();
	double valor();
	Rho(void);
	~Rho(void);
};

#endif