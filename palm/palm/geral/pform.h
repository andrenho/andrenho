#ifndef FORM_H
#define FORM_H

#include "palmincludes.h"
#include "pedidos.h"
#include "segment.h"

typedef enum { INSERINDO, EDITANDO } TipoInsercao;

class Form
{
public:
	Form() GERAL;
	virtual void open() GERAL;
	ControlType* getControl(UInt16 id) GERAL;
	Char* getField(UInt16 field) GERAL;
	int getFieldI(UInt16 field) GERAL;
	double getFieldD(UInt16 field) GERAL;
	void setField(UInt16 field, Char* s) GERAL;
	UInt16 id;
	bool carregaPreferencias;

	virtual void carregarPreferencias() {}
	virtual void gravarPreferencias() {}
protected:
	void goToForm(Form* form) GERAL;
	void displayAlert(UInt16 id) GERAL;
	void mensagemErro(Char* message) GERAL;
	bool perguntaSimNao(Char* mensagem) GERAL;
	FormType* getFormType() GERAL;

	bool leave_form;

	virtual void doAfterDrawing() GERAL;
	virtual bool event(UInt16 controlID, EventType* e) =0;
private:
};

#endif
