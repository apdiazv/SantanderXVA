#include "headerFiles.h"
#include "CreditExposure.h"

CreditExposure::CreditExposure(void)
{
}
//En el mapa vienen: 
//stopTime 
//vector ={auxEE, auxNEE, auxME, auxPFE, auxEFV}={0,1,2,3,4}
CreditExposure::CreditExposure(std::map<int, vector<double> > metricasNettingSet, std::map<int, pair<double, double>> probDefault, std::pair<double,double> valueLGD, Curva* curvaBase)
{
	_metricasNettingSet = metricasNettingSet;
	_probDefault = probDefault; //StopTime y first = Institución, Second = Contraparte
	_valueLGD = valueLGD; //first = Institución, Second = Contraparte
	_numStopTimes = _metricasNettingSet.size();
	spline = new Interpola(curvaBase);
}

double CreditExposure::getUnilateralCVA()
{
	double suma = 0;
	
	for (map<int, vector<double>>::iterator it = _metricasNettingSet.begin(); it != _metricasNettingSet.end(); ++it)
	{
		double time = (double)(it->first)*DT;
		spline->getIndice(time);
		double discFactor = exp(- spline->getRate() * time);
		suma = (it->second[0]) * discFactor * _probDefault[it->first].second + suma;
		//it->second[0] == vector de EE
	}
	//_probDefault.rbegin()->first
	
	double result = _valueLGD.second * suma;
	return result;
}

double CreditExposure::getCVA()
{
	double suma = 0.0;
	int i = 0;
	for (map<int, vector<double>>::iterator it = _metricasNettingSet.begin(); it != _metricasNettingSet.end(); ++it)
	{
		int StopTime = it->first;
		string nombre = "inst"; //first = Institución, Second = Contraparte
		double probStopTime = getProbDefaultAtStopTime(_probDefault, StopTime, nombre);
		double time = (double)StopTime * DT;
		spline->getIndice(time);
		double discFactor = exp(- spline->getRate() * time);
		suma = (it->second[0]) * discFactor * (1 - probStopTime)* _probDefault[StopTime].second + suma;//getExposicionEsperada()
		i++;
	}
	_valueCVA = _valueLGD.second * suma;
	return _valueCVA;
}

double CreditExposure::getDVA()
{
	double suma = 0.0;
	int i = 0;
	for (map<int, vector<double>>::iterator it = _metricasNettingSet.begin(); it != _metricasNettingSet.end(); ++it)
	{
		int StopTime = it->first;
		string nombre = "cont" ;//first = institución, Second = Contraparte
		double probStopTime = getProbDefaultAtStopTime(_probDefault, StopTime, nombre);
		double time = (double)StopTime * DT;
		spline->getIndice(time);
		double discFactor = exp(- spline->getRate() * time);
		suma = (it->second[1]) *  discFactor *(1- probStopTime)* _probDefault[StopTime].first + suma;//getExposicionNegativaEsperada()
		i++;
	}
	_valueDVA = _valueLGD.first * suma;
	return _valueDVA;
}

double CreditExposure::getBilateralCVA()
{
	double result = _valueCVA + _valueDVA;
	return result;
}

double CreditExposure::getFVA(std::map<int, pair<double, double>> spread)
{
	double suma = 0.0;
	string nombre;
	double auxTime = 0.0;
	for (map<int, vector<double>>::iterator it = _metricasNettingSet.begin(); it != _metricasNettingSet.end(); ++it)
	{
		int StopTime = it->first;
		nombre = "cont"; //first = Institución, Second = Contraparte
		double probCont = getProbDefaultAtStopTime(_probDefault, StopTime, nombre);
		nombre = "inst"; //first = Institución, Second = Contraparte
		double probInst = getProbDefaultAtStopTime(_probDefault, StopTime, nombre);	
		auxTime = ((double)StopTime - auxTime)*DT;
		double time = (double)StopTime * DT;
		spline->getIndice(time);
		double discFactor = exp(- spline->getRate() * time);
		suma = (1 - probCont)*(1 - probInst)* auxTime * discFactor * ((it->second[0])*(spread[StopTime].first) +  (it->second[1])*(spread[StopTime].second))  + suma;
		auxTime =  (double)StopTime;
	}
	double _valueFVA = suma;
	return _valueFVA;
}

double CreditExposure::getPFEMaxima()
{
	//double plazoResidual = _metricasNettingSet.rbegin()->first;
	//Para cada stopTime cálcula la maxima exposicion y posteriormente cálcula la mayor exposicion dentro de todos los stopTimes.
	vector<double> auxMaxExposure(_numStopTimes);
	int i = 0;
	for (map<int, vector<double>>::iterator it = _metricasNettingSet.begin(); it != _metricasNettingSet.end(); ++it)
	{
		//int StopTime = it->first;
		auxMaxExposure.at(i) = it->second[2];//getExposicionMaxima();
		i++;
	}
	double result = *max_element(auxMaxExposure.begin(),auxMaxExposure.end());
	auxMaxExposure.clear();
	return result;
}

double CreditExposure::getExposicionPossitivaEsperada()
{
	double suma = 0.0;
	for (map<int, vector<double>>::iterator it = _metricasNettingSet.begin(); it != _metricasNettingSet.end(); ++it)
	{
		//double StopTime = it->first;
		suma = it->second[0] + suma;//getExposicionEsperada()
	}
	double result = suma/_numStopTimes;
	return result;
}

CreditExposure::~CreditExposure(void)
{
	for (map<int, vector<double>>::iterator it = _metricasNettingSet.begin(); it != _metricasNettingSet.end(); ++it)
	{
		vector<double>().swap(it->second);	
	}
	_metricasNettingSet.clear();
	_probDefault.clear();
	if (spline != 0)
	delete spline;
}
