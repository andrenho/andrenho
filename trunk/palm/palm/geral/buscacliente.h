#ifndef BUSCACLIENTE_H
#define BUSCACLIENTE_H

#include "form.h"

class BuscaCliente : public Form
{
public:
	BuscaCliente();
	
	void event(UInt16 controlID);
	void loadData();
};

#endif
