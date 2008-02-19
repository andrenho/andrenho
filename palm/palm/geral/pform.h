#ifndef FORM_H
#define FORM_H

#include "palmincludes.h"
#include "pedidos.h"

class Form
{
public:
	Form();
	virtual void open();
	void* getControl(UInt16 id);
	Char* getField(UInt16 field);
	int getFieldI(UInt16 field);
	double getFieldD(UInt16 field);
	void setField(UInt16 field, Char* s);
	UInt16 id;
	bool carregaPreferencias;

	virtual void carregarPreferencias() {}
	virtual void gravarPreferencias() {}
protected:
	void goToForm(Form* form);
	void displayAlert(UInt16 id);
	void mensagemErro(Char* message);
	bool perguntaSimNao(Char* mensagem);
	FormType* getFormType();

	bool leave_form;

	virtual void doAfterDrawing();
	virtual bool event(UInt16 controlID, EventType* e) =0;
private:
};

#endif
