//
// DESCRIPTION 
//

#ifndef LEG_H
#define LEG_H

#include <string>
#include <vector>


using namespace std;

class Leg
{
public:
// Constructor y Destructor por default
	Leg(void);
	Leg(const Leg& copyLeg);
	Leg(string tipoTasa);
	~Leg(void);

    void setNotionalAmount(double amount, string currency);
	void setCalendars(double startTime, double expiryTime, string periodicity, string stubPeriod, string fixingPeriodicity, string fixingStubPeriod);
	void setCalendarAmortize(string amort);
	void setCalendarAmortize(vector<double> customAmort);
	void setInterest(string formaTasa, double valueRate, double spread);
	void setPricingParameters(string projectCurve, string discountCurve, string includeAmort);	
	vector<int> getCalendarCoupon();
	vector<int> getCalendarFixing();
	int getLastFixing();
	int getNextFixing();
	double getAmortize(int coupon);
	double getInterest(int coupon0, int coupon1, double valueRate);
	void resetCalendars(int stopTime);
	void resetAmount();
	void initiateCalendars();
	bool getFlagFixing(void);
	bool getFlagProj(void);
	double getAmount(void);
	string getCurrency(void);
	string getDiscountCurve(void);
	string getProjectCurve(void);
	string getIncludeAmort(void);	
	double getValueRate(void);
	
	
	string tipoPata;
	
private:
	//Datos especificos de cada pata. 
	//Según el tipo de tasa "FIX", "FLOAT"
	vector<int> couponTimes;
	vector<int> fixingTimes;
	vector<double> percAmor;
	vector<int> cupVigentes;
	vector<double> amorVigentes;
	vector<int> fixVigentes;
	//Interes	
	vector<double> fixInterest; 
	int _nextFixing;
	int _lastFixing;
	bool flagProj;
	bool flagPeriod;
	bool flagFixing;
	string _formaTasa;		//"Lin", "Com". Indica la forma de cálculo del Wf
	double _spread;         //Spread para tasa "FLOAT"
	double _amount;
	string _currency;
	string _discountCurve;
	string _projectCurve;
	string _includeAmort;	//"Si", "No" incluye amort	
	double _valueRate;		//Valor tasa corriente
	double notVigente;
};
#endif