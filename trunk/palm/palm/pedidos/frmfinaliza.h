#ifndef FRMFINALIZA_H
#define FRMFINALIZA_H

#include "pform.h"
#include "lista.h"

#define N_FORM_FINALIZA 4

class FrmFinaliza : public Form
{
public:
	FrmFinaliza();
	~FrmFinaliza();
	void inicializacao();
	bool event(UInt16 controlID, EventType* e);
	void carregarPreferencias();
	void gravarPreferencias();
	
	int numeroPedido;
	double valorPedido;
protected:
	void doAfterDrawing();
private:
	Char** s;
	Lista* l;
	void ajustaValorTotal();
	int pagtoSelecionado;
};

#endif
