#include "ui/ui.h"

#include <syslog.h>

int main()
{
	openlog("newhope", LOG_CONS, LOG_USER);
	UI* ui = ui_init();


	ui_free(ui);
	closelog();
	return 0;
}
