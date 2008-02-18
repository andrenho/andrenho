#include "frmitens.h"

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
		}
	return false;
}
