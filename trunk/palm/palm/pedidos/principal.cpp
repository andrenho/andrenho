#include "principal.h"
#include "pedido.h"

extern Form* current;
extern Pedido* pedido;

Principal::Principal()
{
	this->id = PrincipalFrm;
}

bool Principal::event(UInt16 controlID, eventsEnum evt)
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

void Principal::loadData()
{
}
