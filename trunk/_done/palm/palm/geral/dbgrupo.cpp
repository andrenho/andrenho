#include "dbgrupo.h"

DBGrupo::DBGrupo()
{
	if(!openDB())
		throw "O BD dos grupos não pôde ser aberto.";
}

void DBGrupo::populateDB()
{
	R_Grupo g;

	g.n = 1;
	StrCopy(g.descricao, "Produtos Teste");
	g.pai = 0;
	adicionaRegistro(&g, sizeof(R_Grupo));

	g.n = 2;
	StrCopy(g.descricao, "Grupo Teste");
	g.pai = 1;
	adicionaRegistro(&g, sizeof(R_Grupo));

	g.n = 3;
	StrCopy(g.descricao, "Outro");
	g.pai = 1;
	adicionaRegistro(&g, sizeof(R_Grupo));
}
