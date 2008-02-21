#ifndef FRMFINALIZA_H
#define FRMFINALIZA_H

#include "pform.h"

#define N_FORM_FINALIZA 4

class FrmFinaliza : public Form
{
public:
	FrmFinaliza();
	bool event(UInt16 controlID, EventType* e);
	void carregarPreferencias();
	void gravarPreferencias();
	
	int numeroPedido;
	double valorPedido;
protected:
	void doAfterDrawing();
private:
	void ajustaValorTotal();
};

#endif
