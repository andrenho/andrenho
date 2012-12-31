#include "terminal.h"

#include <stdlib.h>
#include "SDL.h"

#include "ui/resource.h"
#include "ui/ui.h"
#include "util/numbers.h"

#define PARTIAL_H 300
#define STEPS 15


Terminal* terminal_init(struct UI* ui)
{
	Terminal* term = malloc(sizeof(Terminal));
	term->ui = ui;
	term->term_sf = res("terminal");
	term->state = CLOSED;
	term->y = term->ui->screen->h;
	return term;
}


void terminal_free(Terminal* term)
{
	free(term);
}


void terminal_state(Terminal* term, enum TerminalState state)
{
	if(term->state == state)
		return;

	int goal_y = 0;
	switch(state)
	{
		case OPEN:
			goal_y = (term->ui->screen->h / 2) 
				- (term->term_sf->h / 2);
			break;
		case CLOSED:
			goal_y = (term->ui->screen->h);
			break;
		case PARTIAL:
			goal_y = term->ui->screen->h - PARTIAL_H;
			break;
		default:
			abort();
	}

	/*
	SDL_Surface* screen = SDL_CreateRGBSurfaceFrom(term->ui->screen->pixels,
			term->ui->screen->w, term->ui->screen->h, 32,
			term->ui->screen->pitch,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_Surface* screen = SDL_CreateRGBSurface(SDL_SWSURFACE,
			term->ui->screen->w, term->ui->screen->h, 32,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	*/

	SDL_Rect r = { 
		(term->ui->screen->w / 2) - (term->term_sf->w / 2),
		term->y,
//		term->term_sf->w,
//		term->term_sf->h,
	};
	int tst = sgn(goal_y - term->y);
	while(sgn(goal_y - term->y) == tst)
	{
		r.y = term->y;

		// draw screen
	//	SDL_Rect r2 = { r.x, r.y-STEPS, r.w, r.h+(2*STEPS) };
	//	debug("%d %d %d %d", r2.x, r2.y, r2.w, r2.h);
	//	SDL_BlitSurface(screen, &r2, term->ui->screen, &r2);

		// draw terminal
		Uint32 t = SDL_GetTicks() + 1000/60;
		SDL_BlitSurface(term->term_sf, NULL, term->ui->screen, &r);
		SDL_UpdateRect(term->ui->screen, r.x, r.y, r.w, r.h); // TODO
		while(t > SDL_GetTicks())
			SDL_Delay(1);
		term->y += STEPS * sgn(goal_y - term->y);
	}

	//SDL_FreeSurface(screen);

	debug("Terminal state changed.");
	term->state = state;
}


char terminal_getch(Terminal* term)
{
	SDL_Event e;
	char c = 0;
	
	while(c == 0)
	{
		SDL_WaitEvent(&e);
		switch(e.type)
		{
			case SDL_KEYDOWN:
				c = e.key.keysym.sym;
				break;
		}
	}

	return c;
}
