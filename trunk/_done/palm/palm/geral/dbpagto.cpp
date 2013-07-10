#include "dbpagto.h"

DBPagto::DBPagto()
{
	if(!openDB())
		throw "O BD dos pagamentos não pôde ser aberto.";
}

void DBPagto::populateDB()
{
	R_Pagto p, p2, p3;

	p.n = 1;
	StrCopy(p.descricao, "À Vista");
	adicionaRegistro(&p, sizeof(R_Pagto));

	p2.n = 2;
	StrCopy(p2.descricao, "30/60 dias");
	adicionaRegistro(&p2, sizeof(R_Pagto));

	p3.n = 3;
	StrCopy(p3.descricao, "15/30 dias");
	adicionaRegistro(&p3, sizeof(R_Pagto));
}

int DBPagto::numeroPagtos()
{
	return DmNumRecords(db);
}

void DBPagto::alimentaLista(Lista* l)
{
	int i, max=0;
	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_Pagto* p = (R_Pagto*)MemHandleLock(h);
		l->adicionaRegistro(p->n, p->descricao);
		MemHandleUnlock(h);
	}
	l->adicionaRegistro(0, "Outro...");
}
