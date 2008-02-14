#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "form.h"

class Principal : public Form
{
public:
	Principal();
	void event(UInt16 controlID);
};

#endif
