//
// DESCRIPTION Calculus of Theta in Hull-White model with Campled Spline Interpolations.
//

#ifndef THETA_H
#define THETA_H

#include <vector>
#include "Curva.h"
#include "interpola.h"

using namespace std;

class Theta
{
public:
	Theta(Curva* curva, double gamma, double sigma);
	Theta();
	~Theta();
	double getRate(double t);				//r(0,t)
	double getInstForwardRate(double t);	//f(0,t)
	double getTheta(double t);				//theta in Hull-White mod
	

protected:

private:
	vector<double> _coef;	//coefficients vectors
	double _gamma;			//gamma factor in Hull-White model
	double _sigma;			//volatility in Hull-White model
	Interpola s;	
};

#endif