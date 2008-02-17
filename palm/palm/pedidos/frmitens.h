#ifndef FRMITENS_H
#define FRMITENS_H

#include "pform.h"

class FrmItens : public Form
{
public:
	FrmItens();
	bool event(UInt16 controlID, eventsEnum evt);
	void loadData();
};

#endif
