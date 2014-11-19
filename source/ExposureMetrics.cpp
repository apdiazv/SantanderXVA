#include "headerFiles.h"
#include "ExposureMetrics.h"

ExposureMetrics::ExposureMetrics(void)
{
}

ExposureMetrics::ExposureMetrics(size_t simulaciones)
{
	_simulaciones = simulaciones;
	_exposure.assign(_simulaciones, 0.0);
	_negExposure.assign(_simulaciones, 0.0);
}
void ExposureMetrics::setNumeroSimulaciones(size_t simulaciones)
{
	_simulaciones = simulaciones;
	_exposure.assign(_simulaciones, 0.0);
	_negExposure.assign(_simulaciones, 0.0);

}

void ExposureMetrics::setValor(std::vector<double> valoresNettingSet)
{
	_valoresNettingSet = valoresNettingSet;
			
}
void ExposureMetrics::setColateral(std::vector<double> amountCollateral)
{
	_amountCollateral = amountCollateral;		
}

void ExposureMetrics::calculateExposicion()
{
	for (unsigned int i = 0; i < _simulaciones; i++)
	{
		_exposure.at(i) = max(_valoresNettingSet[i] - _amountCollateral[i], 0.0);
	}	
}

void ExposureMetrics::claculateExposicionNegativa()
{
	for (unsigned int i = 0; i < _simulaciones; i++)
	{
		_negExposure.at(i) = min(_valoresNettingSet[i] - _amountCollateral[i], 0.0);
	}
}

double ExposureMetrics::getValorFuturoEsperado()
{
     double result = mean(_valoresNettingSet) - mean(_amountCollateral);
	 return result;
}

double ExposureMetrics::getExposicionEsperada()
{
	 double result = mean(_exposure);
	 return result;
}

double ExposureMetrics::getExposicionNegativaEsperada()
{
	 double result = mean(_negExposure);
	 return result;
}

double ExposureMetrics::getExposicionPotencialFutura(double _per)
{
	 double result = percentil(_exposure, _per);
	 return result;
}

double ExposureMetrics::getExposicionMaxima()
{
	double result = *max_element(_exposure.begin(), _exposure.end());
	return result;	
}


ExposureMetrics::~ExposureMetrics(void)
{
	_valoresNettingSet.clear();
	_amountCollateral.clear();
	_exposure.clear();
	_negExposure.clear();
}
