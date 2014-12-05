//
// DESCRIPTION: 
//

#ifndef RISK_H
#define RISK_H

using namespace std;

struct Risk
{
	string nettingSet;
	double unilateralCVA;
	double valueCVA;
	double valueDVA;
	double bilateralCVA;
	double valueFVA;
	double pFEMax;
	double expPosExp;
	double unilateralDVA;

	Risk()	{	}
	
	Risk(string _nettingSet
		, double _unilateralCVA
		, double _valueCVA
		, double _valueDVA
		, double _bilateralCVA
		, double _valueFVA
		, double _pFEMax
		, double _expPosExp
		, double _unilateralDVA)
	{
		nettingSet = _nettingSet;
		unilateralCVA = _unilateralCVA;
		valueCVA = _valueCVA;
		valueDVA = _valueDVA;
		bilateralCVA = _bilateralCVA;
		valueFVA = _valueFVA;
		pFEMax = _pFEMax;
		expPosExp = _expPosExp;
		unilateralDVA = _unilateralDVA;
	}
};

#endif