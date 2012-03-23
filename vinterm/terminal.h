#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <set>
#include "SDL.h"
using namespace std;

#include "font.h"
#include "options.h"

typedef enum { NORMAL=0, NUM_ATTRS } CharAttr;

typedef struct TerminalChar {
	TerminalChar() : ch(' '), attr(NORMAL) { }
	char ch;
	CharAttr attr;
} TerminalChar;

class Terminal
{
public:
	Terminal(Options const& options);
	~Terminal();

	bool Process();
	void SetChar(const int x, const int y, char c, CharAttr attr);

	TerminalChar Ch(int x, int y) const { return ch[x][y]; }
	const int w, h;
	set<int> dirty;

private:
	Options const& options;
	TerminalChar** ch;
};

#endif
