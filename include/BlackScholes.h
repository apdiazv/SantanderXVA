
//
// DESCRIPTION Calculus Black-Scholes FxRate (whit dt=1/260)
//

#ifndef BLACK_SHOLES_H
#define BLACK_SHOLES_H

#include "Modelo.h"

class BlackScholes: public Modelo
{
public:
	double weakRate();
	double strongRate();
	double spot();
	BlackScholes(void);
	BlackScholes(double spot, double weakRate, double strongRate);
	~BlackScholes(void);
	void initValue(double x);
	double getInitValue();
	double simValue(double sigmasError);
	void setInitialT(double t);
	void resetValues();
	double getDiscountFactor(double t, double T, double r);

private:
	double _weakRate;
	double _strongRate;
	double _spot;
	double _spot0;
};

#endif