#include "frmnovoitem.h"
#include "apppedidos.h"

typedef struct
{
	int numeroForm;
} PrefNovoItem;

FrmNovoItem::FrmNovoItem() : Form()
{
	this->id = NovoItemFrm;
}

bool FrmNovoItem::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
		}
	return false;
}

void FrmNovoItem::carregarPreferencias()
{
	PrefNovoItem* p = (PrefNovoItem*)appPedidos->preferencias;
	this->carregaPreferencias = false;
}

void FrmNovoItem::gravarPreferencias()
{
	PrefNovoItem p;
	Preferencias pref;

	p.numeroForm = N_FORM_NOVO_ITEM;
	
	pref.salvar((void*)&p, sizeof(PrefNovoItem));
}
