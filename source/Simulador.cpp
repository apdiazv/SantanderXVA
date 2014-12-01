#include "headerFiles.h"
#include "Simulador.h"

void Simulador::fx(map<string, FxRate> inFx)
{
	_fx = inFx;
}

FxRate Simulador::getFX(string nombreFX)
{
	return _fx[nombreFX];
}
void Simulador::curva(map<string, Curva> inCurva)
{
	_curva = inCurva;
}

Curva Simulador::getCurva(string nombreCurva)
{
	return _curva[nombreCurva];
}

void Simulador::gamma(map<string, double> inGamma)
{
	_gamma = inGamma;
}

double Simulador::getGamma(string nombreCurva)
{
	return _gamma[nombreCurva];
}


void Simulador::sigma(map<string, double> inSigma)
{
	_sigma = inSigma;
}

double Simulador::getSigma(string nombreFactor)
{
	return _sigma[nombreFactor];
}

void Simulador::rho(map<string, Rho> inRho)
{
	_rho = inRho;
}

Rho Simulador::getRho(string nombreRho)
{
	return _rho[nombreRho];
}

void Simulador::getSeed(long seed)
{
	gen.seed(seed);
}

void Simulador::Cholesky()
{
	_cholesky = covarianza(_factoresParaSimular, _sigma, _rho);
	//_rho.erase(_rho.begin(), _rho.end());
	cholesky(_cholesky);
}


vector<double> Simulador::getErrores()
{
	//Esta linea se debe descomentar para volver a utiizar el rand de c++
	//return mmult(_cholesky, getErroresNoCorrelacionados(_cholesky.size()));
	return mmult(_cholesky, getErroresNoCorrelacionados(_cholesky.size(), gen));
}

void Simulador::setModels()
{
    _modelos.reserve(_factoresParaSimular.size());
	for (unsigned int i = 0; i < _factoresParaSimular.size(); i++)
	{
		if (_factoresParaSimular[i].second == "FX")
		{
			FxRate* fxAux = new FxRate;
			*fxAux = getFX(_factoresParaSimular[i].first);
			Curva* curvaAux = new Curva;
			*curvaAux = getCurva(fxAux->curvaDebil());
			double weakRate = getInterpolationRate(curvaAux, _horizonte); //en vez de sacar el punto más corto hay que
			*curvaAux = getCurva(fxAux->curvaFuerte());
			double strongRate = getInterpolationRate(curvaAux, _horizonte); //sacar la tasa al plazo de la simulación
			_modelos.push_back(new BlackScholes(fxAux->valor(), weakRate, strongRate));
			delete fxAux;
			delete curvaAux;
		}
		else if (_factoresParaSimular[i].second == "IR")
		{
			string auxStr = _factoresParaSimular[i].first;
			_modelos.push_back(new HullWhite(&getCurva(auxStr), getGamma(auxStr), getSigma(auxStr)));
		}
	}

	return;
}


//void Simulador::runSimulacion(vector<_simulacion> &vec_sim)
void Simulador::runSimulacion(std::list<_simulacion> &vec_sim)
{
	unsigned  nPasos = (unsigned int)ceil(_horizonte / DT) + 1;
	vector<double> alea;
	_simulacion temp_sim;
	
	for (unsigned int k = 0; k < _simulaciones; k++)
	{
		temp_sim.numSimulacion = k;

		for (unsigned int j = 0; j <_factoresParaSimular.size(); j++) //Condiciones iniciales
		{
			double x = _modelos[j]->getInitValue(); //sacar el valor inicial y guardarlo en temp
			temp_sim.factor = _factoresParaSimular[j].first;
			temp_sim.tiempo = 0;
			temp_sim.valor = x;	
			int aux_cont = j + k * (_factoresParaSimular.size() * nPasos);
			//vec_sim(aux_cont) = temp_sim;
			vec_sim.push_back(temp_sim);		
		}
				
		for (unsigned int i = 1; i < nPasos; i++)
		{
			alea = getErrores();
			for (unsigned int j = 0; j <_factoresParaSimular.size(); j++)
			{
				double x = _modelos[j]->simValue(alea[j]);
				temp_sim.factor = _factoresParaSimular[j].first;
				temp_sim.tiempo = i;
				temp_sim.valor = x;
				int aux_cont = j + k * (_factoresParaSimular.size() * nPasos) + i * _factoresParaSimular.size();
				//vec_sim.at(aux_cont) = temp_sim;
				vec_sim.push_back(temp_sim);
				_modelos[j]->initValue(x);
				_modelos[j]->setInitialT(i*DT);
					
			}
		}

		for (unsigned int j = 0; j <_factoresParaSimular.size(); j++)
		{
			_modelos[j]->resetValues(); //volver al inicio los valores
		}
	}
	alea.clear();
	//testDiscountFactor.clear();
	return ;//vec_sim;
}



Simulador::Simulador(double horizonte, unsigned long simulaciones, vector<pair<string, string>> factoresParaSimular)
{
	_horizonte = horizonte;
	_simulaciones = simulaciones;
	_factoresParaSimular = factoresParaSimular;
}



Simulador::Simulador(void)
{
}

Simulador::~Simulador(void)
{
	_fx.clear();
	_curva.clear();
	_gamma.clear();
	_sigma.clear();
	_rho.clear();
	_cholesky.clear(); 
	while(!_modelos.empty()) delete _modelos.back(), _modelos.pop_back();

	_factoresParaSimular.clear();
}
