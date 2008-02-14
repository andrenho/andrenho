#include "pedidos.h"
#include "palm.h"
#include "forms.h"

void testaPrimeiroUso()
{
	// WagnClienteDB
	if(DmCreateDatabase(0, "WagnClienteDB", DB_CREATOR, 'DATA', false) == dmErrAlreadyExists)
		return;
	
}

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	UInt16 err;
	EventType e;
	FormType* pfrm;

	testaPrimeiroUso();

	principal = new Principal();
	pedido = new Pedido();
	itens = new Itens();
	buscaCliente = new BuscaCliente();
	
	current = principal;

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

	return 0;
}

/*
void load_pointers()
{
	// pSegB = (ControlPtr)FrmGetObjectPtr(pfrm, FrmGetObjectIndex(pfrm, SegB));
}
*/
