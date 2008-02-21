#include "frmitens.h"
#include "apppedidos.h"
#include "util.h"

typedef struct
{
	int numeroForm;
	int numeroPedido;
	int itemNoTopo;
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
				return true;
			case ItensNovo:
				appPedidos->frmNovoItem->numeroPedido = this->numeroPedido;
				appPedidos->frmNovoItem->numeroItem = appPedidos->dbPedidoItem->ultimoItem(numeroPedido);
				goToForm(appPedidos->frmNovoItem);
				return true;
			case ItensFinalizar:
				if(appPedidos->dbPedidoItem->numeroItens(this->numeroPedido) == 0)
					mensagemErro("É necessário incluir pelo menos um item antes de finalizar o pedido.");
				else
				{
					appPedidos->frmFinaliza->numeroPedido = this->numeroPedido;
					appPedidos->frmFinaliza->valorPedido = appPedidos->dbPedidoItem->valorPedido(this->numeroPedido);
					goToForm(appPedidos->frmFinaliza);
				}
				return true;
		}
	else if(e->eType == sclRepeatEvent)
	{
		itemNoTopo = e->data.sclRepeat.newValue;
		alimentaLista();
		return true;
	}

	return false;
}

void FrmItens::carregarPreferencias()
{
	PrefItens* p = (PrefItens*)appPedidos->preferencias;
	this->numeroPedido = p->numeroPedido;
	this->itemNoTopo = p->itemNoTopo;

	this->carregaPreferencias = false;
}

void FrmItens::gravarPreferencias()
{
	PrefItens p;
	Preferencias pref;

	p.numeroForm = N_FORM_ITENS;
	p.numeroPedido = this->numeroPedido;
	p.itemNoTopo = this->itemNoTopo;
	
	pref.salvar((void*)&p, sizeof(PrefItens));
}

void FrmItens::doAfterDrawing()	
{
	char buf[20];
	int itens;

	Form::doAfterDrawing();
	
	itens = appPedidos->dbPedidoItem->numeroItens(this->numeroPedido);
	StrPrintF(buf, "%d ite%s", itens, itens == 1 ? "m" : "ns");
	setField(ItensNItens, buf);
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
				char qtd[12], vlr_unit[16], qtd_vlr[30];
				char vlr[20], vlr_total[17];
				fmtdbl(p->quantidade, -1, qtd);
				fmtdbl(p->valor, 2, vlr_unit);
				fmtdbl(p->quantidade * p->valor, 2, vlr_total);
				StrPrintF(qtd_vlr, "%s x R$ %s", qtd, vlr_unit);
				StrPrintF(vlr, "R$ %s", vlr_total);
				setField(id + 1, "Teste"); // TODO
				FrmShowObject(getFormType(), FrmGetObjectIndex(getFormType(), id + 2));
				setField(id + 3, qtd_vlr);
				setField(id + 4, vlr);
			}
			id += 10;
			numRegistros++;
		}
		MemHandleUnlock(h);
	}

	while(id < 5040)
	{
		setField(id + 1, "");
		FrmHideObject(getFormType(), FrmGetObjectIndex(getFormType(), id + 2));
		setField(id + 3, "");
		setField(id + 4, "");
		id += 10;
	}

	if(numRegistros == 0)
		numRegistros = 1;

	SclSetScrollBar((ScrollBarType*)getControl(ItensScroll),
			itemNoTopo, 1, numRegistros, 4);
}
