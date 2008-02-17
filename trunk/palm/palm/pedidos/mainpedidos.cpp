#include "palmincludes.h"
#include "main.h"
#include "extern_pedidos.h"

FrmPrincipal* frmPrincipal;
FrmPedido* frmPedido;
FrmItens* frmItens;

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	frmPrincipal = new FrmPrincipal();
	frmPedido = new FrmPedido();
	frmItens = new FrmItens();
	
	current = frmPrincipal;

	mainGeral(cmd);

	delete frmItens;
	delete frmPedido;
	delete frmPrincipal;

	return 0;
}
