#include "dbproduto.h"

DBProduto::DBProduto()
{
	if(!openDB())
		throw "O BD dos produtos não pôde ser aberto.";
}

void DBProduto::populateDB()
{
	R_Produto p;
	p.n = 1;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));
}
