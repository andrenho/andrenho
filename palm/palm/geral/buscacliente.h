#ifndef BUSCACLIENTE_H
#define BUSCACLIENTE_H

#include "frmmodal.h"
#include "palmincludes.h"
#include "segment.h"

class BuscaCliente : public FrmModal
{
public:
	BuscaCliente() GERAL;
	bool busca(Form* caller, UInt16 CNPJ, UInt16 campoFantasia, UInt16 campoRazaoSocial, int cidade) GERAL;
protected:
	bool event(UInt16 controlID, EventType *e) GERAL;
};

#endif
