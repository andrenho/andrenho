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
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->pedido == nPedido)
			if(p->n > i)
				i = p->n;
		MemHandleUnlock(h);
	}

	return max;
}

int DBPedidoItem::numeroItens(int nPedido)
{
	int i, ct = 0;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->pedido == nPedido)
			ct++;
		MemHandleUnlock(h);
	}

	return ct;
}

double DBPedidoItem::valorPedido(int nPedido)
{
	int i;
	double valor;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->pedido == nPedido)
			valor += (p->quantidade * p->valor);
		MemHandleUnlock(h);
	}

	return valor;
}

void DBPedidoItem::excluirItem(int pedido, int item)
{
	int i;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->pedido == pedido && p->n == item)
		{
			int resp;
			MemHandleUnlock(h);
			resp = DmRemoveRecord(db, i);
			ErrNonFatalDisplayIf(resp == dmErrReadOnly, "dmErrReadOnly excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == dmErrIndexOutOfRange, "dmErrIndexOutOfRange excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == memErrChunkLocked, "memErrChunkLocked excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == memErrInvalidParam, "memErrInvalidParam excluindo registro de pedido");
		}
		else	
			MemHandleUnlock(h);
	}
}

void DBPedidoItem::excluirItens(int pedido)
{
	int i;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		if(p->pedido == pedido)
		{
			int resp;
			MemHandleUnlock(h);
			resp = DmRemoveRecord(db, i);
			ErrNonFatalDisplayIf(resp == dmErrReadOnly, "dmErrReadOnly excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == dmErrIndexOutOfRange, "dmErrIndexOutOfRange excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == memErrChunkLocked, "memErrChunkLocked excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == memErrInvalidParam, "memErrInvalidParam excluindo registro de pedido");
		}
		else	
			MemHandleUnlock(h);
	}
}

bool DBPedidoItem::atualizaRegistro(void* r)
{
	int i;
	R_PedidoItem *n = (R_PedidoItem*)r;

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmGetRecord(db, i);
		R_PedidoItem* p = (R_PedidoItem*)MemHandleLock(h);
		MemHandle novoH;
		R_PedidoItem* novo;

		if(p->pedido == n->pedido && p->n == n->n)
		{
			novoH = MemHandleNew(sizeof(R_PedidoItem));
			novo = (R_PedidoItem*)MemHandleLock(novoH);
			MemMove(novo, n, sizeof(R_PedidoItem));
			DmWrite(p, 0, novo, sizeof(R_PedidoItem));
			MemHandleUnlock(novoH);
			MemHandleFree(novoH);
		}
		MemHandleUnlock(h);
		DmReleaseRecord(db, i, false);
	}

	return true;
}
