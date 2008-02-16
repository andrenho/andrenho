#ifndef BUSCACLIENTE_H
#define BUSCACLIENTE_H

#include "pform.h"
#include "palmincludes.h"

class BuscaCliente : public Form
{
public:
	BuscaCliente();
	
	bool event(UInt16 controlID, eventsEnum evt);
	void loadData();
	void busca(Form* caller, UInt16 CNPJ, UInt16 campoFantasia, UInt16 campoRazaoSocial);
};

#endif
