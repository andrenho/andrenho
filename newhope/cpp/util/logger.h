#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H

#include <string>

class Logger {
public:
	Logger(bool show_debug, bool debug_frames)
		: show_debug(show_debug), debug_frames(debug_frames) { }
	void Debug(std::string const& s, ...);
	void DebugFrame(std::string const& s, ...);
	void Warning(std::string const& s, ...);
	void Error(int status, std::string const& s, ...);

private:
	const bool show_debug, debug_frames;
};

extern Logger logger;

#endif
