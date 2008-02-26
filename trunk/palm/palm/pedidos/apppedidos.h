#ifndef APPPEDIDOS_H
#define APPPEDIDOS_H

#include "aplicativo.h"
#include "frmprincipal.h"
#include "frmconsulta.h"
#include "frmpedido.h"
#include "frmitens.h"
#include "frmnovoitem.h"
#include "frmfinaliza.h"
#include "frmenvio.h"

class AppPedidos : public Aplicativo
{
public:
	AppPedidos();
	~AppPedidos();
	void inicializacao();

	FrmPrincipal* frmPrincipal;
	FrmConsulta* frmConsulta;
	FrmPedido* frmPedido;
	FrmItens* frmItens;
	FrmNovoItem* frmNovoItem;
	FrmFinaliza* frmFinaliza;
	FrmEnvio* frmEnvio;

	int numeroAplicativo() { return 1; }
};

extern AppPedidos* appPedidos;

#endif
