#include "dbparcela.h"

DBParcela::DBParcela()
{
	if(!openDB())
		throw "O BD dos pagamentos não pôde ser aberto.";
}

void DBParcela::populateDB()
{
	R_Parcela p;
	p.n = 2;
	p.dias = 30;
	p.perc = 0.5;
	adicionaRegistro(&p, sizeof(R_Parcela));

	p.n = 2;
	p.dias = 60;
	p.perc = 0.5;
	adicionaRegistro(&p, sizeof(R_Parcela));
}
