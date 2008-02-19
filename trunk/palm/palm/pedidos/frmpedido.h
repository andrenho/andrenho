#ifndef FRMPEDIDO_H
#define FRMPEDIDO_H

#include "pform.h"

#define N_FORM_PEDIDO 1

class FrmPedido : public Form
{
public:
	FrmPedido();
	~FrmPedido();
	bool event(UInt16 controlID, EventType* e);
	void carregarPreferencias();
	void gravarPreferencias();

	int nPedidoAtual;
	Char* cliente;
protected:
	void doAfterDrawing();
private:
	Char** cidades;
	int* codCidades;
	int nCidades;
	int cidadeSelecionada;
	void salvarDados();
};

#endif
