#include "form.h"

extern Form* current;

void Form::open()
{
	FrmGotoForm(id);
	current = this;
}

void Form::load()
{
	FrmGotoForm(id);
	loadData();
	current = this;
}
