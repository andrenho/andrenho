#ifndef PEDIDO_H
#define PEDIDO_H

#include "form.h"

class Pedido : public Form
{
public:
	Pedido();
	void event(UInt16 controlID);
};

#endif
