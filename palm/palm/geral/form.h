#ifndef FORM_H
#define FORM_H

#include "palm.h"
#include "pedidos.h"

class Form
{
public:
	void open();
	void load();
	virtual void event(UInt16 controlID) =0;
	virtual void loadData() =0;
protected:
	FormType* getFormType();
	void* getControl(UInt16 id);
	UInt16 id;
};

#endif
