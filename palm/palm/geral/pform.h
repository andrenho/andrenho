#ifndef FORM_H
#define FORM_H

#include "palmincludes.h"
#include "pedidos.h"

class Form
{
public:
	void open();
	void load();
	virtual void loadData() =0;
	void* getControl(UInt16 id);
	void setField(UInt16 field, Char* s);
protected:
	virtual void event(UInt16 controlID) =0;
	FormType* getFormType();
	UInt16 id;
	bool leave_form;
};

#endif
