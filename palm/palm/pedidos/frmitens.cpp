#include "frmitens.h"
#include "apppedidos.h"

typedef struct
{
	int numeroForm;
	int numeroPedido;
} PrefItens;

FrmItens::FrmItens() : Form()
{
	this->id = ItensFrm;
}

bool FrmItens::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case ItensCancelar:
				if(perguntaSimNao("Tem certeza que deseja cancelar a inclusão deste pedido?"))
				{
					appPedidos->dbPedido->excluirPedido(numeroPedido);
					goToForm(appPedidos->frmPrincipal);
				}
				break;
			case ItensNovo:
				appPedidos->frmNovoItem->numeroPedido = this->numeroPedido;
				appPedidos->frmNovoItem->numeroItem = appPedidos->dbPedidoItem->ultimoItem(numeroPedido);
				goToForm(appPedidos->frmNovoItem);
				break;
		}
	return false;
}

void FrmItens::carregarPreferencias()
{
	PrefItens* p = (PrefItens*)appPedidos->preferencias;
	this->numeroPedido = p->numeroPedido;

	this->carregaPreferencias = false;
}

void FrmItens::gravarPreferencias()
{
	PrefItens p;
	Preferencias pref;

	p.numeroForm = N_FORM_ITENS;
	p.numeroPedido = this->numeroPedido;
	
	pref.salvar((void*)&p, sizeof(PrefItens));
}
