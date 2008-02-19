#include "apppedidos.h"
#include "palmincludes.h"

AppPedidos* appPedidos;

AppPedidos::AppPedidos() : Aplicativo(1)
{
	Preferencias pref;
	PrefGeral* g;

	frmPrincipal = new FrmPrincipal();
	frmPedido = new FrmPedido();
	frmItens = new FrmItens();

	if(this->preferencias == NULL)
		current = frmPrincipal;
	else 
	{
		g = (PrefGeral*)this->preferencias;
		if(g->numeroForm == N_FORM_PEDIDO)
			current = frmPedido;
		else
			current = frmPrincipal;
		current->carregaPreferencias = true;
	}
}

AppPedidos::~AppPedidos()
{
	delete frmItens;
	delete frmPedido;
	delete frmPrincipal;
}

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	app = new AppPedidos();
	appPedidos = (AppPedidos*)app;
	app->executar(cmd);
	delete appPedidos;
}
