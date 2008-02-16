#ifndef PEDIDO_H
#define PEDIDO_H

#include "pform.h"

class Pedido : public Form
{
public:
	Pedido();
	~Pedido();
	bool event(UInt16 controlID, eventsEnum evt);
	void loadData();

	Char* cliente;
};

#endif
