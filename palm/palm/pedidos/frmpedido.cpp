#include "frmpedido.h"
#include "frmprincipal.h"
#include "frmitens.h"
#include "buscacliente.h"
#include "dbcliente.h"
#include "extern_pedidos.h"

FrmPedido::FrmPedido() : Form()
{
	this->id = PedidoFrm;
}

FrmPedido::~FrmPedido()
{
}

bool FrmPedido::event(UInt16 controlID, eventsEnum evt)
{
	if(evt == ctlSelectEvent)
		switch(controlID)
		{
			case PedidoCancelar:
				goToForm(frmPrincipal);
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
			case PedidoCidade:
				frmCidades->showDialog();
				return true;
		}
	return false;
}

void FrmPedido::loadData()
{
}
