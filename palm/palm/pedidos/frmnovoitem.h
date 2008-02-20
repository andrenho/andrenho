#ifndef FRM_NOVO_ITEM_H
#define FRM_NOVO_ITEM_H

#include "pform.h"

#define N_FORM_NOVO_ITEM 3

class FrmNovoItem : public Form
{
public:
	FrmNovoItem();
	~FrmNovoItem();
	bool event(UInt16 controlID, EventType* e);
	void carregarPreferencias();
	void gravarPreferencias();
	void doAfterDrawing();

	int numeroPedido;
	int numeroItem;
private:
	bool validarDados();
	void salvarDados();

	int produto;
	MemHandle hDataEntrega;
	Char* dataEntrega;
};

#endif
