#ifndef DBPAGTO_H
#define DBPAGTO_H

#include "database.h"
#include "lista.h"
#include "segment.h"

typedef struct
{
	int n;
	char descricao[30];
} R_Pagto;

class DBPagto : public Database
{
public:
	DBPagto() GERAL;
	int numeroPagtos() GERAL;
	void alimentaLista(Lista* l) GERAL;

	void populateDB() GERAL;
private:
	const Char* dbName() { return "WGSFPagtosDB"; }
};

#endif

