#ifndef FRMITENS_H
#define FRMITENS_H

#include "pform.h"

#define N_FORM_ITENS 2

class FrmItens : public Form
{
public:
	FrmItens();
	bool event(UInt16 controlID, EventType* e);
	void carregarPreferencias();
	void gravarPreferencias();

	TipoInsercao tipoInsercao;
	int numeroPedido;
protected:
	void doAfterDrawing();
private:
	void alimentaLista();

	int itemNoTopo;
};

#endif
