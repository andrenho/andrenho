#include "frmcidades.h"

FrmCidades::FrmCidades()
{
	this->id = CidadesFrm;
}

bool FrmCidades::event(UInt16 controlID, eventsEnum evt)
{
	if(evt == ctlSelectEvent)
		switch(controlID)
		{
			case CidadesOK:
				returnValue = NULL;
				this->leave_form = true;
				return true;
		}
	return false;
}

void FrmCidades::loadData()
{
}
