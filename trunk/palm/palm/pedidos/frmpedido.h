#ifndef FRMPEDIDO_H
#define FRMPEDIDO_H

#include "pform.h"

class FrmPedido : public Form
{
public:
	FrmPedido();
	~FrmPedido();
	bool event(UInt16 controlID, EventType* e);
	void loadData();

	Char* cliente;
protected:
	void doAfterDrawing();
private:
	Char** cidades;
	int* codCidades;
	int nCidades;
	int cidadeSelecionada;
};

#endif
