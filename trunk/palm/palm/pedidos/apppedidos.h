#ifndef APPPEDIDOS_H
#define APPPEDIDOS_H

#include "aplicativo.h"
#include "frmprincipal.h"
#include "frmpedido.h"
#include "frmitens.h"
#include "frmnovoitem.h"
#include "frmfinaliza.h"

class AppPedidos : public Aplicativo
{
public:
	AppPedidos();
	~AppPedidos();
	void inicializacao();

	FrmPrincipal* frmPrincipal;
	FrmPedido* frmPedido;
	FrmItens* frmItens;
	FrmNovoItem* frmNovoItem;
	FrmFinaliza* frmFinaliza;

	int numeroAplicativo() { return 1; }
};

extern AppPedidos* appPedidos;

#endif
