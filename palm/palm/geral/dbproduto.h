#ifndef DBPRODUTO_H
#define DBPRODUTO_H

#include "database.h"
#include "segment.h"

#define DESC_PRODUTO_CHARS 100
#define UNID_MEDIDA_CHARS 3
#define REFERENCIA_CHARS 10

typedef struct
{
	int n;
	int grupo;
	char descricao[DESC_PRODUTO_CHARS];
	char unid_medida[UNID_MEDIDA_CHARS];
	char referencia[REFERENCIA_CHARS];
} R_Produto;

class DBProduto : public Database
{
public:
	DBProduto() GERAL;
	void populateDB() GERAL;
private:
	const Char* dbName() { return "WGSFProdutosDB"; }
};

#endif

