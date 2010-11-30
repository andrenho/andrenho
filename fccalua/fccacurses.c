#include <curses.h>

int running = 1;

void load_script()
{
}

void init_curses()
{
}

void draw_screen()
{
}

void event()
{
}

void close_curses()
{
}

void unload_lua()
{
}

int main()
{
	load_script();
	init_curses();

	while(running)
	{
		draw_screen();
		event();
	}

	close_curses();
	unload_lua();

	return 0;
}
