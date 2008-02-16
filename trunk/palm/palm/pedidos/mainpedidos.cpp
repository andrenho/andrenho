#include "palmincludes.h"
#include "main.h"
#include "extern_pedidos.h"

Principal* principal;
Pedido* pedido;
Itens* itens;

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	principal = new Principal();
	pedido = new Pedido();
	itens = new Itens();
	
	current = principal;

	mainGeral(cmd);

	delete itens;
	delete pedido;
	delete principal;

	return 0;
}
