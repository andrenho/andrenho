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

	p.n = 2;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 2");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 3;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 3");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 4;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 4");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 5;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 5");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 6;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 6");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 7;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 7");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 8;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 8");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 9;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 9");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));

	p.n = 10;
	p.grupo = 2;
	StrCopy(p.descricao, "Produto teste 10");
	StrCopy(p.unid_medida, "UN");
	StrCopy(p.referencia, "1234");
	adicionaRegistro(&p, sizeof(R_Produto));
}
