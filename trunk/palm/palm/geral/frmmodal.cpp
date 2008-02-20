#include "frmmodal.h"
#include "aplicativo.h"

void FrmModal::showDialog(void* returnValue)
{
	UInt16 err;
	EventType e;

	this->leave_form = false;
	this->returnValue = returnValue;

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
				app->appActive = false;
				return;
			default:
				if(!event(e.data.ctlSelect.controlID, &e))
					FrmDispatchEvent(&e);
				break;
		}
	}

	FrmReturnToForm(app->current->id);
}
