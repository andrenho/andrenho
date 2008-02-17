#include "itens.h"

FrmItens::FrmItens()
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
