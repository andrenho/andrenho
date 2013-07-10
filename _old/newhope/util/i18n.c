#include "i18n.h"

#include <locale.h>
#include <sys/stat.h>

#include "util/log.h"

void i18n_init()
{
#ifdef I18N
	char *locale = setlocale(LC_ALL, "");
	if(locale)
		debug("Locale set to %s.", locale);
	else
		debug("Could not set locale.");

	// if running from installation, get messages from LOCALEDIR, if not
	// from local directories
	char *dir;
	struct stat s;
	int st = stat(DATADIR "/grass.png", &s);
	if(st == 0)
		dir = bindtextdomain("newhope", LOCALEDIR);
	else
		dir = bindtextdomain("newhope", "./po");
	debug("Locale base directory is %s.", dir);

	char *domain = textdomain("newhope");
	debug("Domain set to %s.", domain);
#else
	debug("Not using localization.");
#endif
}
