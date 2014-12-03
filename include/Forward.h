//
// DESCRIPTION 
//

#ifndef FORWARD_H
#define FORWARD_H

#include <string>
class Forward
{
public:
	Forward(void);
	~Forward(void);
	long int dealNumber;
	std::string tipoInstrumento;
	std::string pricer;
	std::string fxPair;
	double montoCompra;
	std::string monedaCompra;
	double montoVenta;
	std::string monedaVenta;
	double plazoResidual;
	std::string curvaDescuentoCompra;
	std::string curvaDescuentoVenta;
};
#endif