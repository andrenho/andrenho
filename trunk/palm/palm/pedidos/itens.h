#ifndef ITENS_H
#define ITENS_H

#include "pform.h"

class Itens : public Form
{
public:
	Itens();
	bool event(UInt16 controlID, eventsEnum evt);
	void loadData();
};

#endif
