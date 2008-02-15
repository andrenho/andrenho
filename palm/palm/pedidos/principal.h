#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "pform.h"

class Principal : public Form
{
public:
	Principal();
	void event(UInt16 controlID);
	void loadData();
};

#endif
