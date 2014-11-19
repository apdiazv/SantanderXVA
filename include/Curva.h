//
// DESCRIPTION 
//

#ifndef CURVA_H
#define CURVA_H

#include <vector>
#include <string>

class Curva
{
public:
	std::string nombre;
	std::vector<double> tenors;
	std::vector<double> rates;
	Curva(std::string inNombre, std::vector<double> inTenors, std::vector<double> inRates);
	Curva(void);
	~Curva(void);

};

#endif
