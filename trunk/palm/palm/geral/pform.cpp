#include "pform.h"

extern Form* current;

void Form::open()
{
	UInt16 err;
	EventType e;

	this->leave_form = false;
	FrmGotoForm(this->id);

	while(!this->leave_form)
	{
		EvtGetEvent(&e, 100);
		if (SysHandleEvent(&e))
			continue;
		if (MenuHandleEvent(NULL, &e, &err))
			continue;

		switch(e.eType)
		{
			case frmLoadEvent:
				FrmSetActiveForm(FrmInitForm(e.data.frmLoad.formID));
				break;
			case frmOpenEvent:
				FrmDrawForm(getFormType());
				break;
			case appStopEvent:
				this->leave_form = true; // TODO
				break;
			default:
				event(e.data.ctlSelect.controlID);
				if (FrmGetActiveForm())
					FrmHandleEvent(FrmGetActiveForm(), &e);
				break;
		}
	}
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
