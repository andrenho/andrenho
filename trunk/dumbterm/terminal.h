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

	void BeginFrame() { }
	void Process();
	void EndFrame() { }
	void SetChar(const char c, const int x, const int y);

	inline uint8_t T(const int x, const int y) const { return sf[y*w+x]; }

private:
	const Font* const font;
	Options const& options;
public:
	const int w, h;
private:
	uint8_t* sf;
};

#endif
