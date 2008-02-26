#ifndef FRMENVIO_H
#define FRMENVIO_H

#include "pform.h"

#define N_FORM_ENVIO 6

class FrmEnvio : public Form
{
public:
	FrmEnvio();
	void gravarPreferencias();
	void carregarPreferencias();
	bool event(UInt16 controlID, EventType* e);

	int numeroPedido;
protected:
	void doAfterDrawing();
};

#endif
