#include "frmprincipal.h"
#include "frmpedido.h"

extern Form* current;
extern FrmPedido* pedido;

FrmPrincipal::FrmPrincipal()
{
	this->id = PrincipalFrm;
}

bool FrmPrincipal::event(UInt16 controlID, eventsEnum evt)
{
	if(evt == ctlSelectEvent)
		switch(controlID)
		{
			case PrincipalNovo:
				goToForm(pedido);
				return false;
			case PrincipalConectar:
				displayAlert(ToBeDone);
				return true;
		}
	return false;
}

void FrmPrincipal::loadData()
{
}
