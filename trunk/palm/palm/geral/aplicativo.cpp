#include "aplicativo.h"

Aplicativo* app;

Aplicativo::Aplicativo(int numeroAplicativo)
{
	Preferencias pref;
	int n;

	dbCliente = new DBCliente();
	dbCidade = new DBCidade();
	dbPedido = new DBPedido();
	dbPedidoItem = new DBPedidoItem();
	dbProduto = new DBProduto();
	buscaCliente = new BuscaCliente();

	this->numeroAplicativo = numeroAplicativo;
	n = pref.tamanhoDados(numeroAplicativo);
	if(n > 0)
	{
		h = MemHandleNew(n);
		preferencias = MemHandleLock(h);
		pref.ler(numeroAplicativo, preferencias);
	}
	else
		preferencias = NULL;
}

void Aplicativo::executar(UInt16 cmd)
{
	appActive = true;

	frmType = NonModal;

	if (cmd == sysAppLaunchCmdNormalLaunch)
		while(appActive)
			current->open();
	current->gravarPreferencias();
}

Aplicativo::~Aplicativo()
{
	FrmCloseAllForms();

	if(preferencias != NULL)
	{
		MemHandleUnlock(h);
		MemHandleFree(h);
	}

	delete dbProduto;
	delete dbCliente;
	delete buscaCliente;
	delete dbCidade;
	delete dbPedido;
	delete dbPedidoItem;
}
