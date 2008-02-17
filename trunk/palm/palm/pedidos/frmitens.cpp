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
		}
	return false;
}

void FrmItens::loadData()
{
}
