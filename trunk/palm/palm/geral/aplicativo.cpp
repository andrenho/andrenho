#include "aplicativo.h"

Aplicativo* app;

Aplicativo::Aplicativo()
{
	dbCliente = new DBCliente();
	dbCidade = new DBCidade();
	dbPedido = new DBPedido();
	buscaCliente = new BuscaCliente();
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

	delete dbCliente;
	delete buscaCliente;
	delete dbCidade;
	delete dbPedido;
}
