#include "dbcidade.h"

DBCidade::DBCidade()
{
	if(!openDB())
		throw "O BD das cidades não pôde ser aberto.";
}

void DBCidade::populateDB()
{
	R_Cidade cidade, sl;

	cidade.codigo = 1;
	StrCopy(cidade.nome, "Novo Hamburgo");
	adicionaRegistro(&cidade, sizeof(R_Cidade));

	sl.codigo = 2;
	StrCopy(sl.nome, "São Leopoldo");
	adicionaRegistro(&sl, sizeof(R_Cidade));
}
