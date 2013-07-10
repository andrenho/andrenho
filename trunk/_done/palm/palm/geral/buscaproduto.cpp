#include "buscaproduto.h"
#include "apppedidos.h"
#include "util.h"
#include "debug.h"

#define LABEL_REFERENCIA "Referência:"
#define LABEL_DESCRICAO  "Descrição:"

BuscaProduto::BuscaProduto()
{
	this->id = BuscaProdutoFrm;
	this->itemNoTopo = 1;
	this->produtoSelecionado = -1;
	this->lista = NULL;
}

bool BuscaProduto::event(UInt16 controlID, EventType *e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case BuscaProdutoReferencia:
				setField(BuscaProdutoLabel, LABEL_REFERENCIA);
				break;
			case BuscaProdutoDescricao:
				setField(BuscaProdutoLabel, LABEL_DESCRICAO);
				break;
			case BuscaProdutoCancelar:
				if(lista)
					delete lista;
				this->produtoSelecionado = -1;
				this->leave_form = true;
				break;
			case BuscaProdutoOK:
				int pos = LstGetSelection((ListType*)getControl(BuscaProdutoLista));
				if(pos == noListSelection)
				{
					mensagemErro("Nenhum produto foi selecinado.");
					return false;
				}
				MemHandle h = DmQueryRecord(appPedidos->dbProduto->db, lista->registro(pos));
				ErrFatalDisplayIf(h == NULL, "Registro não encontrado.");
				R_Produto* p = (R_Produto*)MemHandleLock(h);
				this->produtoSelecionado = p->n;
				caller->setField(referencia, p->referencia);
				caller->setField(descricao, p->descricao);
				caller->setField(unidMedida, p->unid_medida);
				MemHandleUnlock(h);
				if(lista)
					delete lista;
				this->leave_form = true;
				break;
		}
	else if(e->eType == sclRepeatEvent)
	{
		itemNoTopo = e->data.sclRepeat.newValue;
		alimentaLista();
		return false;
	}

	return false;
}

int BuscaProduto::busca(Form* caller, UInt16 referencia, UInt16 descricao, UInt16 unidMedida)
{
	int i, ct = 0, only;
	R_Produto* p;
	Char* ref = FldGetTextPtr((FieldType*)caller->getControl(referencia));

	this->caller = caller;
	this->referencia = referencia;
	this->descricao = descricao;
	this->unidMedida = unidMedida;

	if(ref == NULL)
	{
		ct = 2;
		goto vazio;
	} 
	else if(StrCompare(ref, "") == 0)
	{
		ct = 2;
		goto vazio;
	}

	for(i=0; i<DmNumRecords(app->dbProduto->db); i++)
	{
		MemHandle h = DmQueryRecord(app->dbProduto->db, i);
		p = (R_Produto*)MemHandleLock(h);
		if(StrCaselessCompare(ref, p->referencia) == 0)
		{
			// encontrado!!!
			only = i;
			ct++;
		}
		MemHandleUnlock(h);
	}
	
vazio:
	if(ct == 0)
	{
		displayAlert(ProdutoNaoExiste);
		return -1;
	}
	else if(ct == 1)
	{
		int n;
		MemHandle h = DmQueryRecord(app->dbProduto->db, only);
		p = (R_Produto*)MemHandleLock(h);
		n = p->n;
		caller->setField(referencia, p->referencia);
		caller->setField(descricao, p->descricao);
		caller->setField(unidMedida, p->unid_medida);
		MemHandleUnlock(h);
		return n;
	}
	else // ct > 1
	{
		showDialog(NULL);
		return this->produtoSelecionado;
	}
}

void BuscaProduto::doAfterDrawing()
{
	CtlSetValue(getControl(BuscaProdutoReferencia), 1);
	setField(BuscaProdutoLabel, LABEL_REFERENCIA);
	alimentaLista();

	Form::doAfterDrawing();
}

void BuscaProduto::alimentaLista()
{
	char parametro;
	int i, ct = 0;
	DmOpenRef db = appPedidos->dbProduto->db;
	int numRegistros = 0;
	int falta = itemNoTopo;
	char* campo = getField(BuscaProdutoCampo);
	
	// encontra o parâmetro de procura
	if(CtlGetValue(getControl(BuscaProdutoDescricao)) == 1)
		parametro = 'D';
	else
		parametro = 'R';

	if(lista)
		delete lista;
	lista = new Lista();

	for(i=0; i<DmNumRecords(db); i++)
	{
		bool encontrado = false;
		MemHandle h = DmQueryRecord(db, i);
		R_Produto* p = (R_Produto*)MemHandleLock(h);
		if(campo == NULL)
			encontrado = true;
		else if(parametro = 'R')
		{
			if(StrCompare(campo, p->referencia) == 0)
				encontrado = true;
		}
		else
		{
			if(StrStr(p->descricao, campo) != NULL)
				encontrado = true;
		}
		if(encontrado) // TODO - vê se fecha com o critério
		{
			falta--;
			if (ct < 7 && falta <= 0)
			{
				lista->adicionaRegistro(i, p->descricao);
				ct++;
			}
			numRegistros++;
		}
		MemHandleUnlock(h);
	}

	lista->setItensLista((ListType*)getControl(BuscaProdutoLista), 7, false);

	if(numRegistros > 7)
		SclSetScrollBar((ScrollBarType*)getControl(BuscaProdutoScroll),
				itemNoTopo, 1, numRegistros-6, 4);
	else
		SclSetScrollBar((ScrollBarType*)getControl(BuscaProdutoScroll),
				1, 1, 1, 4);
}