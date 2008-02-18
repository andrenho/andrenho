#include "dbpedido.h"

DBPedido::DBPedido()
{
	if(!openDB())
		throw "O BD dos pedidos não pôde ser aberto.";
}

int DBPedido::ultimoPedido()
{
	int i, max = 0;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_Pedido* p = (R_Pedido*)MemHandleLock(h);
		if(p->n > i)
			i = p->n;
		MemHandleUnlock(h);
	}

	return max;
}
