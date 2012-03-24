#include "terminal.h"

#include "SDL.h"

Terminal::Terminal(Options const& options, Console& console)
	: w(80), h(25), options(options), console(console), 
	  ch(new TerminalChar*[w]), cursor_x(0), cursor_y(0)
{
	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, 
			SDL_DEFAULT_REPEAT_INTERVAL);
	for(int x=0; x<w; x++)
		ch[x] = new TerminalChar[h];
}


Terminal::~Terminal()
{
	for(int x=0; x<w; x++)
		delete[] ch[x];
	delete[] ch;
	dirty.clear();
}


bool
Terminal::Process()
{
	// read chars and send them to the console (TODO - move to screen?)
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_KEYDOWN:
			{
				uint16_t c = e.key.keysym.unicode;
				if(c != 0)
					KeyPress(c);
			}
			break;
		case SDL_QUIT:
			return false;
		}
	}

	// read console and draw on terminal
	string s;
	if(console.ReceiveString(s) == Console::READ_OK)
	{
		string::const_iterator it;
		for(it = s.begin(); it != s.end(); it++)
			PrintChar(*it);
	}

	return true;
}


void
Terminal::KeyPress(uint16_t key)
{
	printf("%d\n", key);
	console.SendChar((uint8_t)key);
}


void 
Terminal::PrintChar(const int c)
{
	switch(c)
	{
	case '\t': // tab
		AdvanceCursorX();
		while((cursor_x % 8) != 0)
			AdvanceCursorX();
		break;
	case '\n': // new line
		AdvanceCursorY();
		break;
	case '\r': // carriage return
		cursor_x = 0;
		break;
	case '\b':
		if(cursor_x > 0)
		{
			SetChar(cursor_x-1, cursor_y, ' ', NORMAL);
			--cursor_x;
		}
		break;
	default:
		SetChar(cursor_x, cursor_y, c, NORMAL);
		AdvanceCursorX();
	}
}


void 
Terminal::SetChar(const int x, const int y, int c, CharAttr attr)
{
	if(x < 0 || y < 0 || x >= w || y >= h)
		abort();
	ch[x][y].ch = c;
	ch[x][y].attr = attr;
	dirty.insert(y*w+x);
}


void 
Terminal::AdvanceCursorX()
{
	cursor_x++;
	if(cursor_x >= w)
	{
		AdvanceCursorY();
		cursor_x = 0;
	}
}


void 
Terminal::AdvanceCursorY()
{
	++cursor_y;

	// advance page
	if(cursor_y >= h)
	{
		for(int y=1; y<h; y++)
			for(int x=0; x<w; x++)
				SetChar(x, y-1, ch[x][y].ch, ch[x][y].attr);
		for(int x=0; x<w; x++)
			SetChar(x, h-1, ' ', NORMAL);
		--cursor_y;
	}

}
