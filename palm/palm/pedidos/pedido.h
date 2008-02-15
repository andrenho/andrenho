#ifndef PEDIDO_H
#define PEDIDO_H

#include "pform.h"

class Pedido : public Form
{
public:
	Pedido();
	~Pedido();
	void event(UInt16 controlID);
	void loadData();

	Char* cliente;
};

#endif
