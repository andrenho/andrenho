#ifndef APPPEDIDOS_H
#define APPPEDIDOS_H

#include "aplicativo.h"
#include "frmprincipal.h"
#include "frmpedido.h"
#include "frmitens.h"

class AppPedidos : public Aplicativo
{
public:
	AppPedidos();
	~AppPedidos();

	FrmPrincipal* frmPrincipal;
	FrmPedido* frmPedido;
	FrmItens* frmItens;
};

extern AppPedidos* appPedidos;

#endif
