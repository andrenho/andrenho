#ifndef FRMPRINCIPAL_H
#define FRMPRINCIPAL_H

#include "pform.h"

class FrmPrincipal : public Form
{
public:
	FrmPrincipal();
	void gravarPreferencias();
	bool event(UInt16 controlID, EventType* e);
protected:
	void doAfterDrawing();
private:
	void alimentaLista();

	int itemNoTopo;
};

#endif
