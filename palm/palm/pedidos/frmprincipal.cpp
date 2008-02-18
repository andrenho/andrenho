#include "frmprincipal.h"
#include "apppedidos.h"

extern Form* current;

FrmPrincipal::FrmPrincipal() : Form()
{
	this->id = PrincipalFrm;
}

bool FrmPrincipal::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case PrincipalNovo:
				goToForm(appPedidos->frmPedido);
				return false;
			case PrincipalConectar:
				displayAlert(ToBeDone);
				return true;
		}
	return false;
}
