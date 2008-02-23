#include "frmprincipal.h"
#include "apppedidos.h"

extern Form* current;

FrmPrincipal::FrmPrincipal() : Form()
{
	this->id = PrincipalFrm;
	itemNoTopo = 1;
}

bool FrmPrincipal::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case PrincipalNovo:
				appPedidos->frmPedido->numeroPedido = appPedidos->dbPedido->ultimoPedido() + 1;
				goToForm(appPedidos->frmPedido);
				return false;
			case PrincipalConectar:
				displayAlert(ToBeDone);
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

void FrmPrincipal::doAfterDrawing()
{
	char buf[41];
	int pedidos;

	Form::doAfterDrawing();
	
	pedidos = appPedidos->dbPedido->numeroPedidos();
	StrPrintF(buf, "%d pedido%s não enviado%s", pedidos, pedidos == 1 ? "" : "s", pedidos == 1 ? "" : "s");
	setField(PrincipalNPedidos, buf);

	alimentaLista();
}

void FrmPrincipal::gravarPreferencias()
{
	Preferencias p;
	p.salvar(NULL, 0);
}

void FrmPrincipal::alimentaLista()
{
	int i;
	int id = 4000 - ((itemNoTopo-1) * 10);
	int numRegistros = 0;
	DmOpenRef db = appPedidos->dbPedido->db;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_Pedido* p = (R_Pedido*)MemHandleLock(h);
		if(id >= 4000 && id < 4040)
		{
			/*
			char qtd[12], vlr_unit[16], qtd_vlr[30];
			char vlr[20], vlr_total[17];
			fmtdbl(p->quantidade, -1, qtd);
			fmtdbl(p->valor, 2, vlr_unit);
			fmtdbl(p->quantidade * p->valor, 2, vlr_total);
			StrPrintF(qtd_vlr, "%s x R$ %s", qtd, vlr_unit);
			StrPrintF(vlr, "R$ %s", vlr_total);
			*/
			setField(id + 1, "Teste"); // TODO
			FrmShowObject(getFormType(), FrmGetObjectIndex(getFormType(), id + 2));
			/*
			setField(id + 3, qtd_vlr);
			setField(id + 4, vlr);
			*/
		}
		id += 10;
		numRegistros++;
		MemHandleUnlock(h);
	}

	while(id < 4040)
	{
		setField(id + 1, "");
		FrmHideObject(getFormType(), FrmGetObjectIndex(getFormType(), id + 2));
		setField(id + 3, "");
		setField(id + 4, "");
		id += 10;
	}

	if(numRegistros == 0)
		numRegistros = 1;

	SclSetScrollBar((ScrollBarType*)getControl(PrincipalScroll),
			itemNoTopo, 1, numRegistros, 4);
}
