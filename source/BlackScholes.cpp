#include "headerFiles.h"
#include "BlackScholes.h"

double BlackScholes::weakRate()
{
	return _weakRate;
}

double BlackScholes::strongRate()
{
	return _strongRate;
}

double BlackScholes::spot()
{
	return _spot;
}

BlackScholes::BlackScholes(void)
{
}

BlackScholes::BlackScholes(double spot, double weakRate, double strongRate)
{
	_spot0 = spot;
	_weakRate = weakRate;
	_strongRate = strongRate;
	_spot = _spot0;
}


void BlackScholes::initValue(double x)
{
	_spot = x;
}
	
double BlackScholes::getInitValue()
{
	return _spot;
}

double BlackScholes::simValue(double sigmasError)
{
	_spot = _spot * (1 + (_weakRate - _strongRate) * DT + sigmasError * RDT);
	return _spot;
}


void BlackScholes::resetValues()
{
	_spot = _spot0;
}


void BlackScholes::setInitialT(double t)
{
}

double BlackScholes::getDiscountFactor(double t, double T, double r)
{
	return 1.0;
}

BlackScholes::~BlackScholes(void)
{
}
