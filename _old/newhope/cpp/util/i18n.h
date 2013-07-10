#ifndef I18N_H
#define I18N_H

#ifdef I18N
#  include <libintl.h>
#  define _(STRING) gettext(STRING)
#else
#  define _(STRING) STRING
#endif

void i18n_init();

#endif
