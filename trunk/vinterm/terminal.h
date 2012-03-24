#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <set>
#include "SDL.h"
using namespace std;

#include "font.h"
#include "options.h"
#include "console.h"

typedef enum { NORMAL=0, NUM_ATTRS } CharAttr;

typedef struct TerminalChar {
	TerminalChar() : ch(' '), attr(NORMAL) { }
	int ch;
	CharAttr attr;
} TerminalChar;

class Terminal
{
public:
	Terminal(Options const& options, Console& console);
	~Terminal();

	bool Process();

	TerminalChar Ch(int x, int y) const { return ch[x][y]; }
	const int w, h;
	set<int> dirty;

private:
	void KeyPress(uint16_t key);
	void PrintChar(const int c);
	void SetChar(const int x, const int y, int c, CharAttr attr);
	void AdvanceCursorX();
	void AdvanceCursorY();

	Options const& options;
	Console& console;
	TerminalChar** ch;
	int cursor_x, cursor_y;
};

#endif
