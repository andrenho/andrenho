#include "itens.h"

Itens::Itens()
{
	this->id = ItensFrm;
}

bool Itens::event(UInt16 controlID, eventsEnum evt)
{
	if(evt == ctlSelectEvent)
		switch(controlID)
		{
		}
	return false;
}

void Itens::loadData()
{
}
