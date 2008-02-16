#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "pform.h"

class Principal : public Form
{
public:
	Principal();
	bool event(UInt16 controlID, eventsEnum evt);
	void loadData();
};

#endif
