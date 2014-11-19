//
// DESCRIPTION: 
//

#ifndef VALORIZADOR_H
#define VALORIZADOR_H

#include <map>
#include <vector>
#include "Curva.h"
#include "Operacion.h"
#include "Operation.h"
#include "Interface.h"
#include "Forward.h"
#include "HullWhite.h"
#include "Leg.h"
#include "cppinterface.h"


using namespace std;

class Valorizador
{
public:
	static Valorizador* getInstance();
	double valorOperacion(Operacion* op);
	double valorSwap(pair<Leg, Leg>& swapLegs); 
	double valorOperacionScenario(Operation op, const vector<double>& st, vector<vector<double> >& m2m, string moneda);
	//double valorOperacionScenario(Operation op, double st, map<string, double>& sim, vector<vector<double> >& m2m, string moneda, const int auxj);
	double valorOperacionScenario(Operation op, double st, map<string, double>& sim, vector<double>& m2m, string moneda);
	double valorSwapScenario(pair<Leg, Leg>& swapLegs, const vector<double>& st, vector<vector<double> >& m2m, string moneda);
	double valorSwapScenario(pair<Leg, Leg>& swapLegs, double st, map<string, double>& sim, vector<double>& m2m, string moneda);
	~Valorizador(void);
private:
	Valorizador(void);
	static bool instanceFlag;
	static Valorizador* valor;
	map<string, Curva> storeCurvas;
	map<string, HullWhite> storeHullWhite;
	void addCurvaToStore(string nombreCurva);
	void addHullWhiteToStore(string nombreCurva);
	double valorForward(Forward* fwd);
	double valorForwardScenario(Operation op, const vector<double>& st, vector<vector<double> >& m2m, string moneda);
	//double valorForwardScenario(Operation op, double st, map<string, double>& sim, vector<vector<double> >& m2m, string moneda, const int auxj);
	double valorForwardScenario(Operation op, double st, map<string, double>& sim, vector<double>& m2m, string moneda);
	double valorLegScenario(Leg& leg, int stopTime, double discRate, double projRate, double nextFixingRate);
	double aMonedaBase(double monto, string moneda);
	double aMonedaBase(double monto, string moneda, double usdclp, double eurusd = 1, double usdjpy = 1, double clfclp = 1);
    double aMoneda(string queMoneda, double monto, string monedaMonto
		, double usdclp
		, double eurusd = 1
		, double usdjpy = 1
		, double clfclp = 1
		, double usdaud = 1
		, double usdcad = 1
		, double usdbrl = 1
		, double gbpusd = 1
		, double chfusd = 1
		, double usdmxn = 1);
};
#endif