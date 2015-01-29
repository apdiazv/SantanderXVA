//
//
//   XVA_H
//

#ifndef XVA_H
#define XVA_H


#include "headerFiles.h"

using namespace xlw;

//<xlw:libraryname=CreasysXVALibrary


double //Realiza Interpolacion: Cubic, Clamped or Lineal interpolations depend on type.
getInterpolations(MyArray data1, MyArray data2, double arg, unsigned long type
				  );

//////////////////////////////////////

double //Prueba el uso de SQLITE
testInsertData(double whatever //cualquier cosa para que parta
			   );

double //Inserta los FXa
insertFx(CellMatrix valores //El rango de FXs
		 );
CellMatrix //Inserta Fx iniciales a la BBDD
testString(CellMatrix input //Matriz de Fx iniciales
		   );

double //Inserta Curvas Cup�n Cero inciales a la BBDD
insertCurvas(CellMatrix valores //Matriz con las curvas iniciales
			 );

double //Inserta operaciones
insertOperations(CellMatrix valores //Rango con todas las operaciones
				 );

double //Inserta factores a simular
insertQueFactores(CellMatrix queFactores //Rango con los factores
				  );
/*
MyArray //Trae curva
getCurva(std::string nombre //Nombre de la curva
		 );
*/
double //Valoriza una operacion
valueFwd(int number //DealNumber de la operaci�n
		 );

double //Inserta la moneda base
insertMonedaBase(std::string monedaBase //Identificador de la moneda base
				 );

double //Inserta vectores de datos del tipo (nombre, valor) en la tabla destino
insertVector(CellMatrix valores //vector de valores
			 , std::string destino //tabla de destino
			 );

std::string getMonedaBase();

double //Inserta Horizonte y Numero de Siumulaciones
insertParamDeSimulacion(double horizonte //Horizonte de simulaci�n
						, unsigned long numSimulaciones //N�mero de simulaciones
						);

double//Hace comenzar la simulacion
startSimulation();

MyMatrix //Devuelve un numero de simulaciones de un factor
getSimulaciones(std::string factor //Factor elegido
				, int cuantasSim //Cuantas simulaciones debe devolver
				, double horizonte //Maximo plazo de las simulaciones
				);

double //Inserta la relaci�n Deal Number - Netting Set en BBDD
insertDealNumberNettingSet(CellMatrix valores //Rango de valores
						   );

double //Inserta prob. de default y tasa de recuperacion de institucion
insertInstitution(double probDefault //Probabilidad de default
				  , double recovRate //Tasa de recuperacion
				  , double spreadCap //Spread captacion
				  , double spreadCol //Spread colocacion
				  );
//double insertInstitution(double probDefault, double recovRate, double spreadCap, double spreadCol)
double insertCustomAmort(CellMatrix valores //Rango de valores
						 );

double //Comienza el proceso de valorizaci�n de los netting sets escogidos
startValorizacion(CellMatrix nettingSets //Netting Sets a valorizar
				  , MyArray stopTimes //En que tiempos vamos a valorizar
				  );

/*double //Comienza el proceso de calculo de las metricas de exposicion para los netting sets escogidos
startMetricasDeExposicion(vector<string> nettingSets //Netting Sets
						  );*/


double //Comienza el c�lculo de las  m�tricas de exposicion para los netting sets escogidos.
startMetricas(CellMatrix nettingSets //Netting Sets
			  );

double // Comienza el c�lculo del CVA y los otrs indicadores de exposici�n para los netting sets escogidos.
startExposicionCrediticia(CellMatrix nettingSets 
						  );

double //Inserta la descripci�n de los netting sets
insertNettingSets(CellMatrix valores
				  );

double //Inserta el valor del precentil a usar para las m�tricas
insertValorPercentil(double valorPercentil //Valor del percentil
					 );
MyMatrix // Devuelve un numero de valorizaciones para un netting set
getValorizaciones(string nombreNS // Netting set elegido
				  , int cuantasVal // Cuantas valorizaciones debe devolver
				  );

MyMatrix // Devuelve el valor de las metricas de exposicion para los distintos escenarios 
getMetricas(string nombreNS  // Netting set elegido
		);
double // Devuelve el factor de descuento, al tiempo t para una curva 
getDiscountFactorFromCurva(string nombreCurva // Curva elegida
						   , double t // tiempo 
						   );

MyMatrix // Devuelve el resultado de: Unilateral CVA, CVA, DVA, BilateralCVA, FVA, PFEMaxima y EPE.
getCreditExposureResults(string nombreNS  // Netting set elegido
						 );

double //Guarda los par�metros de valorizaci�n
insertParamDeValorizacion(CellMatrix nettingSets //Netting Sets a valorizar
						, MyArray stopTimes //En que tiempos vamos a valorizar
						);

double legSwaps(string nombreNS
				, MyArray stopTimes);


double startValorizacionExe();


double getValueSwapFromDealNumber(CellMatrix  dealNumber);



#endif
