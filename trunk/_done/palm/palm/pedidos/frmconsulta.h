#ifndef FRMCONSULTA_H
#define FRMCONSULTA_H

#include "pform.h"

class FrmConsulta : public Form
{
public:
	FrmConsulta();
	bool event(UInt16 controlID, EventType* e);

	int numeroPedido;
protected:
	void doAfterDrawing();
private:
	void alimentaLista();
	int itemNoTopo;
};

#endif

