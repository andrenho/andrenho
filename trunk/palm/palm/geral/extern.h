#ifndef EXTERN_H
#define EXTERN_H

#include "pform.h"
#include "preferencias.h"
#include "buscacliente.h"
#include "dbcliente.h"
#include "dbcidade.h"
#include "dbpedido.h"

typedef enum { NonModal, Modal, ReturnFromModal } FrmType;

extern Form* current;
extern BuscaCliente* buscaCliente;
extern DBCliente* dbCliente;
extern DBCidade* dbCidade;
extern DBPedido* dbPedido;
extern bool appActive;
extern FrmType frmType;

#endif
