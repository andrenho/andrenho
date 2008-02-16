#ifndef FORM_H
#define FORM_H

#include "palmincludes.h"
#include "pedidos.h"

class Form
{
public:
	void open();
	void load();
	void* getControl(UInt16 id);
	void setField(UInt16 field, Char* s);
protected:
	void goToForm(Form* form);
	void displayAlert(UInt16 id);
	virtual bool event(UInt16 controlID, eventsEnum evt) =0;
	virtual void loadData() =0;
	FormType* getFormType();

	UInt16 id;
private:
	bool leave_form;
};

#endif
