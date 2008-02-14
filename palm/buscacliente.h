#ifndef BUSCACLIENTE_H
#define BUSCACLIENTE_H

#include "form.h"

class BuscaCliente : public Form
{
public:
	BuscaCliente();
	
	Char* busca(UInt16 textBox);
	void event(UInt16 controlID);
	void loadData();

private:
	bool clienteExiste(Char* cliente);
};

#endif
