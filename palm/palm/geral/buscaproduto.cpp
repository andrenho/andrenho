#include "buscaproduto.h"
#include "aplicativo.h"
#include "util.h"
#include "debug.h"

#define LABEL_REFERENCIA "Referência:"
#define LABEL_DESCRICAO  "Descrição:"

BuscaProduto::BuscaProduto()
{
	this->id = BuscaProdutoFrm;
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
		}
	return false;
}

int BuscaProduto::busca(Form* caller, UInt16 referencia, UInt16 descricao, UInt16 unidMedida)
{
	int i, ct = 0, only;
	R_Produto* p;
	Char* ref = FldGetTextPtr((FieldType*)caller->getControl(referencia));

	if(ref == NULL)
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
		return -1;
	}
}

void BuscaProduto::doAfterDrawing()
{
	CtlSetValue(getControl(BuscaProdutoReferencia), 1);
	setField(BuscaProdutoLabel, LABEL_REFERENCIA);
}