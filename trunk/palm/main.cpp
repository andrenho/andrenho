#include "pedidos.h"
#include "palm.h"
#include "forms.h"

FormType* pfrm;

/*
void load_pointers()
{
	// pSegB = (ControlPtr)FrmGetObjectPtr(pfrm, FrmGetObjectIndex(pfrm, SegB));
}
*/

/*
static void dealWithSelectEvent(UInt16 controlID)
{
	switch(controlID)
	{
		case PrincipalNovo:
			FrmGotoForm(Pedido);
			break;
		case PrincipalConectar:
			FrmAlert(ToBeDone);
			break;

		case PedidoCancelar:
			FrmGotoForm(Principal);
			break;
		case PedidoItens:
			FrmGotoForm(Itens);
			break;
	}
}
*/

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	UInt16 err;
	EventType e;

	principal = new Principal();
	pedido = new Pedido();
	
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
