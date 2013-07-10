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
	int pagtoSelecionado;
} PrefFinaliza;

FrmFinaliza::FrmFinaliza()
{
	this->id = FinalizaFrm;

	pagtoSelecionado = 1;
}

void FrmFinaliza::inicializacao()
{
	l = new Lista();
	appPedidos->dbPagto->alimentaLista(l);
}

FrmFinaliza::~FrmFinaliza()
{
	delete l;
}

bool FrmFinaliza::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case FinalizaOK:
				if(validarDados())
				{
					salvarDados();
					SndPlaySystemSound(sndConfirmation);
					appPedidos->frmEnvio->numeroPedido = numeroPedido;
					goToForm(appPedidos->frmEnvio);
				}
				break;
			case FinalizaVoltar:
				appPedidos->frmItens->numeroPedido = numeroPedido;
				goToForm(appPedidos->frmItens);
				break;
		}

	else if(e->eType == keyDownEvent)
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

	else if(e->eType == popSelectEvent)
		if(controlID == FinalizaPagamento)
		{
			int p = l->registro(e->data.popSelect.selection);
			if(p == 0) /* Outra */
			{
				displayAlert(ToBeDone);
				FrmDispatchEvent(e);
				CtlSetLabel(getControl(FinalizaPagamento), "À Vista");
				LstSetSelection((ListType*)getControl(FinalizaPagamentoList), 0);
				pagtoSelecionado = 1;
				return true;
			}
			else
				pagtoSelecionado = p;
		}

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
	this->pagtoSelecionado = p->pagtoSelecionado;

	this->carregaPreferencias = false;
}

void FrmFinaliza::gravarPreferencias()
{
	PrefFinaliza p;
	Preferencias pref;

	p.numeroForm = N_FORM_FINALIZA;
	p.valorPedido = this->valorPedido;
	p.numeroPedido = this->numeroPedido;
	p.pagtoSelecionado = this->pagtoSelecionado;
	StrCopyTest(p.vlrDesconto, getField(FinalizaDescontoDinheiro));
	StrCopyTest(p.percDesconto, getField(FinalizaDescontoPerc));
	StrCopyTest(p.pagamento, CtlGetLabel(getControl(FinalizaPagamento)));
	
	pref.salvar((void*)&p, sizeof(PrefFinaliza));
}

void FrmFinaliza::doAfterDrawing()
{
	l->setItensLista((ListType*)getControl(FinalizaPagamentoList), 10, true);

	Form::doAfterDrawing();
	ajustaValorTotal();
}

void FrmFinaliza::ajustaValorTotal()
{
	char valor[25];
	fmtdbl(this->valorPedido - strToDouble(getField(FinalizaDescontoDinheiro)), 2, valor);
	setField(FinalizaTotal, valor);
}

bool FrmFinaliza::validarDados()
{
	if(this->valorPedido - strToDouble(getField(FinalizaDescontoDinheiro)) < 0)
	{
		mensagemErro("O valor do desconto não pode ser maior que o valor do pedido.");
		return false;
	}
	return true;
}

void FrmFinaliza::salvarDados()
{
	appPedidos->dbPedido->encerraPedido(numeroPedido, pagtoSelecionado, strToDouble(getField(FinalizaDescontoDinheiro)));
}
