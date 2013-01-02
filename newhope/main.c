#include "ui/ui.h"
#include "ui/event.h"
#include "util/i18n.h"
#include "util/log.h"
#include "world/world.h"

#include <stdio.h>

int main(int argc, char** argv)
{
	// initialization
	log_init(1);
	i18n_init();
	World* world = world_init(5000, 5000);
	UI* ui = ui_init(world);
	if(!ui)
		return 1;

	// main loop
	while(ui->active)
	{
		ui_start_frame(ui);
		evt_process(ui, world);
		ui_draw(ui);
		ui_end_frame(ui);
	}

	// free everything
	ui_free(ui);
	world_free(world);

	return 0;
}
