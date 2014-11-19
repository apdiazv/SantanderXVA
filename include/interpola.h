/*
DESCRIPTION Calculus of Campled Spline (Interpolations and derivatives)
*/

#ifndef INTERPOLA_H
#define INTERPOLA_H

#include <vector> 
#include <iostream>
#include "Curva.h"

using namespace std;

class Interpola
{
public:	
	Interpola(Curva* curva);
	//Leg(const Leg& copyLeg);
	Interpola(const Interpola& copyInterpola);
	Interpola();
	~Interpola();
		
	void getIndice(double t); //calculus of index for interpolations
	double getRate(); //interpolation rate
	double getDerivativeRate(); //derivative rate
	double getSecondDerivativeRate(); //second derivate rate
	

protected:

private:		
	vector<double> _coef;	//coefficients vector
	vector<double> x;		//x vector
	double _t;				//argument for interpolations
	int k;					//index
	int N;					//size of x´vector
	double r0;
	bool val;
};

#endif