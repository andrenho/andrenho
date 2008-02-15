#include "pform.h"

extern Form* current;

void Form::open()
{
	FrmGotoForm(id);
	current = this;
}

void Form::load()
{
	FrmGotoForm(id);
	loadData();
	current = this;
}

FormType* Form::getFormType()
{
	return FrmGetFormPtr(this->id);
}

void* Form::getControl(UInt16 id)
{
	FormType* frm = getFormType();
	return FrmGetObjectPtr(frm, FrmGetObjectIndex(frm, id));
}
