
#include "headerFiles.h"
#include "Curva.h"

Curva::Curva(void)
{
}

Curva::Curva(std::string inNombre, std::vector<double> inTenors, std::vector<double> inRates)
{
	if (inTenors.size() == inRates.size())
	{
		nombre = inNombre;
		tenors = inTenors;
		rates = inRates;		
	}

	return;
}

Curva::~Curva(void)
{
	tenors.clear();
	tenors.swap(std::vector<double> (tenors));
	rates.clear();
	rates.swap(std::vector<double> (rates));
}
