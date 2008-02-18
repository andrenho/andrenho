#ifndef APLICATIVO_H
#define APLICATIVO_H

#include "palmincludes.h"
#include "pform.h"
#include "preferencias.h"
#include "buscacliente.h"
#include "dbcliente.h"
#include "dbcidade.h"
#include "dbpedido.h"

typedef enum { NonModal, Modal, ReturnFromModal } FrmType;

class Aplicativo
{
public:
	Aplicativo();
	~Aplicativo();

	void executar(UInt16 cmd);

	Form* current;
	BuscaCliente* buscaCliente;

	DBCliente* dbCliente;
	DBCidade* dbCidade;
	DBPedido* dbPedido;
	
	bool appActive;
	FrmType frmType;
};

extern Aplicativo* app;

#endif
