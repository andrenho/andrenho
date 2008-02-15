#ifndef BUSCACLIENTE_H
#define BUSCACLIENTE_H

#include "pform.h"

class BuscaCliente : public Form
{
public:
	BuscaCliente();
	
	void event(UInt16 controlID);
	void loadData();
};

#endif
