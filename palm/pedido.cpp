#include "pedido.h"
#include "principal.h"
#include "itens.h"
#include "buscacliente.h"
#include "dbcliente.h"

extern Principal* principal;
extern Itens* itens;
extern BuscaCliente* buscaCliente;
extern DBCliente* dbCliente;

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
		{
			Char* t = FldGetTextPtr((FieldType*)getControl(PedidoCliente));
			this->cliente = dbCliente->buscaCNPJ(t);
			if(this->cliente == NULL)
				FrmAlert(ClienteNaoExiste);
			else
				itens->open();
			break;
		}
	}
}

void Pedido::loadData()
{
}
