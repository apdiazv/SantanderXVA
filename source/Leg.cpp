#include "headerFiles.h"
#include "Leg.h"

Leg::Leg(void)
{
}

Leg::Leg(const Leg& copyLeg)
{
	tipoPata = copyLeg.tipoPata;
	_amount = copyLeg._amount;
	_currency = copyLeg._currency;
	_includeAmort = copyLeg._includeAmort;
	
	couponTimes = copyLeg.couponTimes;
	cupVigentes = copyLeg.cupVigentes;
	percAmor = copyLeg.percAmor;	
	//amorVigentes = copyLeg.amorVigentes;
	fixingTimes = copyLeg.fixingTimes;
	fixVigentes = copyLeg.fixVigentes;
	
	_formaTasa = copyLeg._formaTasa;
	_valueRate = copyLeg._valueRate;	
	_spread = copyLeg._spread;
	flagProj = copyLeg.flagProj;
	flagFixing = copyLeg.flagFixing;
	flagPeriod = copyLeg.flagPeriod;

	_lastFixing = copyLeg._lastFixing;
	_nextFixing = copyLeg._nextFixing;
	
	_projectCurve = copyLeg._projectCurve;
	_discountCurve = copyLeg._discountCurve;
	
}

Leg::Leg(std::string tipoTasa)
{
	assert( tipoTasa == "FIX" || tipoTasa == "FLOAT" || tipoTasa == "FLOATCAM");
	tipoPata = tipoTasa;
}


Leg::~Leg(void)
{
	couponTimes.clear();
	percAmor.clear();
	fixingTimes.clear();
	cupVigentes.clear();
	amorVigentes.clear();
	fixVigentes.clear();
}


void Leg::setNotionalAmount(double amount, std::string currency)
{
	_amount = amount;
	_currency = currency;
}

void Leg::setPricingParameters(string projectCurve, string discountCurve, std::string includeAmort)
{
	_discountCurve = discountCurve;
	flagProj = true;
	_includeAmort = "Si";
	if (includeAmort == "No")
	{
		_includeAmort = includeAmort;
	}
	if( projectCurve != "" &&  projectCurve != discountCurve)
	{
		_projectCurve = projectCurve;
		flagProj = false;
	}
	else
	{
		_projectCurve = _discountCurve;
		if(!flagPeriod)
		{
			flagProj = false;
		}
	}
}

void Leg::setCalendars(double startTime, double expiryTime, string periodicity, string stubPeriod, string fixingPeriodicity, string fixingStubPeriod)
{
	int _startTime = getStoppingTimeFromTime(startTime);
	int _expiryTime = getStoppingTimeFromTime(expiryTime);
	string _stubPeriod = stubPeriod;
	string _fixingStubPeriod = _stubPeriod;
	int aux = atoi(periodicity.c_str());
	assert(aux > 0 && aux < 13);
	int _period = aux;
	int _fixingPeriod = _period;
	flagPeriod = true;

	if(tipoPata != "FIX")
	{
		if( fixingStubPeriod != "" || fixingPeriodicity!= "")
		{
			_fixingStubPeriod = fixingStubPeriod;
			aux = atoi(fixingPeriodicity.c_str());
			assert(aux > 0 && aux < 13);
			_fixingPeriod = aux;		
			if( _fixingStubPeriod != _stubPeriod || _fixingPeriod != _period)
			{
				flagPeriod  = false;
			}
		}
	}
	vector<int> timesC;
	//  Un StubPeriod  corto acepta un periodo un poco más largo pero no al revés.
	//  StubPeriod Default == CortoAlInicio
	calendar(_startTime, _expiryTime,  _period * DM, _stubPeriod, timesC);
	couponTimes.assign(timesC.begin(), timesC.end());
	timesC.clear();
	
	if (!flagPeriod)
	{
		calendar(_startTime, _expiryTime,  _fixingPeriod* DM, _fixingStubPeriod, fixingTimes);
	}
	else if(tipoPata != "FIX")
	{		
		fixingTimes.assign(couponTimes.begin(), couponTimes.end());	
	}
    //En el caso FIX el vector de fixing es vacío
}

