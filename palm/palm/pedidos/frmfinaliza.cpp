#include "frmfinaliza.h"
#include "apppedidos.h"
#include "util.h"
#include "lista.h"

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
	s = NULL;

	pagtoSelecionado = 1;
}

void FrmFinaliza::inicializacao()
{
	l = new Lista();
	l->adicionaRegistro(1, "À Vista");
	l->adicionaRegistro(1, "A Prazo");
}

FrmFinaliza::~FrmFinaliza()
{
	if(s)
		MemPtrFree(s);
	delete l;
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

				// insere caractere no campo, já que estamos bloqueando-o
				FrmDispatchEvent(e);

				// ajusta os valores
				double vlrDesconto = strToDouble(getField(FinalizaDescontoDinheiro));
				double perc = vlrDesconto / valorPedido * 100;
				fmtdbl(perc, 2, buf);
				setField(FinalizaDescontoPerc, buf);
				ajustaValorTotal();
				return true;
			}
			case FinalizaDescontoPerc:
			{
				char buf[20];

				// insere caractere no campo, já que estamos bloqueando-o
				FrmDispatchEvent(e);

				// ajusta os valores
				double perc = strToDouble(getField(FinalizaDescontoPerc));
				double vlrDesconto = valorPedido * (perc / 100);
				fmtdbl(vlrDesconto, 2, buf);
				setField(FinalizaDescontoDinheiro, buf);
				ajustaValorTotal();
				return true;
			}
		}
		return false;
	}
	/*
	 * TODO
	else if(e->eType == popSelectEvent)
		if(controlID == FinalizaPagamento)
			pagtoSelecionado = codPagtos[e->data.popSelect.selection];
	*/

	return false;
}

void FrmFinaliza::carregarPreferencias()
{
	PrefFinaliza* p = (PrefFinaliza*)appPedidos->preferencias;

	setField(FinalizaDescontoDinheiro, p->vlrDesconto);
	setField(FinalizaDescontoPerc, p->percDesconto); // TODO - não está carregando quando alimentdo automático
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
	s = (Char**)MemPtrNew(l->numeroRegistros() * sizeof(char*));
	l->stringLista(s);

	LstSetListChoices((ListType*)getControl(FinalizaPagamentoList), s, l->numeroRegistros());
	if(l->numeroRegistros() >= 10)
		LstSetHeight((ListType*)getControl(FinalizaPagamentoList), 10);
	else
		LstSetHeight((ListType*)getControl(FinalizaPagamentoList), l->numeroRegistros());
	LstDrawList((ListType*)getControl(FinalizaPagamentoList));

	FrmSetFocus(getFormType(), FrmGetObjectIndex(getFormType(), FinalizaDescontoDinheiro));

	Form::doAfterDrawing();
	ajustaValorTotal();
}

void FrmFinaliza::ajustaValorTotal()
{
	char valor[25];
	fmtdbl(this->valorPedido - strToDouble(getField(FinalizaDescontoDinheiro)), 2, valor);
	setField(FinalizaTotal, valor);
}
