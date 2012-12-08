#ifndef LOG_H
#define LOG_H

#include <err.h>

void log_init(int show_debug);
void debug(char* fmt, ...);

#endif
