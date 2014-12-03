//
// DESCRIPTION Exposure metrics
//

#ifndef EXPOSURE_METRICS_H
#define EXPOSURE_METRICS_H

#include <vector> 

using namespace std;

class ExposureMetrics
{
public:
	ExposureMetrics(void);
	ExposureMetrics(size_t simulaciones);
	~ExposureMetrics(void);

	void setNumeroSimulaciones(size_t simulaciones);
	//void setValor(const vector<double>& valoresNettingSet);
	//void setColateral(const vector<double>& amountCollateral);
	void setMtmAndColateral(const vector<double>& valoresNettingSet, const vector<double>& amountCollateral);
	void calculateExposicion();
	void claculateExposicionNegativa();
	double getValorFuturoEsperado();
	double getExposicionEsperada();
	double getExposicionNegativaEsperada();
	double getExposicionPotencialFutura(double percentil);
	double getExposicionMaxima();
	
private:
	vector<double> _valoresNettingSet;
	vector<double> _amountCollateral;
	vector<double> _exposure;
	vector<double> _negExposure;
	size_t _simulaciones;
	unsigned int count;
	unsigned int countNeg;
	bool flag;

};
#endif