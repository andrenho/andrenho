#include "main.h"
#include "extern.h"

Form* current;
BuscaCliente* buscaCliente;
DBCliente* dbCliente;
bool appActive;

void mainGeral(UInt16 cmd)
{
	appActive = true;

	dbCliente = new DBCliente();
	buscaCliente = new BuscaCliente();

	if (cmd == sysAppLaunchCmdNormalLaunch)
		while(appActive)
			current->open();

	FrmCloseAllForms();

	delete dbCliente;
	delete buscaCliente;
}
