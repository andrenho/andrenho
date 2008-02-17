#ifndef EXTERN_H
#define EXTERN_H

#include "pform.h"
#include "buscacliente.h"
#include "dbcliente.h"
#include "frmcidades.h"

typedef enum { NonModal, Modal, ReturnFromModal } FrmType;

extern Form* current;
extern BuscaCliente* buscaCliente;
extern FrmCidades* frmCidades;
extern DBCliente* dbCliente;
extern bool appActive;
extern FrmType frmType;

#endif
