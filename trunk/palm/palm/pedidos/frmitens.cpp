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
	itemNoTopo = 1;
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
	else if(e->eType == sclRepeatEvent)
	{
		itemNoTopo = e->data.sclRepeat.newValue;
		alimentaLista();
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

void FrmItens::doAfterDrawing()	
{
	Form::doAfterDrawing();
	alimentaLista();
}

void FrmItens::alimentaLista()
{
	int i;
	int id = 5000 - ((itemNoTopo-1) * 10);
	int numRegistros = 0;
	DmOpenRef db = appPedidos->dbPedidoItem->db;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->pedido == numeroPedido)
		{
			if(id >= 5000 && id < 5040)
			{
				setField(id + 1, "Teste"); // TODO
				CtlShowControl(getControl(id + 4));
			}
			id += 10;
			numRegistros++;
		}
		MemHandleUnlock(h);
	}

	while(id < 5040)
	{
		setField(id + 1, "");
		setField(id + 2, "");
		setField(id + 3, "");
		CtlHideControl(getControl(id + 4));
		id += 10;
	}

	if(numRegistros == 0)
		numRegistros = 1;

	SclSetScrollBar((ScrollBarType*)getControl(ItensScroll),
			itemNoTopo, 1, numRegistros, 4);
}
