#include "principal.h"
#include "pedido.h"

extern Form* current;
extern Pedido* pedido;

Principal::Principal()
{
	this->id = PrincipalFrm;
}

void Principal::event(UInt16 controlID)
{
	switch(controlID)
	{
		case PrincipalNovo:
			pedido->open();
			break;
		case PrincipalConectar:
			FrmAlert(ToBeDone);
			break;
	}
}
