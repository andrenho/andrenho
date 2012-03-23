#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include "SDL.h"

#include "font.h"
#include "options.h"

typedef enum { NORMAL=0, NUM_ATTRS } CharAttr;

typedef struct {
	char ch;
	CharAttr attr;
} TerminalChar;

class Terminal
{
public:
	Terminal(Options const& options);
	~Terminal();

	bool Process();
	void SetChar(const char c, const int x, const int y);

	const int w, h;
	TerminalChar Ch(int x, int y) const { return ch[x][y]; }

private:
	Options const& options;
	TerminalChar** ch;
};

#endif
