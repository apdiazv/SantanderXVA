#include "headerFiles.h"
#include "NettingSet.h"

NettingSet::NettingSet(void)
{
}

NettingSet::NettingSet(const NettingSet& copyNettingSet)
{
	_name = copyNettingSet._name;
	_thresholdCurrency = copyNettingSet._thresholdCurrency;
	_thresholdInstitution = copyNettingSet._thresholdInstitution;
	_thresholdCounterparty  = copyNettingSet._thresholdCounterparty;
	_periodicity = copyNettingSet._periodicity;
	_collateralAdjustment = copyNettingSet._collateralAdjustment;
	_mta = copyNettingSet._mta;

}

NettingSet::~NettingSet(void)
{
}

NettingSet::NettingSet(string name, string thresholdCurrency, double thresholdInstitution, double thresholdCounterparty, int periodicity, double collateralAdjustment, double mta): _name(name), _thresholdCurrency(thresholdCurrency), _thresholdInstitution(thresholdInstitution), _thresholdCounterparty(thresholdCounterparty), _periodicity(periodicity), _collateralAdjustment(collateralAdjustment), _mta(mta)
{
}

double NettingSet::collateral(double m2m)
{
	//Notar que el colateral tiene el mismo signo que el m2m
	if (m2m == 0)
	{
		return 0.0;
	}

	if (m2m < 0)
	{
		if (-m2m > _thresholdInstitution)
		{
			return m2m + _thresholdInstitution;
		}
		else
		{
			return 0.0;
		}
	}

	if (m2m > 0)
	{
		if (m2m > _thresholdCounterparty)
		{
			return m2m - _thresholdCounterparty;
		}
		else
		{
			return 0.0;
		}
	}
	return 0.0;
}

double NettingSet::collateralWithCSA(double m2m)
{
	//Notar que el colateral tiene el mismo signo que el m2m 
	if (m2m == 0)
	{
		return 0.0;
	}

	if (m2m < 0)
	{
		if (-m2m > _thresholdInstitution)
		{
			return m2m + _thresholdInstitution;
		}
		else
		{
			return 0.0;
		}
	}

	if (m2m > 0)
	{
		if (m2m > _thresholdCounterparty)
		{
			double _collateral = 0.0;
			_collateral = (m2m - _thresholdCounterparty)*(1 - _collateralAdjustment);
			//Revisar en caso de querer implementar 
			return _collateral;
		}
		else
		{
			return 0.0;
		}
	}
	return 0.0;
}





void NettingSet::setName(string name)
{
	_name = name;
}

string NettingSet::getName()
{
	return _name;
}

int NettingSet::getPeriodicity()
{
	return _periodicity;
}

string NettingSet::getThresholdCurrency()
{
	return _thresholdCurrency;
}

void NettingSet::setThresholdCurrency(string thresholdCurrency)
{
	_thresholdCurrency = thresholdCurrency;
}

void NettingSet::setThresholdInstitution(double thresholdInstitution)
{
	_thresholdInstitution = thresholdInstitution;
}

void NettingSet::setThresholdCounterparty(double thresholdCounterparty)
{
	_thresholdCounterparty = thresholdCounterparty;
}

void NettingSet::setPeriodicity(int periodicity)
{
	_periodicity = periodicity;
}



double NettingSet::getCollateralAdjustment()
{
	return _collateralAdjustment;
}

double NettingSet::getMTA()
{
	return _mta;
}

void NettingSet::setCollateralAdjustment(double collateralAdjustment)
{
	if( 0 < collateralAdjustment && collateralAdjustment < 1.0)
	{
		_collateralAdjustment = collateralAdjustment;
	}
	else
	{
		_collateralAdjustment = 0.0;
	}
}

void NettingSet::setMTA(double mta)
{
	if(mta > 0 )
	{
		_mta = mta;
	}
	else
	{
		_mta = 0;
	}

}
