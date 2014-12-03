//
// DESCRIPTION 
//

#ifndef MODELO_H
#define MODELO_H

class Modelo
{
public:
	virtual void initValue(double x) =0;		//Inicializa la condicion inicial para simular
	virtual void setInitialT(double t) =0;		//Inicializa el tiempo de simulacion
	virtual double getInitValue() =0;			//Devuelve la condicion inicial utilizada
	virtual double simValue(double error) =0;	//Realiza un paso de simulacion	
	virtual void resetValues() =0;				//Vuelve los valores a su condicion inicial
	virtual double getDiscountFactor(double t, double T, double r) = 0;
	virtual ~Modelo(){}; // Destructor virtual
};

#endif