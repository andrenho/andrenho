#ifndef FORMS_H
#define FORMS_H

#include "pform.h"
#include "principal.h"
#include "pedido.h"
#include "itens.h"
#include "buscacliente.h"

#include "dbcliente.h"

Form* current;
Principal* principal;
Pedido* pedido;
Itens* itens;
BuscaCliente* buscaCliente;

DBCliente* dbCliente;

#endif
