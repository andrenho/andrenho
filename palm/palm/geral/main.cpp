#include "main.h"
#include "extern.h"

Form* current;
BuscaCliente* buscaCliente;
DBCliente* dbCliente;
DBCidade* dbCidade;
bool appActive;
FrmType frmType;

void mainInit()
{
	dbCliente = new DBCliente();
	dbCidade = new DBCidade();
	buscaCliente = new BuscaCliente();
}

void mainGeral(UInt16 cmd)
{
	appActive = true;

	frmType = NonModal;

	if (cmd == sysAppLaunchCmdNormalLaunch)
		while(appActive)
			current->open();

	FrmCloseAllForms();

	delete dbCliente;
	delete buscaCliente;
	delete dbCidade;
}
