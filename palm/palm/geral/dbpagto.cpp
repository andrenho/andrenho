#include "dbpagto.h"

DBPagto::DBPagto()
{
	if(!openDB())
		throw "O BD dos pagamentos não pôde ser aberto.";
}

void DBPagto::populateDB()
{
	R_Pagto p, p2;

	p.n = 1;
	StrCopy(p.descricao, "À Vista");
	adicionaRegistro(&p, sizeof(R_Pagto));

	p2.n = 2;
	StrCopy(p2.descricao, "30/60 dias");
	adicionaRegistro(&p2, sizeof(R_Pagto));
}

int DBPagto::numeroPagtos()
{
	return DmNumRecords(db);
}
