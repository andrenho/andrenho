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

	void BeginFrame() { }
	void Process();
	void EndFrame() { }

	inline uint8_t T(int x, int y) const { return sf[y*w+x]; }
private:
	Options const& options;
	uint8_t* sf;
	const int w, h;
	Font font;
};

#endif
