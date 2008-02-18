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

	int numeroAplicativo() { return 1; }
};

extern AppPedidos* appPedidos;

#endif
