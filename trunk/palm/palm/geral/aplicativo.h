#ifndef APLICATIVO_H
#define APLICATIVO_H

#include "palmincludes.h"
#include "pform.h"
#include "buscacliente.h"
#include "buscaproduto.h"
#include "dbcliente.h"
#include "dbcidade.h"
#include "dbpedido.h"
#include "dbpedidoitem.h"
#include "dbproduto.h"
#include "dbpagto.h"
#include "dbparcela.h"
#include "dbgrupo.h"
#include "debug.h"
#include "segment.h"

typedef enum { NonModal, Modal, ReturnFromModal } FrmType;
typedef struct
{
	int numeroForm;
	void* data;
} PrefGeral;

class Aplicativo
{
public:
	Aplicativo(int numeroAplicativo) GERAL;
	~Aplicativo() GERAL;

	void executar(UInt16 cmd) GERAL;

	Form* current;

	BuscaCliente* buscaCliente;
	BuscaProduto* buscaProduto;

	DBCliente* dbCliente;
	DBCidade* dbCidade;
	DBPedido* dbPedido;
	DBPedidoItem* dbPedidoItem;
	DBProduto* dbProduto;
	DBPagto* dbPagto;
	DBParcela* dbParcela;
	DBGrupo* dbGrupo;
	
	bool appActive;
	FrmType frmType;

	MemPtr preferencias;

	int numeroAplicativo;
private:
	MemHandle h;
};

extern Aplicativo* app;

#include "preferencias.h"

#endif
