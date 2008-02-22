#ifndef DBCIDADE_H
#define DBCIDADE_H

#include "database.h"
#include "segment.h"

#define CIDADE_CHARS 30

typedef struct
{
	int codigo;
	char nome[CIDADE_CHARS];
} R_Cidade;

class DBCidade : public Database
{
public:
	DBCidade() GERAL;
	void populateDB() GERAL;
private:
	const Char* dbName() { return "WGSFCidadesDB"; }
};

#endif
