#include "dbcliente.h"

DBCliente::DBCliente()
{
	if(!openDB())
		throw "O BD dos clientes não pôde ser abero.";
}

DBCliente::~DBCliente()
{
	closeDB();
}

void DBCliente::populateDB()
{
	R_Cliente r;
	StrCopy(r.CNPJ, "12345");
	StrCopy(r.Fantasia, "Andre");
	StrCopy(r.RazaoSocial, "André Wagner");

	adicionaRegistro(&r, sizeof(R_Cliente));
}

Char* DBCliente::buscaCNPJ(Char* fantasia)
{
	MemPtr p;
	R_Cliente* r;
	int i;

	for(i=0; i<DmNumRecords(this->db); i++)
	{
		MemHandle h = DmQueryRecord(this->db, i);
		p = MemHandleLock(h);
		r = (R_Cliente *)p;
		if(StrCaselessCompare(fantasia, r->Fantasia) == 0)
		{
			MemHandleUnlock(h);
			return "xxx";
			// return
		}
		MemHandleUnlock(h);
	}
	
	return NULL;
}
