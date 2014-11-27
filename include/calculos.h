/*
DESCRIPTION Calculus functions
*/

#ifndef CALCULOS
#define CALCULOS_H

#include <map>
#include <vector>
#include <string>
#include <time.h>
#include "Rho.h"


/*
#include <utility>

#include <algorithm>
#include <cmath>
#include <sstream>
#include "FxRate.h"

#include "distributions.h"
#include "Curva.h"
#include "interpola.h"

*/

typedef std::vector<std::vector<double>> matriz;
#define DT 0.0037878787878787878787878787878787878
#define RDT 0.06154574548966636636712033006262
#define DM 22

using namespace std;

double diffclock(clock_t  clock_1, clock_t clock_2);
string integerToString(int number);
int  index(vector<double> data, double arg ); //return i, where data(i)<=arg
int  index(vector<int> data, int arg ); //return i, where data(i)<=arg
vector<double> clampedSpline(vector<double> x, vector<double> y); // coeficientes en Campled Spline
void covarianza (vector<double> sigma, matriz &rho); //matriz de covarianza
void cholesky(matriz & sigma); //matriz de Cholesky
vector<double> mmult(matriz sigma, vector<double> z);
vector<double> getErroresNoCorrelacionados(size_t n);
vector<double> getErroresNoCorrelacionados(size_t n, boost::random::mt19937 &gen);
matriz covarianza(vector<pair <string, string>> _factoresParaSimular, map<string, double> _sigma, map<string, Rho> _rho);
//double getNewTasa(double r0, double gamma, double theta, double newSigma);
//double getNewFx(double S0, double domesticRate, double foreignRate, double newSigma);
double getInterpolationRate(Curva* curva, double t);
double mean(vector<double> v);
double percentil(std::vector<double> x, double z);
double getProbDefaultAtStopTime(map<int, pair<double, double> > probDefault, double stopTime, string nombre);
int getStoppingTimeFromTime(double time);
void calendar(int startTime, int expiryTime, int period, string stubPeriod, vector<int>&times);
double amortization(string type, const vector<int>& couponTimes, double valueRate, vector<double>& percAmor);
double amortization(string type, int timeC, int expiryTime, double valueRate, int numPeriods);
double interest(string formaTasa, int t0, int t1, double valueRate, double spread);


//Interpolations.h
double qcLinInterpol(vector<double> data1, vector<double> data2, double arg, int type);//Lineal Interpolation or slope.
double qcCubicSpline(vector<double> x, vector<double> y, double arg, int type);// Cubic Spline Interpolation
double qcClampedSpline(vector<double> x, vector<double> y, double arg, int type);// Campled Spline Interpolation
double interpolations(vector<double> data1,vector<double> data2, double arg, int type);// Cubic, Clamped or Lineal interpolation depends of "type"
double derivatives(vector<double> data1,vector<double> data2, double arg, int type);// Cubic, Clamped or Lineal derivative depend on "type"
double seconderivatives(vector<double> data1,vector<double> data2, double arg, int type );// Cubic, Clamped or Lineal second derivative depend on "type"

#endif//