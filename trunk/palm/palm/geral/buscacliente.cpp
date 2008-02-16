#include "buscacliente.h"
#include "extern.h"

BuscaCliente::BuscaCliente()
{
	this->id = BuscaClienteFrm;
}

bool BuscaCliente::event(UInt16 controlID, eventsEnum evt)
{
	if(evt == ctlSelectEvent)
		switch(controlID)
		{
		}
	return false;
}

void BuscaCliente::loadData()
{
}

void BuscaCliente::busca(Form* caller, UInt16 campoCNPJ, UInt16 campoFantasia, UInt16 campoRazaoSocial)
{
	int i, n, c = 0;
	MemPtr p;
	MemHandle mh[200]; // max clientes
	Char* fantasia = FldGetTextPtr((FieldType*)caller->getControl(campoFantasia));
	
	if(fantasia == NULL)
		return;
	if(StrCompare(fantasia, "") == 0)
		return;

	n = StrLen(fantasia);

	// pega handles para todos os clientes
	for(i=0; i<DmNumRecords(dbCliente->db); i++)
	{
		MemHandle h = DmQueryRecord(dbCliente->db, i);
		p = MemHandleLock(h);
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
		FrmAlert(ClienteNaoExiste);
	else if(c == 1)
	{
		R_Cliente* r = (R_Cliente*)MemHandleLock(mh[0]);
		caller->setField(campoCNPJ, r->CNPJ);
		caller->setField(campoFantasia, r->Fantasia);
		if(campoRazaoSocial)
		 	caller->setField(campoRazaoSocial, r->RazaoSocial);
		MemHandleUnlock(mh[0]);
	}
	else
		FrmAlert(ToBeDone);

	// libera os handles
	for(i=0; i<c; i++)
		MemHandleUnlock(mh[i]);
}
