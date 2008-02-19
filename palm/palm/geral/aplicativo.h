#ifndef APLICATIVO_H
#define APLICATIVO_H

#include "palmincludes.h"
#include "pform.h"
#include "buscacliente.h"
#include "dbcliente.h"
#include "dbcidade.h"
#include "dbpedido.h"
#include "debug.h"

typedef enum { NonModal, Modal, ReturnFromModal } FrmType;
typedef struct
{
	int numeroForm;
	void* data;
} PrefGeral;

class Aplicativo
{
public:
	Aplicativo(int numeroAplicativo);
	~Aplicativo();

	void executar(UInt16 cmd);

	Form* current;
	BuscaCliente* buscaCliente;

	DBCliente* dbCliente;
	DBCidade* dbCidade;
	DBPedido* dbPedido;
	
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
