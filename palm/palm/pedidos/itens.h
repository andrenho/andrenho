#ifndef ITENS_H
#define ITENS_H

#include "form.h"

class Itens : public Form
{
public:
	Itens();
	void event(UInt16 controlID);
	void loadData();
};

#endif
