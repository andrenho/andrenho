#include "frmprincipal.h"
#include "apppedidos.h"

typedef struct
{
	int numeroForm;
} PrefEnvio;

FrmEnvio::FrmEnvio()
{
	this->id = EnvioFrm;
}

bool FrmEnvio::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case EnvioOK:
				goToForm(appPedidos->frmPrincipal);
				break;
		}
	return false;
}

void FrmEnvio::doAfterDrawing()
{
	int i, j;

	Form::doAfterDrawing();

	// busca cnpj
	for(i=0; i<DmNumRecords(appPedidos->dbPedido->db); i++)
	{
		MemHandle h = DmQueryRecord(appPedidos->dbPedido->db, i);
		R_Pedido* p = (R_Pedido*)MemHandleLock(h);
		if(p->n == numeroPedido)
		{
			// busca e-mail - TODO fazer de uma forma mais rápida
			for(j=0; j<DmNumRecords(appPedidos->dbCliente->db); j++)
			{
				MemHandle h2 = DmQueryRecord(appPedidos->dbCliente->db, j);
				R_Cliente* p2 = (R_Cliente*)MemHandleLock(h2);
				if(StrCompare(p2->CNPJ, p->cnpj))
				{
					if(p2->Email)
						setField(EnvioEmailPara, p2->Email);
					MemHandleUnlock(h2);
					break;
				}
				MemHandleUnlock(h2);
			}
		}
		MemHandleUnlock(h);
	}
}

void FrmEnvio::gravarPreferencias()
{
	PrefEnvio p;
	Preferencias pref;

	p.numeroForm = N_FORM_ENVIO;
	
	pref.salvar((void*)&p, sizeof(PrefEnvio));
}

void FrmEnvio::carregarPreferencias()
{
	PrefEnvio* p = (PrefEnvio*)appPedidos->preferencias;

	this->carregaPreferencias = true;
}
