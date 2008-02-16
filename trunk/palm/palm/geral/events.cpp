#include "events.h"
#include "extern.h"

Form* initial;
BuscaCliente* buscaCliente;
DBCliente* dbCliente;

void mainGeral(UInt16 cmd)
{
	dbCliente = new DBCliente();
	buscaCliente = new BuscaCliente();

	if (cmd == sysAppLaunchCmdNormalLaunch)
	{
		initial->open();
		FrmCloseAllForms();
	}

	delete dbCliente;
	delete buscaCliente;
}
