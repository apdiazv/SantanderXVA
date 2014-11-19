#include "headerFiles.h"
#include "theta.h"

Theta::Theta(Curva* curva, double gamma, double sigma)
{
	s = Interpola(curva);
	_gamma = gamma;
	_sigma = sigma;
	//cout <<" Constructing Theta "<< "\n";
}

double Theta::getTheta(double t)
{
	s.getIndice(t);
	double _df= 2* s.getDerivativeRate() + t * s.getSecondDerivativeRate(); 	// df = 2*dr+ t*dr2;
	double _b = (1 - exp(-2 * t * _gamma)) / (2 * _gamma);
	
	return  _df + _gamma * getInstForwardRate(t) + _b * _sigma * _sigma;
}

double Theta::getRate(double t)
{
	s.getIndice(t);
	return s.getRate();
}

double Theta::getInstForwardRate(double t)
{
	s.getIndice(t);
	double fwd = s.getRate() + t * s.getDerivativeRate();
	return fwd;
}


Theta::Theta() : _gamma(0), _sigma(0)
{

}

Theta::~Theta()
{
	_coef.clear();
	_coef.swap(vector<double> (_coef));

}

