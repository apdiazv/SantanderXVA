//
// DESCRIPTION: 
//

#ifndef OPERATION_H
#define OPERATION_H

#include<string>
#include <utility>

using namespace std;
class Operation
{
public:
//Datos generales de la operación
	string _dealNumber;				//Numero de la op
	string _type;					//"FWD", "SWAP"
	string _pricer;					//"FX_Forward", "SWAP", "OIS"
	string _fx;						//"USDCLP", "EURUSD", ...

//Datos especificos. Todos los datos se registran en un std::pair 
//donde .first corresponde a la pata activa y .second corresponde a la pata pasiva.
	pair<double, double> _startTime;		//Tiempo inicio. Hoy es t=0
	pair<double, double> _expiryTime;		//Tiempo hasta vencimiento. Hoy es t=0.
	pair<string, string> _currency;			//Moneda de las patas "USD", "CLP", ...
	pair<double, double> _amount;			//Nocional inicial
	pair<string, string> _tipoTasa;			//Tipo de tasa "FIX", "FLOAT"
	pair<string, string> _formaTasa;		//"Lin", "Com". Indica la forma de cálculo del Wf
	pair<double, double> _valueRate;		//Valor tasa corriente
	pair<string, string> _periodicity;		//Periodicidad e.g. "3M"	
	pair<string, string> _stubPeriod;		//Periodo corto
	pair<string, string> _fixingPeriodicity;//Period. del fixing e.g. "3M"
	pair<string, string> _fixingStubPeriod;	//Periodo corto de fixing
	pair<double, double> _spread;			//Spread para tasa "FLOAT"
	pair<string, string> _amort;			//"BULLET", "FRENCH", "GERMAN", "CUSTOM"
	pair<string, string> _includeAmort;		//"YES", "NO" incluye amort
	pair<string, string> _projectCurve;		//Nombre de la curva de proyección
	pair<string, string> _discountCurve;	//Nombre de la curva de descto
	pair<double, double> _initialUF;		//Último fixing de UF

//Constructor y Destructor por default
	Operation(void);
	~Operation(void);
};
#endif