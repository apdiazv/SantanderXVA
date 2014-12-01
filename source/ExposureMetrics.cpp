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
	if ( count_Ceros ==  valoresNettingSet.size())
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
	count = 0;
	if(flag)
	{
		for (unsigned int i = 0; i < _valoresNettingSet.size(); i++)
		{
			_exposure.at(i) = max(_valoresNettingSet[i] - _amountCollateral[i], 0.0);
		}
		// cuenta el número de valores positivos
		count = std::count_if (_exposure.begin(), _exposure.end(), isPositive);
	}
}

void ExposureMetrics::claculateExposicionNegativa()
{
	countNeg = 0;
	if(flag)	
	{
		for (unsigned int i = 0; i < _valoresNettingSet.size(); i++)
		{
			_negExposure.at(i) = min(_valoresNettingSet[i] - _amountCollateral[i], 0.0);
		}
		countNeg = std::count_if (_negExposure.begin(), _negExposure.end(), isNegative);
	}
}

double ExposureMetrics::getValorFuturoEsperado()
{
    double result = 0;
	if(flag)	
	{
		result = mean(_valoresNettingSet) - mean(_amountCollateral);
	}
	 return result;
}

double ExposureMetrics::getExposicionEsperada()
{
	// double result = mean(_exposure); Corregido el 26/11/14
	double result = 0.0;	
	if (count > 0)
	{ 
		for (std::vector<double>::iterator it = _exposure.begin(); it != _exposure.end(); ++it) 
		{
			result += *it;
		}
		result = result / count;
	}
	return  result;
}

double ExposureMetrics::getExposicionNegativaEsperada()
{
	//double result = mean(_negExposure);
	double result = 0.0;	
    if (countNeg > 0)
	{ 
		for (std::vector<double>::iterator it = _negExposure.begin(); it != _negExposure.end(); ++it) 
		{
			result += *it;
		}
		result = result / countNeg;
	}
	 return result;
}

double ExposureMetrics::getExposicionPotencialFutura(double _per)
{
	double result = 0.0;
	if (count > 0)
	{
		vector<double> _auxExp(_exposure);
		remove_if(_auxExp.begin(), _auxExp.end(), isCero);
		_auxExp.resize(count);
		result = percentil(_auxExp, _per);
	}
	return result;
}

double ExposureMetrics::getExposicionMaxima()
{
	double result = 0.0;
	if (count > 0)
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
