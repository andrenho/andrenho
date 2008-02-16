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

bool Pedido::event(UInt16 controlID, eventsEnum evt)
{
	if(evt == ctlSelectEvent)
		switch(controlID)
		{
			case PedidoCancelar:
				goToForm(principal);
				return true;
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
				return true;
			case PedidoBuscaCliente:
				buscaCliente->busca(this, PedidoCNPJ, PedidoCliente, PedidoRazaoSocial);
				return true;
		}
	return false;
}

void Pedido::loadData()
{
}
