#include "pedido.h"
#include "principal.h"
#include "itens.h"
#include "buscacliente.h"

extern Principal* principal;
extern Itens* itens;
extern BuscaCliente* buscaCliente;

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
			this->cliente = buscaCliente->busca(PedidoCliente);
			if(this->cliente == NULL)
				FrmAlert(ClienteNaoExiste);
			else
				itens->open();
			break;
	}
}

void Pedido::loadData()
{
}
