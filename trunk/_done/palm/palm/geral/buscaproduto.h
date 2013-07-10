#ifndef BUSCAPRODUTO_H
#define BUSCAPRODUTO_H

#include "frmmodal.h"
#include "palmincludes.h"
#include "segment.h"
#include "lista.h"

class BuscaProduto : public FrmModal
{
public:
	BuscaProduto() GERAL;
	int busca(Form* caller, UInt16 referencia, UInt16 descricao, UInt16 unidMedida) GERAL;
protected:
	bool event(UInt16 controlID, EventType *e) GERAL;
	void doAfterDrawing();
private:
	void alimentaLista();

	int itemNoTopo;
	int produtoSelecionado;
	Lista* lista;

	Form* caller;
	UInt16 referencia; 
	UInt16 descricao;
	UInt16 unidMedida;
};

#endif
