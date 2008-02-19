#include "frmnovoitem.h"
#include "apppedidos.h"
#include "util.h"

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
	char diaEntrega[3];
	char mesEntrega[3];
	char anoEntrega[5];
	char valorTotal[26];
} PrefNovoItem;

FrmNovoItem::FrmNovoItem() : Form()
{
	this->id = NovoItemFrm;
}

bool FrmNovoItem::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case NovoItemCancelar:
				if(perguntaSimNao("Tem certeza que deseja cancelar a inclusão deste item?"))
					goToForm(appPedidos->frmItens);
				break;
			case NovoItemInserir:
				if(validarDados())
				{
					salvarDados();
					goToForm(appPedidos->frmItens);
				}
				break;
		}
	return false;
}

void FrmNovoItem::doAfterDrawing()
{
	this->produto = -1;
	FldGrabFocus((FieldType*)getControl(NovoItemProduto));
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
	setField(NovoItemDiaEntrega, p->diaEntrega);
	setField(NovoItemMesEntrega, p->mesEntrega);
	setField(NovoItemAnoEntrega, p->anoEntrega);
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
	StrCopyTest(p.diaEntrega, getField(NovoItemDiaEntrega));
	StrCopyTest(p.mesEntrega, getField(NovoItemMesEntrega));
	StrCopyTest(p.anoEntrega, getField(NovoItemAnoEntrega));
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

	// TODO - valida datas

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
	/*
	p.diaEntrega = getFieldI(NovoItemDiaEntrega);
	p.mesEntrega = getFieldI(NovoItemMesEntrega);
	p.anoEntrega = getFieldI(NovoItemAnoEntrega);
	*/

	b = appPedidos->dbPedido->adicionaRegistro(&p, sizeof(R_PedidoItem));
	ErrFatalDisplayIf(!b, "Registro do item do pedido não pode ser adicionado.");
}
