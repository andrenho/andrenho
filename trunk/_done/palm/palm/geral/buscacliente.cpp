#include "buscacliente.h"
#include "aplicativo.h"

BuscaCliente::BuscaCliente()
{
	this->id = BuscaClienteFrm;
}

bool BuscaCliente::event(UInt16 controlID, EventType *e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
		}
	return false;
}

bool BuscaCliente::busca(Form* caller, UInt16 campoCNPJ, UInt16 campoFantasia, UInt16 campoRazaoSocial, int cidade)
{
	int i, n, c = 0;
	bool rt = false;
	MemPtr p;
	MemHandle mh[200]; // max clientes
	Char* fantasia = FldGetTextPtr((FieldType*)caller->getControl(campoFantasia));
	
	if(fantasia == NULL)
		goto buscaClientes;
	if(StrCompare(fantasia, "") == 0)
		goto buscaClientes;

	n = StrLen(fantasia);

	// pega handles para todos os clientes
	for(i=0; i<DmNumRecords(app->dbCliente->db); i++)
	{
		MemHandle h = DmQueryRecord(app->dbCliente->db, i);
		p = MemHandleLock(h);
		if(((R_Cliente*)p)->cidade != cidade && cidade != -1)
		{
			MemHandleUnlock(h);
			continue;
		}
		if(StrNCaselessCompare(fantasia, ((R_Cliente*)p)->Fantasia, n) == 0)
		{
			mh[c] = h;
			c++;
		}
		else
			MemHandleUnlock(h);
		if(c >= 200)
			break;
	}

	if(c == 0)
	{
		displayAlert(ClienteNaoExiste);
		rt = false;
	}
	else if(c == 1)
	{
		R_Cliente* r = (R_Cliente*)MemHandleLock(mh[0]);
		caller->setField(campoCNPJ, r->CNPJ);
		caller->setField(campoFantasia, r->Fantasia);
		if(campoRazaoSocial)
		 	caller->setField(campoRazaoSocial, r->RazaoSocial);
		MemHandleUnlock(mh[0]);
		rt = true;
	}
	else
buscaClientes:
		displayAlert(ToBeDone);

	// libera os handles
	for(i=0; i<c; i++)
		MemHandleUnlock(mh[i]);

	return rt;
}
