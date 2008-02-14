#include "pedido.h"
#include "principal.h"

extern Principal* principal;

Pedido::Pedido()
{
	this->id = PedidoFrm;
}

void Pedido::event(UInt16 controlID)
{
	switch(controlID)
	{
		case PedidoCancelar:
			principal->open();
			break;
		case PedidoItens:
			// FrmGotoForm(Itens);
			break;
	}
}
