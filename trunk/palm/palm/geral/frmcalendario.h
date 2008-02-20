#ifndef FRMCALENDARIO_H
#define FRMCALENDARIO_H

#include "frmmodal.h"
#include "data.h"

class FrmCalendario : public FrmModal
{
public:
	FrmCalendario();
	void showDialog(void* returnValue);
protected:
	virtual bool event(UInt16 controlID, EventType* e);
};

#endif
