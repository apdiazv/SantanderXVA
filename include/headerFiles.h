// headerFiles.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once



#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>
#include <xlw/xlw.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/math/distributions/normal.hpp>

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <map>
#include <list>
#include <cassert>
#include <time.h>

#include "sqlite3/sqlite3.h"
#include "BlackScholes.h"
#include "Curva.h"
#include "calculos.h"
#include "CreditExposure.h"
#include "distributions.h"
#include "ExposureMetrics.h"
#include "Forward.h"
#include "FxRate.h"
#include "HullWhite.h"
#include "interpola.h"
#include "Leg.h"
#include "LegFunctions.h"
#include "Modelo.h"
#include "Metrics.h"
#include "NettingSet.h"
#include "Operacion.h"
#include "Operation.h"
#include "ResultadoValorizacion.h"
#include "Rho.h"
#include "Risk.h"
#include "Simulador.h"
#include "Swap.h"
#include "theta.h"
#include "tablas.h"
#include "Valorizador.h"




/*

#include "Forward.h"
#include "Swap.h"
#include "Operacion.h"
#include "Operation.h"


#include "Valorizador.h"
#include "Simulador.h"
#include "ResultadoValorizacion.h"
#include "time.h"

#include "ExposureMetrics.h"
#include "Metrics.h"
#include "CreditExposure.h"
#include "Risk.h"
#include "NettingSet.h"
#include "Leg.h"
#include "tablas.h"

*/

// TODO: mencionar aquí los encabezados adicionales que el programa necesita