void Leg::setCalendarAmortize(string amort)
{
	//assert(amort == "BULLET" || amort == "FRENCH" || amort == "GERMAN" || amort == "CUSTOM")
	//double _valueRate = 0.0;
	unsigned int _nCoupons = couponTimes.size();
	double cuota;
	percAmor.assign(_nCoupons, 0.0);
	//La primera amortizaciÛn siempre es cero porque =couponTimes[0] = startTime;
	if (amort == "BULLET")
	{
		percAmor.at(_nCoupons - 1) = 1;
	}
	else if (amort == "GERMAN")
	{
		for (unsigned int i = 1; i < _nCoupons; i++)
		{
			percAmor.at(i) = 1.0 / (_nCoupons - 1);
		}
	}
	else if (amort == "FRENCH")
	{
		double aux1 = 0.0;
		for (unsigned int i = 1; i < _nCoupons; i++)
		{
			if (_formaTasa == "Lin")
			{
				double yf = (couponTimes.at(i) - couponTimes.at(0)) * DT;
				aux1 = aux1 + 1/(1 + _valueRate * yf);
			}
			else
			{
				double yf = (couponTimes.at(i) - couponTimes.at(0)) * DT;
				aux1 = aux1 + pow((1 + _valueRate), -yf);
			}
		}
		cuota = 1 / aux1;
		aux1 = 1.0;
		//}
		for (unsigned int i = 1; i < _nCoupons; i++)
		{
			if (_formaTasa == "Lin")
			{
				double yf = (couponTimes.at(i) - couponTimes.at(i-1)) * DT;
				double interest = aux1 * _valueRate * yf;
				percAmor.at(i) = cuota - interest;
				aux1 = aux1 - percAmor.at(i);
			}
			else
			{
				double yf = (couponTimes.at(i) - couponTimes.at(i-1)) * DT;
				double interest = aux1 * (pow((1 + _valueRate), yf) - 1);
				percAmor.at(i) = cuota - interest;
				aux1 = aux1 - percAmor.at(i);
			}
		}
	}
	else
	{
		percAmor.at(_nCoupons - 1) = 1;
	}
}



void Leg::setCalendarAmortize(vector<double> customAmort)
{
	if(!customAmort.empty() && customAmort.size() == couponTimes.size())
	{
		percAmor = customAmort;
	}
	else
	{
		percAmor.assign(couponTimes.size(), 0.0);
	}

}

void Leg::setInterest(string formaTasa,double valueRate, double spread)
{
	_formaTasa = formaTasa;
	_valueRate = valueRate;
	_spread = spread;
	// Si la Pata es fija, se cálcula inmediatamente  un vector de intereses.
	// El primer valor siempre es 0.0.
	if( tipoPata == "FIX")
	{
		fixInterest.assign(couponTimes.size(), 0.0);
		for (unsigned int i = 1; i < couponTimes.size(); i++)
		{
			fixInterest.at(i) = interest(_formaTasa, couponTimes[i-1], couponTimes[i], _valueRate, 0.0);
		}
	}
}


void Leg::initiateCalendars()
{
	flagFixing = false;
	// Corregido el 05/11/14: Cambio de 0 a 1, para eliminar el flujo vencido a tiempo 0.
	unsigned int k =  (unsigned int) index(couponTimes, 1);
	if (0 <= k && k < couponTimes.size())
	{
		cupVigentes.assign(couponTimes.begin()+k, couponTimes.end());
		//amorVigentes.assign(percAmor.begin()+k, percAmor.end());
		if(!fixingTimes.empty())
		{
			if(flagPeriod)
			{
				fixVigentes.assign(fixingTimes.begin()+k, fixingTimes.end());
				_nextFixing = cupVigentes[1];
				_lastFixing = cupVigentes[0];
				
			}
			else
			{
				k =  index(fixingTimes, 1);// Cambiado a 1, para eliminar el flujo vencido a tiempo 0
				fixVigentes.assign(fixingTimes.begin()+k, fixingTimes.end());
				_nextFixing = fixingTimes[k+1];
				_lastFixing = fixingTimes[k];
			}
		}
	}
}

