#include "frmitens.h"
#include "apppedidos.h"

typedef struct
{
	int numeroForm;
} PrefItens;

FrmItens::FrmItens() : Form()
{
	this->id = ItensFrm;
}

bool FrmItens::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case ItensCancelar:
				if(perguntaSimNao("Tem certeza que deseja cancelar a inclusão deste pedido?"))
					; // TODO
				break;
			case ItensNovo:
				goToForm(appPedidos->frmNovoItem);
				break;
		}
	return false;
}

void FrmItens::carregarPreferencias()
{
	PrefItens* p = (PrefItens*)appPedidos->preferencias;
	this->carregaPreferencias = false;
}

void FrmItens::gravarPreferencias()
{
	PrefItens p;
	Preferencias pref;

	p.numeroForm = N_FORM_ITENS;
	
	pref.salvar((void*)&p, sizeof(PrefItens));
}
