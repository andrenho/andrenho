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
	void setField(UInt16 field, Char* s);
	UInt16 id;
protected:
	void goToForm(Form* form);
	void displayAlert(UInt16 id);
	void mensagemErro(Char* message);
	bool perguntaSimNao(Char* mensagem);
	virtual void doAfterDrawing();
	virtual void gravarPreferencias() {}
	virtual void carregarPreferencias(void* info) {}
	virtual bool event(UInt16 controlID, EventType* e) =0;
	FormType* getFormType();

	bool leave_form;
private:
};

#endif