void Leg::resetCalendars(int stopTime)
{
	if(!cupVigentes.empty())
	{
		if(stopTime <= cupVigentes.back())
		{
			int k =  index(cupVigentes, stopTime + 1);// Cambiado a stopTime+1, para eliminar el flujo vencido a tiempo stopTime
			if (0 < k)
			{
				cupVigentes.erase(cupVigentes.begin(), cupVigentes.begin()+k);
				if( !fixingTimes.empty())
				{
					if(flagPeriod)
					{
						fixVigentes.erase(fixVigentes.begin(), fixVigentes.begin()+k);
						_lastFixing = cupVigentes[0];
					}
					else
					{
						k = index(fixVigentes, cupVigentes[1]);// No se hace cambio
						fixVigentes.erase(fixVigentes.begin(), fixVigentes.begin()+k);
						_lastFixing = fixVigentes[0];						
					}
				} 
			}
		}				
		else
		{
			cupVigentes.erase(cupVigentes.begin(), cupVigentes.end());			
		}
	}
}

vector<int> Leg::getCalendarCoupon()
{
	return cupVigentes;
}

vector<int> Leg::getCalendarFixing()
{
	//assert(!fixVigentes.empty());
	return fixVigentes;
}

int Leg::getLastFixing()
{
	return _lastFixing;
}


int Leg::getNextFixing()
{
	return _nextFixing;
}

double Leg::getAmortize(int coupon)
{
	double auxPerc = 0.0;
	if(!percAmor.empty() && !couponTimes.empty())
	{
		std::vector<int>::iterator it;
		it = find(couponTimes.begin(), couponTimes.end(), coupon);
		int k = it - couponTimes.begin();
		auxPerc = percAmor[k];
	}
	double amorVigente = _amount * auxPerc;
	return amorVigente;
}


double Leg::getInterest(int coupon0, int coupon1, double valueRate)
{
	double result = 0.0;
	if( tipoPata == "FIX")
	{
		std::vector<int>::iterator it;
		it = find(couponTimes.begin(), couponTimes.end(), coupon1);
		int k = it - couponTimes.begin();
		result = fixInterest[k];
	}
	else
	{
		result = interest(_formaTasa, coupon0, coupon1, valueRate, _spread);
	}
	return result;
}

bool Leg::getFlagFixing(void)
{
	if(tipoPata != "FIX")
	{
		if( _lastFixing >= _nextFixing)
		{
			//1er Fixing variable: Se debe calcular de las simulaciones
			flagFixing = true;
		}
		//Caso contrario _valueRate es el valor del proximo fixing. 
	}
	 return flagFixing;
}
 
bool Leg::getFlagProj()
{
	return flagProj;
}

void Leg::resetAmount(void)
{
	double aux1 = 1.0;
	if(!percAmor.empty() && !cupVigentes.empty())
	{
		std::vector<int>::iterator it;
		it = find(couponTimes.begin(), couponTimes.end(), cupVigentes[0]);
		unsigned nAmorts = it - couponTimes.begin();
		for (unsigned int i = 1; i <= nAmorts; i++)
		{
			aux1 = aux1 - percAmor[i];
		}
	}
	notVigente = _amount * aux1;
}
double Leg::getAmount(void)
{
	return notVigente;
}

string Leg::getCurrency(void)
{
	return _currency;
}

string Leg::getDiscountCurve(void)
{
	return _discountCurve;
}

string Leg::getProjectCurve(void)
{
	return _projectCurve;
}

string Leg::getIncludeAmort(void)
{
	return  _includeAmort;
}

double Leg::getValueRate(void)
{
	return  _valueRate;
}