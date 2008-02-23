#ifndef DBPEDIDOITEM_H
#define DBPEDIDOITEM_H

#include "database.h"
#include "dbpedido.h"
#include "dbpedidoitem.h"
#include "dbproduto.h"
#include "segment.h"

typedef struct
{
	int pedido;
	int n;
	int produto;
	double quantidade;
	double valor;
	DateType dataEntrega;
	char descProduto[DESC_PRODUTO_CHARS];
} R_PedidoItem;

class DBPedidoItem : public Database
{
public:
	DBPedidoItem() GERAL;
	int ultimoItem(int nPedido) GERAL;
	int numeroItens(int nPedido) GERAL;
	double valorPedido(int nPedido) GERAL;
	void excluirItem(int pedido, int item) GERAL;
	void excluirItens(int pedido) GERAL;
private:
	const Char* dbName() { return "WGSFPedItensDB"; }
};

#endif
