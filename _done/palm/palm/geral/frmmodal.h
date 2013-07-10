#ifndef FRMMODAL_H
#define FRMMODAL_H

#include "pform.h"

class FrmModal : public Form
{
public:
	virtual void showDialog(void* returnValue) GERAL;
protected:
	virtual bool event(UInt16 controlID, EventType* e) =0;
	void* returnValue;
};

#endif
