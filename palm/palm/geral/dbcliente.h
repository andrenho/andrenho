#ifndef DBCLIENTE_H
#define DBCLIENTE_H

#include "database.h"

#define CNPJ_CHARS 18
#define FANTASIA_CHARS 20
#define RAZAOSOCIAL_CHARS 50

typedef struct
{
	char CNPJ[CNPJ_CHARS];
	char Fantasia[FANTASIA_CHARS];
	char RazaoSocial[RAZAOSOCIAL_CHARS];
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
