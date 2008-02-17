#include "dbpedido.h"

DBPedido::DBPedido()
{
	if(!openDB())
		throw "O BD dos pedidos não pôde ser aberto.";
}
