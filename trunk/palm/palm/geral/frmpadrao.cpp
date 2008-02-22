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
		}
	return false;
}

void FrmEnvio::gravarPreferencias()
{
	Preferencias pref;
	PrefEnvio p;

	p.numeroForm = N_FORM_ENVIO;
	
	pref.salvar((void*)&p, sizeof(PrefEnvio));
}

void FrmEnvio::carregarPreferencias()
{
	PrefEnvio* p = (PrefEnvio*)appPedidos->preferencias;

	this->carregaPreferencias = true;
}

