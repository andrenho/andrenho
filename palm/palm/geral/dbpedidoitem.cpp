#include "dbpedidoitem.h"

DBPedidoItem::DBPedidoItem()
{
	if(!openDB())
		throw "O BD dos itens de pedidos não pôde ser aberto.";
}

int DBPedidoItem::ultimoItem(int nPedido)
{
	int i, max = 0;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		// TODO procurar pedido
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->n > i)
			i = p->n;
		MemHandleUnlock(h);
	}

	return max;
}
