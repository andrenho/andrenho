#include "form.h"

extern Form* current;

void Form::open()
{
	FrmGotoForm(id);
	current = this;
}
