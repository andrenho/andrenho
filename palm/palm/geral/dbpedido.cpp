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
		if(p->n > max)
			max = p->n;
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
		MemHandle novoH;
		R_Pedido* novo;

		if(p->n == nPedido)
		{
			novoH = MemHandleNew(sizeof(R_Pedido));
			novo = (R_Pedido*)MemHandleLock(novoH);
			MemMove(novo, p, sizeof(R_Pedido));
			novo->status = INSERIDO;
			novo->pagamento;
			novo->vlrDesconto;
			DmWrite(p, 0, novo, sizeof(R_Pedido));
			MemHandleUnlock(novoH);
			MemHandleFree(novoH);
		}
		MemHandleUnlock(h);
		DmReleaseRecord(db, i, false);
	}
}

int DBPedido::numeroPedidos()
{
	return DmNumRecords(db);
}
