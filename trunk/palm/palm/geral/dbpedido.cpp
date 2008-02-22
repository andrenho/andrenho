#include "dbpedido.h"
#include "aplicativo.h"
#include "debug.h"

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

void DBPedido::excluirPedido(int n)
{
	int i;

	app->dbPedidoItem->excluirItens(n);

	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmQueryRecord(db, i);
		R_Pedido* p = (R_Pedido*)MemHandleLock(h);
		if(p->n == n)
		{
			int resp;
			MemHandleUnlock(h);
			resp = DmRemoveRecord(db, i);
			ErrNonFatalDisplayIf(resp == dmErrReadOnly, "dmErrReadOnly excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == dmErrIndexOutOfRange, "dmErrIndexOutOfRange excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == dmErrNotRecordDB, "dmErrNotRecordDB excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == memErrChunkLocked, "memErrChunkLocked excluindo registro de pedido");
			ErrNonFatalDisplayIf(resp == memErrInvalidParam, "memErrInvalidParam excluindo registro de pedido");
		}
		else	
			MemHandleUnlock(h);
	}
}

void DBPedido::encerraPedido(int nPedido, int pagamento, double valorDesconto)
{
	int i;
	for(i=0; i<DmNumRecords(db); i++)
	{
		MemHandle h = DmGetRecord(db, i);
		R_Pedido* p = (R_Pedido*)MemHandleLock(h);
		if(p->n == nPedido)
		{
			debug("vai escrever");
			p->status = INSERIDO;
			p->pagamento = pagamento;
			p->vlrDesconto = valorDesconto;
			debug("escrito");
		}
		MemHandleUnlock(h);
		DmReleaseRecord(db, i, false);
	}
}
