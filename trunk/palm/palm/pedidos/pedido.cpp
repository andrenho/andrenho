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

Pedido::~Pedido()
{
}

void Pedido::event(UInt16 controlID)
{
	switch(controlID)
	{
		case PedidoCancelar:
			principal->open();
			break;
		case PedidoItens:
			/*
			Char* t = FldGetTextPtr((FieldType*)getControl(PedidoCliente));
			R_Cliente* r = dbCliente->busca(t, false);
			this->cliente = r ? r->CNPJ : NULL;
			if(this->cliente == NULL)
				FrmAlert(ClienteNaoExiste);
			else
				itens->open();
			break;
			*/
			break;
		case PedidoBuscaCliente:
			buscaCliente->busca(this, PedidoCNPJ, PedidoCliente, 0);
			break;
	}
}

void Pedido::loadData()
{
}
