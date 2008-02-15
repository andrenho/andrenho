#include "events.h"
#include "extern.h"

Form* current;
BuscaCliente* buscaCliente;
DBCliente* dbCliente;

void mainLoop(UInt16 cmd)
{
	UInt16 err;
	EventType e;
	FormType* pfrm;

	dbCliente = new DBCliente();
	buscaCliente = new BuscaCliente();

	if (cmd == sysAppLaunchCmdNormalLaunch)
	{
		current->open();

		while(1)
		{
			EvtGetEvent(&e, 100);
			if (SysHandleEvent(&e))
				continue;
			if (MenuHandleEvent(NULL, &e, &err))
				continue;

			switch(e.eType)
			{
				case ctlSelectEvent:
					current->event(e.data.ctlSelect.controlID);
					goto _default;
					break;

				case frmLoadEvent:
					FrmSetActiveForm(FrmInitForm(e.data.frmLoad.formID));
					break;

				case frmOpenEvent:
					pfrm = FrmGetActiveForm();
					FrmDrawForm(pfrm);
					break;

				case appStopEvent:
					goto _quit;

				default:
_default:
					if (FrmGetActiveForm())
						FrmHandleEvent(FrmGetActiveForm(), &e);
			}
		}

_quit:
		FrmCloseAllForms();
	}
}
