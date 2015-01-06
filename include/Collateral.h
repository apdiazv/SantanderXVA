#pragma once
#include "Nettingset.h"

class Collateral :
	public NettingSet
{
public:
	Collateral(int lastCollateralDate, double collateralAmount);
	virtual double getCollateralAmount(double mtm, int marginDate);

	~Collateral(void);

private:
	int _nextCollateralDate;
	double _collateralAmount;
};
