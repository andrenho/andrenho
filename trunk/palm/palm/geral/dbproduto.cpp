#include "dbproduto.h"

DBProduto::DBProduto()
{
	if(!openDB())
		throw "O BD dos produtos não pôde ser aberto.";
}

void DBProduto::populateDB()
{
	R_Produto p;
	StrCopy(p.tipo, "01");
	StrCopy(p.grupo, "01");
	StrCopy(p.subgrupo1, "01");
	StrCopy(p.subgrupo2, "01");
	StrCopy(p.subgrupo3, "01");
	StrCopy(p.numero, "001");
	StrCopy(p.descricao, "Produto teste");
	StrCopy(p.unid_medida, "UN");
	adicionaRegistro(&p, sizeof(R_Produto));
}
