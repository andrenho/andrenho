#include "frmitens.h"

FrmItens::FrmItens() : Form()
{
	this->id = ItensFrm;
}

bool FrmItens::event(UInt16 controlID, eventsEnum evt)
{
	if(evt == ctlSelectEvent)
		switch(controlID)
		{
		}
	return false;
}

void FrmItens::loadData()
{
}
