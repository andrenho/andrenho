#ifndef FRMENVIO_H
#define FRMENVIOL_H

#include "pform.h"
#include "segment.h"

#define N_FORM_ENVIO 6

class FrmEnvio : public Form
{
public:
	FrmEnvio() GERAL;
	void gravarPreferencias() GERAL;
	void carregarPreferencias() GERAL;
	bool event(UInt16 controlID, EventType* e) GERAL;
};

#endif

