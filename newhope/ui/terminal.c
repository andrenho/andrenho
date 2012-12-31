#include "terminal.h"

#include "ui/resource.h"
#include "ui/ui.h"

Terminal* terminal_init(struct UI* ui)
{
	Terminal* term = malloc(sizeof(Terminal));
	term->ui = ui;
	term->term_sf = res("terminal");
	return term;
}


void terminal_free(Terminal* term)
{
	free(term);
}
