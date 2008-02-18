#ifndef FRMPRINCIPAL_H
#define FRMPRINCIPAL_H

#include "pform.h"

class FrmPrincipal : public Form
{
public:
	FrmPrincipal();
	bool event(UInt16 controlID, EventType* e);
};

#endif
