#ifndef DBPAGTO_H
#define DBPAGTO_H

#include "database.h"

typedef struct
{
	int n;
	char descricao[30];
} R_Pagto;

class DBPagto : public Database
{
public:
	DBPagto();
	int numeroPagtos();

	void populateDB();
private:
	const Char* dbName() { return "WGSFPagtosDB"; }
};

#endif

