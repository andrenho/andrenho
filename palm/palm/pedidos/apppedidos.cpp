#include "apppedidos.h"
#include "palmincludes.h"

AppPedidos* appPedidos;

AppPedidos::AppPedidos() : Aplicativo(1)
{
	Preferencias pref;
	PrefGeral* g;

	dbCliente = new DBCliente();
	dbCidade = new DBCidade();
	dbPedido = new DBPedido();
	dbPedidoItem = new DBPedidoItem();
	dbProduto = new DBProduto();

	buscaCliente = new BuscaCliente();

	frmPrincipal = new FrmPrincipal();
	frmPedido = new FrmPedido();
	frmItens = new FrmItens();
	frmNovoItem = new FrmNovoItem();
	frmFinaliza = new FrmFinaliza();

	if(this->preferencias == NULL)
		current = frmPrincipal;
		// current = frmNovoItem;
	else   
	{
		g = (PrefGeral*)this->preferencias;
		switch(g->numeroForm)
		{
			case N_FORM_PEDIDO:
				current = frmPedido;
				break;
			case N_FORM_ITENS:
				current = frmItens;
				break;
			case N_FORM_NOVO_ITEM:
				current = frmNovoItem;
				break;
			case N_FORM_FINALIZA:
				current = frmFinaliza;
				break;
			default:
				current = frmPrincipal;
				break;
		}
		current->carregaPreferencias = true;
	}
}

AppPedidos::~AppPedidos()
{
	delete dbProduto;
	delete dbCliente;
	delete dbCidade;
	delete dbPedido;
	delete dbPedidoItem;

	delete buscaCliente;

	delete frmFinaliza;
	delete frmNovoItem;
	delete frmItens;
	delete frmPedido;
	delete frmPrincipal;
}

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	if (cmd == sysAppLaunchCmdNormalLaunch)
	{
		app = new AppPedidos();
		appPedidos = (AppPedidos*)app;
		app->executar(cmd);
		delete appPedidos;
	}
}
