//
// DESCRIPTION: 
//

#ifndef NETTING_SET_H
#define NETTING_SET_H

#include <string>

using namespace std;

class NettingSet
{
public:
	NettingSet(void);
	NettingSet(const NettingSet & copyNettingSet);
	~NettingSet(void);
	NettingSet(string name, string thresholdCurrency, double thresholdInstitution, double thresholdCounterparty, int periodicity, double ajusteSobreGarantias, double minimunTransferAmount);
	//double collateral(double m2m); //este método supone que m2m viene en la divisa del threshold
	double collateral(double m2m, int stopTime);
	void setName(string name);
	string getName();
	int getPeriodicity();
	string getThresholdCurrency();
	void setThresholdCurrency(string thresholdCurrency);
	void setThresholdInstitution(double thresholdInstitution);
	void setThresholdCounterparty(double thresholdCounterparty);
	void setPeriodicity(int periodicity);
	void setCollateralAdjustment(double collateralAdjustment);
	void setMTA(double mta);
	void setLastMarginDate(int time);
	void setInitialCollateral(double collateralAmount);
	double getCollateralAdjustment();
	double getMTA();
	int getMarginDate(int stopTime); //!Dado un tiempo t, entrega el tiempo en se calcula garantia
	double collateralWithCSA(double m2m);

private:
	string _name;
	string _thresholdCurrency;
	double _thresholdInstitution;
	double _thresholdCounterparty;
	int _periodicity;
	double _collateralAdjustment;
	double _mta;
	int _lastMarginDate;
	double _initialCollateralAmount;
	int _nextMarginDate;
};
#endif