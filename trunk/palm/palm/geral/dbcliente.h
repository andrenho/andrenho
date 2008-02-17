#ifndef DBCLIENTE_H
#define DBCLIENTE_H

#include "database.h"

typedef struct
{
	char CNPJ[18];
	char Fantasia[20];
	char RazaoSocial[50];
	int cidade;
} R_Cliente;

class DBCliente : public Database
{
public:
	DBCliente();

	void populateDB();
private:
	const Char* dbName() { return "WGSFClientesDB"; }
};

#endif
