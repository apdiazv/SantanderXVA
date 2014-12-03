//
// DESCRIPTION: Expositions Metrics. 
//

#ifndef METRICS_H
#define METRICS_H

#include <string>

struct Metrics
{
	string nettingSet;
	int stopTime;
	double expExp;
	double negExpExp;
	double maxExp;
	double potFutExp;
	double expFutVal;

	Metrics()	{	}
	
	Metrics(string _nettingSet, int _stopTime, double _expExp, double _negExpExp, double _maxExp, double _potFutExp, double _expFutVal)
	{
		nettingSet = _nettingSet;
		stopTime = _stopTime;
		expExp = _expExp;
		negExpExp = _negExpExp;
		maxExp = _maxExp;
		potFutExp = _potFutExp;// Asociar Percentil;
		expFutVal = _expFutVal;
	}
};

#endif
