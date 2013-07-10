#include "pform.h"
#include "aplicativo.h"
#include "util.h"

Form::Form()
{
	carregaPreferencias = false;
}

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
				FrmSetActiveForm(FrmInitForm(this->id));
				break;
			case frmOpenEvent:
				FrmDrawForm(getFormType());
				doAfterDrawing();
				break;
			case appStopEvent:
				app->appActive = false;
				return;
			default:
				if(!event(e.data.ctlSelect.controlID, &e))
					FrmDispatchEvent(&e);
				break;
		}
	}
}

void Form::doAfterDrawing()
{
	if(carregaPreferencias)
		carregarPreferencias();
}

void Form::goToForm(Form* form)
{
	this->leave_form = true;
	app->current = form;
}
	
void Form::displayAlert(UInt16 id)
{
	FrmAlert(id);
}

void Form::mensagemErro(Char* message)
{
	FrmCustomAlert(MensagemErro, message, " ", " ");
}

bool Form::perguntaSimNao(Char* mensagem)
{
	return FrmCustomAlert(PerguntaSimNao, mensagem, " ", " ") == 0 ? true : false;
}

bool Form::perguntaAvisoSimNao(Char* mensagem)
{
	return FrmCustomAlert(PerguntaAvisoSimNao, mensagem, " ", " ") == 0 ? true : false;
}

FormType* Form::getFormType()
{
	return FrmGetFormPtr(this->id);
}

ControlType* Form::getControl(UInt16 id)
{
	FormType* frm = getFormType();
	return (ControlType*)FrmGetObjectPtr(frm, FrmGetObjectIndex(frm, id));
}

Char* Form::getField(UInt16 field)
{
	return FldGetTextPtr((FieldType*)getControl(field));
}

int Form::getFieldI(UInt16 field)
{
	return StrAToI(FldGetTextPtr((FieldType*)getControl(field)));
}

double Form::getFieldD(UInt16 field)
{
	return strToDouble(FldGetTextPtr((FieldType*)getControl(field)));
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
