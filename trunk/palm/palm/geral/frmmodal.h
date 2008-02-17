#ifndef FRMMODAL_H
#define FRMMODAL_H

#include "pform.h"

class FrmModal : public Form
{
public:
	void* showDialog();
	virtual bool event(UInt16 controlID, eventsEnum evt) =0;
	virtual void loadData() =0;
protected:
	void* returnValue;
};

#endif
