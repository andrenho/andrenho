#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H

#include <string>

class Logger {
public:
	void Debug(std::string s, ...);
};

extern Logger logger;

#endif
