#ifndef DBGRUPO_H
#define DBGRUPO_H

#include "database.h"
#include "segment.h"

#define DESC_GRUPO_CHARS 20

typedef struct
{
	int n;
	char descricao[DESC_GRUPO_CHARS];
	int pai;
} R_Grupo;

class DBGrupo : public Database
{
public:
	DBGrupo() GERAL;
	void populateDB() GERAL;
private:
	const Char* dbName() { return "WGSFGruposDB"; }
};

#endif

