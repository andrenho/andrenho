#include "i18n.h"

#include <locale.h>

void i18n_init()
{
#ifdef I18N
	setlocale(LC_ALL, "");
	bindtextdomain("newhope", "/usr/share/locale");
	textdomain("newhope");
#endif
}
