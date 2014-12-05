//
// DESCRIPTION 
//

#ifndef CREDIT_EXPOSURE_H
#define CREDIT_EXPOSURE_H

#include <vector>
#include <map>
#include "interpola.h"


using namespace std;
class CreditExposure
{
public:
	CreditExposure(void);
	CreditExposure(map<int, vector<double>> metricasNettingSet
		, map<int, pair<double, double>> probDefault
		, pair<double, double> valueLGD
		, Curva* curvaBase
		);
	~CreditExposure(void);

	double getUnilateralCVA();
	double getCVA();
	double getDVA();
	double getBilateralCVA();
	double getFVA( map<int, pair<double, double>> spread);
	double getPFEMaxima();
	double getExposicionPossitivaEsperada();
	double getUnilateralDVA(); //NBacquet Sbecerra 20141205

private:
	map<int, vector<double>> _metricasNettingSet;
	map<int, pair<double, double>> _probDefault;
	pair<double, double> _valueLGD;
	size_t _numStopTimes;
	double _valueCVA;
	double _valueDVA;
	Interpola* spline;
};
#endif