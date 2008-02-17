#ifndef FRMPEDIDO_H
#define FRMPEDIDO_H

#include "pform.h"

class FrmPedido : public Form
{
public:
	FrmPedido();
	~FrmPedido();
	bool event(UInt16 controlID, eventsEnum evt);
	void loadData();

	Char* cliente;
};

#endif
