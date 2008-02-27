#ifndef BUSCAPRODUTO_H
#define BUSCAPRODUTO_H

#include "frmmodal.h"
#include "palmincludes.h"
#include "segment.h"

class BuscaProduto : public FrmModal
{
public:
	BuscaProduto() GERAL;
	int busca(Form* caller, UInt16 referncia, UInt16 descricao) GERAL;
protected:
	bool event(UInt16 controlID, EventType *e) GERAL;
};

#endif
