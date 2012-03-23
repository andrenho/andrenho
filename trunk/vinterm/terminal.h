#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include "SDL.h"

#include "font.h"
#include "options.h"

class Terminal
{
public:
	Terminal(Options const& options);
	~Terminal();

	bool Process();
	void SetChar(const char c, const int x, const int y);

	const int w, h;

private:
	Options const& options;
};

#endif
