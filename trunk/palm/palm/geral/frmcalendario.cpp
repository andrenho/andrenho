#include "frmcalendario.h"

FrmCalendario::FrmCalendario()
{
	//this->id = CalendarioFrm;
}

void FrmCalendario::showDialog(void* d)
{
	displayAlert(ToBeDone);
}

bool FrmCalendario::event(UInt16 controlID, EventType* e)
{
	return false;
}
