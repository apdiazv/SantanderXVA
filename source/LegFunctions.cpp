#include "headerFiles.h"
#include "LegFunctions.h"

double valueLegFixScenario(Leg* leg, vector<double>& discFactors)
{
	size_t numCoupons = discFactors.size();
	double result = 0.0;
	vector <int> cupVigentes(leg->getCalendarCoupon());
	double notVig = leg->getAmount();
	for (unsigned int i = 1; i < numCoupons; i++)
	{
		double interest = notVig *(leg->getInterest(cupVigentes[i-1], cupVigentes[i], 0.0));
		double amort = leg->getAmortize(cupVigentes[i]);
		double cashflow = interest;
		if (leg->getIncludeAmort() == "Si")
		{
			cashflow = cashflow + amort;
		}
        result = result + cashflow * discFactors[i];
		notVig = notVig - amort;		
	}
	return result;		
}

double valueLegFloatScenario(Leg* leg, vector<double>& discFactors, vector<double>& fixRates)
{
	size_t numCoupons = discFactors.size();
	double result = 0.0;
	vector <int> cupVigentes(leg->getCalendarCoupon());
	double notVig = leg->getAmount();
	for (unsigned int i = 1; i < numCoupons; i++)
	{
		double interest = notVig *(leg->getInterest(cupVigentes[i-1], cupVigentes[i], fixRates[i]));
		double amort = leg->getAmortize(cupVigentes[i]);
		double cashflow = interest;
		if (leg->getIncludeAmort() == "Si")
		{
			cashflow = cashflow + amort;
		}
        result = result + cashflow * discFactors[i];
		notVig = notVig - amort;		
	}
	return result;
}

double valueLegFloatCamScenario(Leg* leg, vector<double>& discFactors, vector<double>& forwardRates, double nextInterest)
{
	size_t numCoupons = discFactors.size()-1;
	double result = 0.0;
	vector <int> cupVigentes(leg->getCalendarCoupon());
	double notVig = leg->getAmount();
	//vector <double> aux(numCoupons, 0.0);
	//Corregido el 29/09
	double interest = nextInterest;
	double amort = leg->getAmortize(cupVigentes[1]);
	for (unsigned int i = 1; i < numCoupons; i++)
	{
		double cashflow = interest;
		if (leg->getIncludeAmort() == "Si")
		{
			cashflow = cashflow + amort;
		}
        result = result + cashflow * discFactors[i];
		notVig = notVig - amort;
		interest = notVig * (leg->getInterest(cupVigentes[i], cupVigentes[i+1], forwardRates[i+1]));
		amort = leg->getAmortize(cupVigentes[i+1]);
	}
	double cashflow = interest;
	if (leg->getIncludeAmort() == "Si")
	{
		cashflow = cashflow + amort;
	}
    result = result + cashflow * discFactors[numCoupons];

	return result;
}





double getForwardRateFromDiscountFactors(int stopTime, const vector<int>& coupons, const vector<double>& discFactors, vector<double>& forwardRates)
{
	size_t numCoupons = discFactors.size();
	// Cambio Realizado el 30/10/2014.
	int auxTime = stopTime;
	for (unsigned int i = 1; i < numCoupons; i++)
	{
		double deltaT = (coupons[i]- auxTime)*DT;
		forwardRates.at(i) = (discFactors[i-1]/discFactors[i]-1)/ deltaT;
		auxTime = coupons[i];
	}
	return 0.0;
}

double getFixingRatesForLeg(const vector <int>& cupVigentes, const vector <int>& fixVigentes,const vector<double>& forwardRates, double nextFixingRate, vector<double>& fixingRates)
{
	fixingRates.resize(cupVigentes.size());
	unsigned int i = 1;
	while ((i < cupVigentes.size()) && (cupVigentes[i] <= fixVigentes[1]))
	{
		fixingRates.at(i) = nextFixingRate;				
		i++;		
	}
		
	for (unsigned int j = 2; j < fixVigentes.size(); j++)
	{
		while ((i < cupVigentes.size()) && (cupVigentes[i] <= fixVigentes[j]))
		{
			fixingRates.at(i) = forwardRates[j];				
			i++;
		}
	}
	return 0.0;
}