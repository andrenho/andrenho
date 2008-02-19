#ifndef DBPEDIDOITEM_H
#define DBPEDIDOITEM_H

#include "database.h"
#include "dbpedido.h"
#include "dbpedidoitem.h"

typedef struct
{
	int pedido;
	int n;
	int produto;
	double quantidade;
	double valor;
	DateType dataEntrega;
} R_PedidoItem;

class DBPedidoItem : public Database
{
public:
	DBPedidoItem();
	int ultimoItem(int nPedido);
private:
	const Char* dbName() { return "WGSFPedItensDB"; }
};

#endif
