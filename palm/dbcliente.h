#ifndef DBCLIENTE_H
#define DBCLIENTE_H

#include "database.h"

class R_Cliente : public Registro
{
public:
	Char* CNPJ;
	Char* Fantasia;
	Char* RazaoSocial;
	Char* traducao();
};

class DBCliente : public Database
{
public:
	DBCliente();
	~DBCliente();

	void populateDB();

private:
	const Char* dbName() { return "WagnClientesDB"; }
};

#endif
