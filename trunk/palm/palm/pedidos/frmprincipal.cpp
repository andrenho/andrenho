#include "frmprincipal.h"
#include "frmpedido.h"

extern Form* current;
extern FrmPedido* frmPedido;

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
				goToForm(frmPedido);
				return false;
			case PrincipalConectar:
				displayAlert(ToBeDone);
				return true;
		}
	return false;
}
