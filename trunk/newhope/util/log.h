#ifndef LOG_H
#define LOG_H

#if !__MINGW32__
#  include <err.h>
#endif

void log_init(int show_debug);
void debug(char* fmt, ...);
#if __MINGW32__
void warnx(char* fmt, ...);
void errx(int errcode, char* fmt, ...);
#endif

#endif
