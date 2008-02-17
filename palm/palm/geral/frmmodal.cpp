#include "frmmodal.h"
#include "extern.h"

void* FrmModal::showDialog()
{
	UInt16 err;
	EventType e;

	returnValue = NULL;
	this->leave_form = false;

	FrmPopupForm(this->id);

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
				break;
			case appStopEvent:
				appActive = false;
				return NULL;
			default:
				if(!event(e.data.ctlSelect.controlID, e.eType))
					FrmDispatchEvent(&e);
				break;
		}
	}

	FrmReturnToForm(current->id);

	return returnValue;
}
