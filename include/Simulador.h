//
// DESCRIPTION: Simulador. 
//

#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <string>
#include <utility>
#include <vector>
#include <list>
#include <map>
#include "FxRate.h"
#include "Curva.h"
#include "Rho.h"
#include "Modelo.h"


using namespace std;
typedef vector<vector<double>> matriz;
class Simulador
{
public:
	void fx(map<string, FxRate> inFx);
	FxRate getFX(string nombreFX);
	void curva(map<string, Curva> inCurva);
	Curva getCurva(string nombreCurva);
	void gamma(map<string, double> inGamma);
	double getGamma(string nombreCurva);
	void sigma(map<string, double> inSigma);
	double getSigma(string nombreFactor);
	void rho(map<string, Rho> inRho);
	Rho getRho(string nombreRho);
	void Cholesky();
	vector<double> getErrores();
	void setModels();
	struct _simulacion { //Este struct simula un registro de la BBDD
			string factor;
			int numSimulacion;
			double tiempo;
			double valor;
			};
	void runSimulacion(std::list<_simulacion> &vec_sim);
	//void runSimulacion(vector<_simulacion> &vec_sim);

	Simulador(double horizonte, unsigned long simulaciones, vector<pair<string, string>> factoresParaSimular);
	Simulador(void);
	~Simulador(void);


private:
	double _horizonte;
	unsigned long _simulaciones;
	vector<pair<string, string>> _factoresParaSimular;
	map<string, FxRate> _fx;
	map<string, Curva> _curva;
	map<string, double> _gamma;
	map<string, double> _sigma;
	map<string, Rho> _rho;
	matriz _cholesky;
	vector<Modelo*> _modelos;

};
#endif