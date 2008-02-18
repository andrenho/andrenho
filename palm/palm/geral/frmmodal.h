#ifndef FRMMODAL_H
#define FRMMODAL_H

#include "pform.h"

class FrmModal : public Form
{
public:
	void* showDialog();
	virtual bool event(UInt16 controlID, EventType* e) =0;
protected:
	void* returnValue;
};

#endif
