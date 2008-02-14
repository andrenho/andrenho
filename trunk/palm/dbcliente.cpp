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

Char* R_Cliente::traducao()
{
	Char* s;

	int n = StrLen(CNPJ) + StrLen(Fantasia) + StrLen(RazaoSocial) + 3;
	MemHandle h = MemHandleNew(n);
	s = (Char *)MemHandleLock(h);
	StrPrintF(s, "%s\1%s\1%s\1", CNPJ, Fantasia, RazaoSocial);
	MemHandleUnlock(h);

	return s;
}

void DBCliente::populateDB()
{
	R_Cliente* r = new R_Cliente();
	r->CNPJ = "12345";
	r->Fantasia = "Andre";
	r->RazaoSocial = "André Wagner";

	adicionaRegistro(r);

	delete r;
}
