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

/*
void ExposureMetrics::setValor(const std::vector<double>& valoresNettingSet)
{
	_valoresNettingSet = valoresNettingSet;
			
}
void ExposureMetrics::setColateral(const vector<double>& amountCollateral)
{
	_amountCollateral = amountCollateral;		
}*/

void ExposureMetrics::setMtmAndColateral(const vector<double>& valoresNettingSet, const vector<double>& amountCollateral)
{
	unsigned int count_Ceros = std::count_if (valoresNettingSet.begin(), valoresNettingSet.end(), isCero);
	if ( count_Ceros == valoresNettingSet.size())
	{
		flag = false;
	}
	else
	{
		_valoresNettingSet = valoresNettingSet;
		_amountCollateral = amountCollateral;
		flag = true;
	}
}

void ExposureMetrics::calculateExposicion()
{
	if (flag)
	{
		for (unsigned int i = 0; i < _valoresNettingSet.size(); i++)
		{
			_exposure.at(i) = max(_valoresNettingSet[i] - _amountCollateral[i], 0.0);
		}
		// cuenta el número de valores positivos
		//count = std::count_if (_exposure.begin(), _exposure.end(), isPositive);
	}
}

void ExposureMetrics::claculateExposicionNegativa()
{
	if (flag)	
	{
		for (unsigned int i = 0; i < _valoresNettingSet.size(); i++)
		{
			_negExposure.at(i) = min(_valoresNettingSet[i] - _amountCollateral[i], 0.0);
		}
		//countNeg = std::count_if (_negExposure.begin(), _negExposure.end(), isNegative);
	}
}

double ExposureMetrics::getValorFuturoEsperado()
{
    double result = 0;
	if (flag)	
	{
		result = mean(_valoresNettingSet) - mean(_amountCollateral);
	}
	 return result;
}

double ExposureMetrics::getExposicionEsperada()
{
	double result = 0;
	if (flag)	
	{
	result = mean(_exposure); //ReCorregido el 10/12/14
	}
	return  result;
}

double ExposureMetrics::getExposicionNegativaEsperada()
{
	double result = 0.0;	
    if (flag)	
	{
		result = mean(_negExposure);
	}
	return result;
}

double ExposureMetrics::getExposicionPotencialFutura(double _per)
{
	double result = 0.0;
	if (flag)	
	{
		result = percentil(_exposure, _per);
	}
	return result;
}

double ExposureMetrics::getExposicionMaxima()
{
	double result = 0.0;
	if (flag)
	{
		result = *max_element(_exposure.begin(), _exposure.end());
	}
	return result;	
}


ExposureMetrics::~ExposureMetrics(void)
{
	_valoresNettingSet.clear();
	_amountCollateral.clear();
	_exposure.clear();
	_negExposure.clear();

}
