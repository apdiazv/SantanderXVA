//
// DESCRIPTION: 
//

#ifndef OPERACION_H
#define OPERACION_H

#include <string>
class Operacion
{
public:
	std::string tipo;
	void* oper;
	Operacion(void);
	~Operacion(void);
};
#endif