#include "util/logger.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

void 
Logger::Debug(std::string const& s, ...)
{
	if(!show_debug)
		return;

	va_list ap;
	va_start(ap, s);
	printf("newhope: debug: ");
	vprintf(s.c_str(), ap);
	printf("\n");
	va_end(ap);
}


void 
Logger::DebugFrame(std::string const& s, ...)
{
	if(!show_debug || !debug_frames)
		return;

	va_list ap;
	va_start(ap, s);
	printf("newhope: debug: ");
	vprintf(s.c_str(), ap);
	printf("\n");
	va_end(ap);
}


void 
Logger::Warning(std::string const& s, ...)
{
	if(!show_debug)
		return;

	va_list ap;
	va_start(ap, s);
	printf("newhope: warning: ");
	vprintf(s.c_str(), ap);
	printf("\n");
	va_end(ap);
}


void 
Logger::Error(int status, std::string const& s, ...)
{
	if(!show_debug)
		return;

	va_list ap;
	va_start(ap, s);
	printf("newhope: error: ");
	vprintf(s.c_str(), ap);
	printf("\n");
	va_end(ap);
	abort();
}
