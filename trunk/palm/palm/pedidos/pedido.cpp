#include "frmpedido.h"
#include "frmprincipal.h"
#include "frmitens.h"
#include "buscacliente.h"
#include "dbcliente.h"

extern FrmPrincipal* principal;
extern FrmItens* itens;
extern BuscaCliente* buscaCliente;
extern DBCliente* dbCliente;

FrmPedido::FrmPedido()
{
	this->id = PedidoFrm;
}

FrmPedido::~FrmPedido()
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

void FrmPedido::loadData()
{
}
