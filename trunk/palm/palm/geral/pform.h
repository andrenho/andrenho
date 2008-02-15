#ifndef FORM_H
#define FORM_H

#include "palmincludes.h"
#include "pedidos.h"

class Form
{
public:
	void open();
	void load();
	virtual void event(UInt16 controlID) =0;
	virtual void loadData() =0;
	void* getControl(UInt16 id);
	void setField(UInt16 field, Char* s);
protected:
	FormType* getFormType();
	UInt16 id;
};

#endif
