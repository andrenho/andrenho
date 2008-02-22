#ifndef DBPEDIDO_H
#define DBPEDIDO_H

#include "database.h"
#include "dbcliente.h"
#include "segment.h"

typedef enum
{
	DIGITANDO, INSERIDO
} STATUS;

typedef struct
{
	int n;
	char cnpj[CNPJ_CHARS];
	int pagamento;
	double vlrDesconto;
	STATUS status;
} R_Pedido;

class DBPedido : public Database
{
public:
	DBPedido() GERAL;
	int ultimoPedido() GERAL;
	void excluirPedido(int n) GERAL;
	void encerraPedido(int nPedido, int pagamento, double valorDesconto) GERAL;
private:
	const Char* dbName() { return "WGSFPedidosDB"; }
};

#endif
