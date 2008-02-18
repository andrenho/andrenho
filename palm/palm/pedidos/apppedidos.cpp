#include "apppedidos.h"
#include "palmincludes.h"

AppPedidos* appPedidos;

AppPedidos::AppPedidos() : Aplicativo()
{
	frmPrincipal = new FrmPrincipal();
	frmPedido = new FrmPedido();
	frmItens = new FrmItens();

	current = frmPrincipal;
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
	delete app;
}
