#ifndef DBPRODUTO_H
#define DBPRODUTO_H

#include "database.h"
#include "segment.h"

#define GRUPO_CHARS 3
#define NUMERO_PRODUTO_CHARS 5
#define DESC_PRODUTO_CHARS 100
#define UNID_MEDIDA_CHARS 3

typedef struct
{
	int n;
	char tipo[GRUPO_CHARS];
	char grupo[GRUPO_CHARS];
	char subgrupo1[GRUPO_CHARS];
	char subgrupo2[GRUPO_CHARS];
	char subgrupo3[GRUPO_CHARS];
	char numero[NUMERO_PRODUTO_CHARS];
	char descricao[DESC_PRODUTO_CHARS];
	char unid_medida[UNID_MEDIDA_CHARS];
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

