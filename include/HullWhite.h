//
// DESCRIPTION Calculus Hull-White Rate (with dt=1/260).
//
#ifndef HULL_WHITE_H
#define HULL_WHITE_H

#include "Modelo.h"
#include "Theta.h"

using namespace std;
typedef std::vector<std::vector<double>> matriz;

class HullWhite: public Modelo
{
public:
	HullWhite(Curva* curva, double gamma, double sigma);
	HullWhite(const HullWhite& hw);
	HullWhite(void);
	~HullWhite(void);
	Theta* getTheta() const;
	void initValue(double x);
	double getInitValue();
	double simValue(double sigmaError);	
	void setInitialT(double t);
	void resetValues();
	double getDiscountFactor(double t,  double T, double r);
	double getGamma() const;
	double getSigma() const;
	double getR0() const;
	double getR() const;
	double getInitialT() const;
		
protected:

private:
	double _gamma;
	double _sigma;
	Theta* _theta;
	double _r;
	double  _r0;
	double _initialT;
	
};
#endif