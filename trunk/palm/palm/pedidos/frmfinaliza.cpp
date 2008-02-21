#include "frmfinaliza.h"
#include "apppedidos.h"
#include "util.h"

typedef struct
{
	int numeroForm;
	int numeroPedido;
	double valorPedido;
	char vlrDesconto[13];
	char percDesconto[5];
	char pagamento[31];
} PrefFinaliza;

FrmFinaliza::FrmFinaliza()
{
	this->id = FinalizaFrm;
}

bool FrmFinaliza::event(UInt16 controlID, EventType* e)
{
	if(e->eType == keyDownEvent)
	{
		UInt16 idx = FrmGetFocus(getFormType());
		if(idx == noFocus)
			return false;
		switch(FrmGetObjectId(getFormType(), idx))
		{
			case FinalizaDescontoDinheiro:
			{
				char buf[20];
				double vlrDesconto = strToDouble(getField(FinalizaDescontoDinheiro));
				double perc = vlrDesconto / valorPedido * 100;
				fmtdbl(perc, -1, buf);
				setField(FinalizaDescontoPerc, buf);
				ajustaValorTotal();
				return true;
			}
			case FinalizaDescontoPerc:
				return true;
		}
		return false;
	}
	return false;
}

void FrmFinaliza::carregarPreferencias()
{
	PrefFinaliza* p = (PrefFinaliza*)appPedidos->preferencias;

	setField(FinalizaDescontoDinheiro, p->vlrDesconto);
	setField(FinalizaDescontoPerc, p->percDesconto);
	CtlSetLabel(getControl(FinalizaPagamento), p->pagamento);
	this->valorPedido = p->valorPedido;
	this->numeroPedido = p->numeroPedido;

	this->carregaPreferencias = false;
}

void FrmFinaliza::gravarPreferencias()
{
	PrefFinaliza p;
	Preferencias pref;

	p.numeroForm = N_FORM_FINALIZA;
	p.valorPedido = this->valorPedido;
	p.numeroPedido = this->numeroPedido;
	StrCopyTest(p.vlrDesconto, getField(FinalizaDescontoDinheiro));
	StrCopyTest(p.percDesconto, getField(FinalizaDescontoPerc));
	StrCopyTest(p.pagamento, CtlGetLabel(getControl(FinalizaPagamento)));
	
	pref.salvar((void*)&p, sizeof(PrefFinaliza));
}

void FrmFinaliza::doAfterDrawing()
{
	Form::doAfterDrawing();
	ajustaValorTotal();
}

void FrmFinaliza::ajustaValorTotal()
{
	char valor[25];
	fmtdbl(this->valorPedido - strToDouble(getField(FinalizaDescontoDinheiro)), 2, valor);
	setField(FinalizaTotal, valor);
}
