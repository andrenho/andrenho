#ifndef DBPEDIDO_H
#define DBPEDIDO_H

#include "database.h"
#include "dbcliente.h"

typedef enum
{
	DIGITANDO, INSERIDO
} STATUS;

typedef struct Pedido
{
	int n;
	char cnpj[CNPJ_CHARS];
	STATUS status;
} R_Pedido;

class DBPedido : public Database
{
public:
	DBPedido();
	int ultimoPedido();
private:
	const Char* dbName() { return "WGSFPedidosDB"; }
};

#endif
