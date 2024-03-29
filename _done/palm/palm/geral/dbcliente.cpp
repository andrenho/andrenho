#include "dbcliente.h"

DBCliente::DBCliente()
{
	if(!openDB())
		throw "O BD dos clientes n�o p�de ser aberto.";
}

void DBCliente::populateDB()
{
	R_Cliente r;
	StrCopy(r.CNPJ, "12345");
	StrCopy(r.Fantasia, "Andre");
	StrCopy(r.RazaoSocial, "Andr� Wagner");
	r.cidade = 1;
	StrCopy(r.Email, "andre.nho@gmail.com");

	adicionaRegistro(&r, sizeof(R_Cliente));
}
/*
R_Cliente* DBCliente::busca(Char* fantasia, bool parcial)
{
	MemPtr p;
	R_Cliente* r;
	int i, n;

	if(fantasia == NULL)
		return NULL;
	if(StrCompare(fantasia, "") == 0)
		return NULL;

	if(parcial)
		n = StrLen(fantasia);

	for(i=0; i<DmNumRecords(this->db); i++)
	{
		MemHandle h = DmQueryRecord(this->db, i);
		p = MemHandleLock(h);
		r = (R_Cliente *)p;
		if(parcial)
			if(StrNCaselessCompare(fantasia, r->Fantasia, n) == 0)
			{
				MemHandleUnlock(h);
				return r;
			}
		else
			if(StrCaselessCompare(fantasia, r->Fantasia) == 0)
			{
				MemHandleUnlock(h);
				return r;
			}
		MemHandleUnlock(h);
	}
	
	return NULL;
}

R_Cliente* DBCliente::nComecandoCom(Char* fantasia)
{
	MemPtr p;
	R_Cliente* r;
	int c, i, n;

	if(fantasia == NULL)
		return 0;
	if(StrCompare(fantasia, "") == 0)
		return 0;

	n = StrLen(fantasia);
	for(i=0; i<DmNumRecords(this->db); i++)
	{
		MemHandle h = DmQueryRecord(this->db, i);
		p = MemHandleLock(h);
		r = (R_Cliente *)p;
		if(StrNCaselessCompare(fantasia, r->Fantasia, n) == 0)
			c++;
		MemHandleUnlock(h);
	}
	
	return i;
}
*/
