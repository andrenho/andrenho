#include "main.h"
#include "extern.h"

Form* current;
BuscaCliente* buscaCliente;
FrmCidades* frmCidades;
DBCliente* dbCliente;
bool appActive;
FrmType frmType;

void mainGeral(UInt16 cmd)
{
	appActive = true;

	dbCliente = new DBCliente();
	buscaCliente = new BuscaCliente();
	frmCidades = new FrmCidades();
	frmType = NonModal;

	if (cmd == sysAppLaunchCmdNormalLaunch)
		while(appActive)
			current->open();

	FrmCloseAllForms();

	delete dbCliente;
	delete buscaCliente;
	delete frmCidades;
}
