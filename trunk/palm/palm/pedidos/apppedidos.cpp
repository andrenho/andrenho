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
	dbPagto = new DBPagto();
	dbParcela = new DBParcela();

	buscaCliente = new BuscaCliente();

	frmPrincipal = new FrmPrincipal();
	frmConsulta = new FrmConsulta();
	frmPedido = new FrmPedido();
	frmItens = new FrmItens();
	frmNovoItem = new FrmNovoItem();
	frmFinaliza = new FrmFinaliza();
	frmEnvio = new FrmEnvio();

	if(this->preferencias == NULL)
		current = frmPrincipal;
		//current = frmEnvio;
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
			case N_FORM_ENVIO:
				current = frmEnvio;
				break;
			default:
				current = frmPrincipal;
				break;
		}
		current->carregaPreferencias = true;
	}
}

void AppPedidos::inicializacao()
{
	frmFinaliza->inicializacao();
}

AppPedidos::~AppPedidos()
{
	delete dbProduto;
	delete dbCliente;
	delete dbCidade;
	delete dbPedido;
	delete dbPedidoItem;
	delete dbPagto;
	delete dbParcela;

	delete buscaCliente;

	delete frmEnvio;
	delete frmFinaliza;
	delete frmNovoItem;
	delete frmItens;
	delete frmPedido;
	delete frmConsulta;
	delete frmPrincipal;
}

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	if (cmd == sysAppLaunchCmdNormalLaunch)
	{
		app = new AppPedidos();
		appPedidos = (AppPedidos*)app;
		appPedidos->inicializacao();
		appPedidos->executar(cmd);
		delete appPedidos;
	}
}
