#ifndef DBPARCELA_H
#define DBPARCELA_H

#include "database.h"

typedef struct
{
	int n;
	int dias;
	float perc;
} R_Parcela;

class DBParcela : public Database
{
public:
	DBParcela();

	void populateDB();
private:
	const Char* dbName() { return "WGSFParcelasDB"; }
};

#endif


