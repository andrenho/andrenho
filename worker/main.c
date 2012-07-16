#include <stdlib.h>

#include "level.h"
#ifdef SDL
#  include "sdl/ui.h"
#endif

int main(int argc, char** argv)
{
	(void) argv, (void) argc;

	UI* ui = ui_init();

	Level* level = level_load(0);
	ui_init_level(ui, level);

	while(ui->active)
	{
		ui_draw(ui);
		if(ui->state == EDIT)
			ui_edit(ui);
		else if(ui->state == RUN)
			ui_step(ui);
		else
			abort();
	}

	level_free(&level);
	ui_free(&ui);

	return 0;
}
