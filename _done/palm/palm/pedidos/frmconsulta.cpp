#include "frmconsulta.h"
#include "apppedidos.h"
#include "util.h"

FrmConsulta::FrmConsulta()
{
	this->id = ConsultaFrm;
	itemNoTopo = 1;
}

bool FrmConsulta::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case ConsultaOk:
				goToForm(appPedidos->frmPrincipal);
				break;
			case ConsultaEditar:
				appPedidos->frmItens->numeroPedido = numeroPedido;
				appPedidos->frmItens->tipoInsercao = EDITANDO;
				goToForm(appPedidos->frmItens);
				break;
			case ConsultaExcluir:
				if(perguntaAvisoSimNao("Tem certeza que deseja EXCLUIR este pedido?"))
				{
					appPedidos->dbPedido->excluirPedido(numeroPedido);
					goToForm(appPedidos->frmPrincipal);
				}
				return true;
		}
	else if(e->eType == sclRepeatEvent)
	{
		itemNoTopo = e->data.sclRepeat.newValue;
		alimentaLista();
		return false;
	}

	return false;
}

void FrmConsulta::doAfterDrawing()	
{
	int i;
	DmOpenRef db = appPedidos->dbPedido->db;
	char vlr[25], vlrb[30];

	Form::doAfterDrawing();
	
	// busca cliente
	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_Pedido* p = (R_Pedido*)MemHandleLock(h);
		if(p->n == numeroPedido)
		{
			setField(ConsultaCliente, p->fantasiaCliente);
			MemHandleUnlock(h);
			goto cliente_encontrado;
		}
		MemHandleUnlock(h);
	}
	ErrFatalDisplay("Cliente não encontrado.");
cliente_encontrado:

	// busca valor
	fmtdbl(appPedidos->dbPedido->valorTotal(numeroPedido), 2, vlr);
	StrPrintF(vlrb, "R$ %s", vlr);
	setField(ConsultaValor, vlrb);

	alimentaLista();
}

void FrmConsulta::alimentaLista()
{
	int i;
	int id = 6000 - ((itemNoTopo-1) * 10);
	int numRegistros = 0;
	DmOpenRef db = appPedidos->dbPedidoItem->db;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->pedido == numeroPedido)
		{
			if(id >= 6000 && id < 6030)
			{
				char qtd[12], vlr_unit[16], qtd_vlr[30];
				char vlr[20], vlr_total[17];
				fmtdbl(p->quantidade, -1, qtd);
				fmtdbl(p->valor, 2, vlr_unit);
				fmtdbl(p->quantidade * p->valor, 2, vlr_total);
				StrPrintF(qtd_vlr, "%s x R$ %s", qtd, vlr_unit);
				StrPrintF(vlr, "R$ %s", vlr_total);
				setField(id + 1, p->descProduto); // TODO
				setField(id + 2, qtd_vlr);
				setField(id + 3, vlr);
			}
			id += 10;
			numRegistros++;
		}
		MemHandleUnlock(h);
	}

	while(id < 6030)
	{
		setField(id + 1, "");
		setField(id + 2, "");
		setField(id + 3, "");
		id += 10;
	}

	if(numRegistros == 0)
		numRegistros = 1;

	if(numRegistros > 3)
		SclSetScrollBar((ScrollBarType*)getControl(ConsultaScroll),
				itemNoTopo, 1, numRegistros-2, 3);
	else
		SclSetScrollBar((ScrollBarType*)getControl(ConsultaScroll),
				1, 1, 1, 3);
}
