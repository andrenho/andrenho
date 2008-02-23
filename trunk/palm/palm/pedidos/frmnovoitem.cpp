#include "frmnovoitem.h"
#include "apppedidos.h"
#include "util.h"
#include "data.h"

typedef struct
{
	int numeroForm;
	int pedido;
	int nItem;
	int produto;
	char textoProduto[26];
	char descProduto[81];
	char quantidade[13];
	char um[4];
	char valor[21];
	char dataEntrega[11];
	char valorTotal[26];
} PrefNovoItem;

FrmNovoItem::FrmNovoItem() : Form()
{
	id = NovoItemFrm;
	hDataEntrega = MemHandleNew(11);
	dataEntrega = (Char*)MemHandleLock(hDataEntrega);
}

FrmNovoItem::~FrmNovoItem()
{
	MemHandleUnlock(hDataEntrega);
	MemHandleFree(hDataEntrega);
}

bool FrmNovoItem::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case NovoItemProdutoBusca:
				this->produto = 1;                   // TODO
				StrCopy(this->descProduto, "Teste"); // TODO
				break;
			case NovoItemExcluir:
				goToForm(appPedidos->frmItens);
				/*
				if(perguntaSimNao("Tem certeza que deseja excluir este item?"))
				{
					appPedidos->dbPedidoItem->excluirItem(numeroPedido, numeroItem);
					goToForm(appPedidos->frmItens);
				}
				*/
				break;
			case NovoItemInserir:
				if(validarDados())
				{
					salvarDados();
					goToForm(appPedidos->frmItens);
				}
				break;
			case NovoItemEntrega:
				Data data; // TODO buscar data no controle
				Int16 dia, mes, ano;
				dia = data.dia;
				mes = data.mes;
				ano = data.ano;
				SelectDay(selectDayByDay, &mes, &dia, &ano, "Data de Entrega");
				data.ajusta(dia, mes, ano);
				data.formatarTexto(dataEntrega);
				CtlSetLabel(getControl(NovoItemEntrega), dataEntrega);
				break;
		}
	return false;
}

void FrmNovoItem::doAfterDrawing()
{
	this->produto = -1;
	FrmSetFocus(getFormType(), FrmGetObjectIndex(getFormType(), NovoItemProduto));

	Data data;
	data.formatarTexto(dataEntrega);
	CtlSetLabel(getControl(NovoItemEntrega), dataEntrega);
	
	Form::doAfterDrawing();
}

void FrmNovoItem::carregarPreferencias()
{
	PrefNovoItem* p = (PrefNovoItem*)appPedidos->preferencias;
	
	this->numeroPedido = p->pedido;
	this->numeroItem = p->nItem;
	this->produto = p->produto;
	setField(NovoItemProduto, p->textoProduto);
	setField(NovoItemDescProduto, p->descProduto);
	setField(NovoItemQuantidade, p->quantidade);
	setField(NovoItemUM, p->um);
	setField(NovoItemValor, p->valor);
	CtlSetLabel(getControl(NovoItemEntrega), p->dataEntrega);
	setField(NovoItemTotalItem, p->valorTotal);

	this->carregaPreferencias = false;
}

void FrmNovoItem::gravarPreferencias()
{
	PrefNovoItem p;
	Preferencias pref;

	p.numeroForm = N_FORM_NOVO_ITEM;
	p.pedido = this->numeroPedido;
	p.nItem = this->numeroItem;
	p.produto = this->produto;
	StrCopyTest(p.textoProduto, getField(NovoItemProduto));
	StrCopyTest(p.descProduto, getField(NovoItemDescProduto));
	StrCopyTest(p.quantidade, getField(NovoItemQuantidade));
	StrCopyTest(p.um, getField(NovoItemUM));
	StrCopyTest(p.valor, getField(NovoItemValor));
	StrCopyTest(p.dataEntrega, CtlGetLabel(getControl(NovoItemEntrega)));
	StrCopyTest(p.valorTotal, getField(NovoItemTotalItem));

	pref.salvar((void*)&p, sizeof(PrefNovoItem));
}

bool FrmNovoItem::validarDados()
{
	if(produto == -1)
	{
		mensagemErro("Um produto não foi selecionado.");
		return false;
	}
	if(getFieldD(NovoItemQuantidade) <= 0)
	{
		mensagemErro("A quantidade informada é inválida.");
		return false;
	}
	if(getFieldD(NovoItemValor) <= 0)
	{
		mensagemErro("O valor unitário informado é inválido.");
		return false;
	}
	// TODO verifica se data é menor que hoje
	
	return true;
}

void FrmNovoItem::salvarDados()
{
	// esta função assume que os dados já foram validados
	R_PedidoItem p;
	bool b;
	DateType dtPl;
	Data data(CtlGetLabel(getControl(NovoItemEntrega)));
	data.formatarPalm(&dtPl);

	p.pedido = this->numeroPedido;
	p.n = this->numeroItem;
	p.produto = this->produto;
	p.quantidade = getFieldD(NovoItemQuantidade);
	p.valor = getFieldD(NovoItemValor);
	p.dataEntrega = dtPl;
	StrCopy(p.descProduto, descProduto);

	b = appPedidos->dbPedidoItem->adicionaRegistro(&p, sizeof(R_PedidoItem));
	ErrFatalDisplayIf(!b, "Registro do item do pedido não pode ser adicionado.");
}
