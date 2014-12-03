/*
DESCRIPTION Functions
*/

#ifndef LEG_FUNCTIONS_H
#define LEG_FUNCTIONS_H


#include <string>
#include <vector>


typedef std::vector<std::vector<double>> matriz;

using namespace std;


double valueLegFixScenario(Leg* leg, vector<double>& discFactors);
double valueLegFloatScenario(Leg* leg, vector<double>& discFactors, vector<double>& fixRates);
double valueLegFloatCamScenario(Leg* leg, vector<double>& discFactors, vector<double>& forwardRates, double nextInterest);
double getFixingRatesForLeg(const vector <int>& cupVigentes, const vector <int>& fixVigentes,const vector<double>& forwardRates, double nextFixingRate, vector<double>& fixingRates);
double getForwardRateFromDiscountFactors(int stopTime, const vector<int>& coupons, const vector<double>& discFactors, vector<double>& forwardRates);

#endif//
