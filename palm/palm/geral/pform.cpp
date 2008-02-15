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

void Form::setField(UInt16 field, Char* s)
{
	FieldPtr fldp;
	FieldAttrType fa;
	
	fldp = (FieldPtr)getControl(field);
	FldGetAttributes(fldp, &fa);

	/* if editable, do insert, if not, set poiner */
	if (fa.editable)
	{
		FldDelete(fldp, 0, FldGetTextLength(fldp));
		FldInsert(fldp, s, StrLen(s));
	}
	else
	{
	        //FldSetSelection(fldp, 0,0);   // no field length error if I comment this out
		FldSetTextPtr(fldp, s);
	}
	FldDrawField(fldp);
}
