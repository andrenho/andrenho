#include "frmnovoitem.h"
#include "apppedidos.h"
#include "util.h"
#include "data.h"

#define NOVO_ITEM   "Novo Item"
#define EDITAR_ITEM "Editar Item"

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
			case NovoItemCancelar:
				goToForm(appPedidos->frmItens);
				break;
			case NovoItemExcluir:
				if(perguntaAvisoSimNao("Tem certeza que deseja excluir este item?"))
				{
					appPedidos->dbPedidoItem->excluirItem(numeroPedido, numeroItem);
					goToForm(appPedidos->frmItens);
				}
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
	if(tipoInsercao == INSERINDO)
	{
		this->produto = -1;
		FrmSetFocus(getFormType(), FrmGetObjectIndex(getFormType(), NovoItemProduto));

		FrmHideObject(getFormType(), FrmGetObjectIndex(getFormType(), NovoItemExcluir));
		FrmSetTitle(getFormType(), NOVO_ITEM);

		Data data;
		data.formatarTexto(dataEntrega);
		CtlSetLabel(getControl(NovoItemEntrega), dataEntrega);
	}
	else if(tipoInsercao == EDITANDO)
	{
		int i;

		FrmShowObject(getFormType(), FrmGetObjectIndex(getFormType(), NovoItemExcluir));
		FrmSetTitle(getFormType(), EDITAR_ITEM);

		for(i=0; i<DmNumRecords(appPedidos->dbPedidoItem->db); i++)
		{
			MemHandle h = DmQueryRecord(appPedidos->dbPedidoItem->db, i);
			R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);

			if(p->pedido == numeroPedido && p->n == numeroItem)
			{
				char qtd[12], vlr[20], dt[11];

				this->produto = p->produto;
				setField(NovoItemDescProduto, p->descProduto);

				fmtdbl(p->quantidade, -1, qtd);
				setField(NovoItemQuantidade, qtd);

				fmtdbl(p->valor, 2, vlr);
				setField(NovoItemValor, vlr);

				CtlSetLabel(getControl(NovoItemEntrega), p->dataEntrega);

				MemHandleUnlock(h);
				goto found;
			}

			MemHandleUnlock(h);
		}

		ErrFatalDisplay("Item não encontrado.");
	}

found:
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

	p.pedido = this->numeroPedido;
	p.n = this->numeroItem;
	p.produto = this->produto;
	p.quantidade = getFieldD(NovoItemQuantidade);
	p.valor = getFieldD(NovoItemValor);
	StrCopy(p.dataEntrega, CtlGetLabel(getControl(NovoItemEntrega)));
	StrCopy(p.descProduto, descProduto);

	if(tipoInsercao == INSERINDO)
		b = appPedidos->dbPedidoItem->adicionaRegistro(&p, sizeof(R_PedidoItem));
	else if(tipoInsercao == EDITANDO)
		b = appPedidos->dbPedidoItem->atualizaRegistro(&p);
	ErrFatalDisplayIf(!b, "Registro do item do pedido não pôde ser adicionado.");
}
