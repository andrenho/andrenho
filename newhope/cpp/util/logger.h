#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H

#include <string>

class Logger {
public:
	Logger(bool show_debug)
		: show_debug(show_debug) { }
	void Debug(std::string const& s, ...);
	void Warning(std::string const& s, ...);
	void Error(int status, std::string const& s, ...);

private:
	const bool show_debug;
};

extern Logger logger;

#endif
