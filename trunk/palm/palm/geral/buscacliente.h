#ifndef BUSCACLIENTE_H
#define BUSCACLIENTE_H

#include "frmmodal.h"
#include "palmincludes.h"

class BuscaCliente : public FrmModal
{
public:
	BuscaCliente();
	
	bool event(UInt16 controlID, EventType *e);
	bool busca(Form* caller, UInt16 CNPJ, UInt16 campoFantasia, UInt16 campoRazaoSocial, int cidade);
};

#endif
