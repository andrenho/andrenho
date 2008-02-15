#include "events.h"
#include "extern.h"

Form* current;
BuscaCliente* buscaCliente;
DBCliente* dbCliente;

void mainLoop(UInt16 cmd)
{
	bool quit = false;
	UInt16 err;
	EventType e;
	FormType* pfrm;

	dbCliente = new DBCliente();
	buscaCliente = new BuscaCliente();

	if (cmd == sysAppLaunchCmdNormalLaunch)
	{
		current->open();

		while(!quit)
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
					pfrm = FrmGetActiveForm();
					FrmDrawForm(pfrm);
					break;

				case appStopEvent:
					quit = true;
					break;

				default:
					current->event(e.data.ctlSelect.controlID);
					if (FrmGetActiveForm())
						FrmHandleEvent(FrmGetActiveForm(), &e);
					break;
			}
		}

		FrmCloseAllForms();
	}

	delete dbCliente;
	delete buscaCliente;
}
