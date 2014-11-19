#include "headerFiles.h"
#include "interpola.h"


Interpola::Interpola(const Interpola& copyInterpola)
{
	_coef = copyInterpola._coef;
	x = copyInterpola.x;
	N = copyInterpola.N;
	r0 = copyInterpola.r0;
	//cout <<" Constructing Interpola Copy "<< "\n";
}

Interpola::Interpola(Curva* curva)
{
	_coef = clampedSpline(curva->tenors, curva->rates);
	x = curva->tenors;
	N = curva->tenors.size();
	r0 = curva->rates[0];
    //cout <<" Constructing Interpola "<< "\n";
}

void Interpola::getIndice(double t)
{
	_t = t;
	if ( _t < x[0])
	{
		val = true;
	}
	else
	{
		val = false;
		k = index(x, _t);
		if (k < (N-1))
			k = k;
		else
			k = k-1;
	}
}

double Interpola::getRate()
{
	double result;
	if ( val == true )
	{
		result = r0;
	}
	else
	{
		result = _coef[k + N] + (_t - x[k]) * (_coef[k + 2 * N] + _coef[k + 3 * N] * (_t - x[k]) + _coef[k + 4 * N] * (_t - x[k]) * (_t - x[k]));
	}

	return result;
}

double Interpola::getDerivativeRate()
{
	double result;
	if ( val == true )
	{
		result = 0.0;
	}
	else
	{
		result = _coef[k + 2 * N] + 2 * _coef[k + 3 * N] * (_t - x[k]) + 3 * _coef[k + 4 * N] * (_t - x[k])*(_t - x[k]);
	}
	return result;
}
double Interpola::getSecondDerivativeRate()
{
	double result;
	if ( val == true)
	{
		result = 0.0;
	}
	else
	{
		result =  2 * _coef[k + 3 * N]  + 6 * _coef[k + 4 * N] * (_t - x[k]);
	}
	return result;
}

Interpola::Interpola()
{
	//cout <<" Constructing Interpola Void"<< "\n";
}

Interpola::~Interpola()
{
	_coef.clear();
	_coef.swap(vector<double> (_coef));
	x.clear();
	x.swap(vector<double> (x));
	//cout <<" Destructing Interpola "<< "\n";
}