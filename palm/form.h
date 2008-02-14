#ifndef FORM_H
#define FORM_H

#include "palm.h"
#include "pedidos.h"

class Form
{
public:
	void open();
	virtual void event(UInt16 controlID) =0;
protected:
	UInt16 id;
};

#endif
