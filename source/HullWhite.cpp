#include "headerFiles.h"
#include "HullWhite.h"

HullWhite::HullWhite(Curva* curva, double gamma, double sigma)
{
	_theta = new Theta(curva, gamma, sigma);
	_gamma = gamma;
	_sigma = sigma;
	_r0 = curva->rates[0];
	_r = _r0;
	_initialT = 0.0;	
	//cout <<" Constructing HW "<< "\n";
}

HullWhite::HullWhite(const HullWhite& hw)
{
	_gamma = hw._gamma;
	_sigma = hw._sigma;
	_r0 = hw._r0;
	_r = hw._r;
	_initialT = hw._initialT;

	_theta = new Theta();
	*_theta = *(hw._theta);
	//cout <<" Constructing HW  Copy "<< "\n";
}

double HullWhite::getGamma() const
{
	return _gamma;
}

double HullWhite::getSigma() const
{
	return _sigma;
}

double HullWhite::getR0() const
{
	return _r0;
}

double HullWhite::getR() const
{
	return _r;
}

double HullWhite::getInitialT() const
{
	return _initialT;
}

Theta* HullWhite::getTheta() const
{
	return _theta;
}

void HullWhite::setInitialT(double t)
{
	_initialT = t;
}

void HullWhite::initValue(double x)
{
	_r = x;
}


double HullWhite::getInitValue()
{
	return _r;
}


double HullWhite::simValue(double sigmaError)
{
	_r =_r + (_theta->getTheta(_initialT) - _gamma * _r) * DT+ sigmaError * RDT;
	return _r;
	
}

void HullWhite::resetValues()
{
	_r = _r0;
	_initialT = 0.0;
}

double HullWhite::getDiscountFactor(double t, double T, double r)
{
	if ( (t-T)> TOL)
		return 0;
	else
	{
		double fwd =  _theta->getInstForwardRate(t);
		double log_z = t * _theta->getRate(t) - T * _theta->getRate(T);
		//double log_z = _r0 * (t - T);
		double B = (1 - exp(- _gamma * (T - t)))/ _gamma;		
		double A = log_z + B * fwd - (_sigma * B) * (_sigma * B) * (1 - exp(- 2 * _gamma * t)) / (4 * _gamma);
		
		return exp(A - B * r);
	}
}


HullWhite::HullWhite()
{
	_r = 123; //_r0;
	//_theta = new Theta();
}

HullWhite::~HullWhite(void)
{
	if(_theta!= 0)
		delete _theta;

	//std::cout <<" Destructing HW "<< "\n";
}
