#include <curses.h>
#include <stdlib.h>

static void init_ports()
{
	initscr();
	timeout(1);
	cbreak();
	noecho();
}


static void check_events()
{
	int ch = getch();
	switch(ch)
	{
		case 'q':
			endwin();
			exit(1);
	}
}


static void draw_leds()
{
	int x, y;
	for(y=0; y<16; y++)
		for(x=31; x >= 0; x--)
			if(leds[y] & (1 << x))
				mvaddch(y+3, x+3, 'X');
			else
				mvaddch(y+3, x+3, '.');
	refresh();
}
