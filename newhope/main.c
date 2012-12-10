#include "ui/ui.h"
#include "ui/event.h"
#include "util/log.h"

#include <stdio.h>

int main(int argc, char** argv)
{
	log_init(1);
	UI* ui = ui_init();
	if(!ui)
		return 1;

	while(ui->active)
	{
		ui_start_frame(ui);
		evt_process(ui, NULL);
		ui_end_frame(ui);
	}

	ui_free(ui);
	return 0;
}
