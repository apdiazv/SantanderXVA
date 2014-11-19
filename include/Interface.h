//
// DESCRIPTION: 
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include "headerFiles.h"

using namespace std;
using namespace xlw;

double getSimulationAtT(string curva1, string curva2, double t, map<string, double>& sim);
double getSimulationAtT(string curva1, long int t, vector<double>& sim);
std::string convertDouble(double number);
sqlite3* openDb();
int getMaxSim();
double testInsertData(double whatever);
double insertFx(CellMatrix valores);
double insertCurvas(CellMatrix valores);
double insertOperations(CellMatrix valores);
double getOperationFromDealNumber(int numero, Operacion* op);
double getCurvaFromNombre(std::string nombre, Curva* curvaOut);
double getGamma(string nombreFactor);
double getSigma(string nombreFactor);
xlw::MyArray getCurva(std::string nombre);
FxRate* getFX(std::string nombreFX);
double getNettingSetsAndStopTimes(vector<string> & nettingSets, vector<double>& stopTimes);

#endif