#ifndef FRMCIDADES_H
#define FRMCIDADES_H

#include "frmmodal.h"

class FrmCidades : public FrmModal
{
public:
	FrmCidades();
	bool event(UInt16 controlID, eventsEnum evt);
	void loadData();
};

#endif
