#include "terminal.h"

#include <stdlib.h>
#include "SDL.h"

#include "ui/resource.h"
#include "ui/ui.h"
#include "util/log.h"
#include "util/numbers.h"

#define PARTIAL_H 200
#define STEPS 20


static void terminal_draw_buffer(Terminal* term, int x, int y);


Terminal* terminal_init(struct UI* ui)
{
	// initialize terminal struct
	Terminal* term = malloc(sizeof(Terminal));
	term->ui = ui;
	term->term_sf = res("terminal");
	term->state = CLOSED;
	term->y = term->ui->screen->h;
	term->last_scr = NULL;

	return term;
}


void terminal_free(Terminal* term)
{
	if(term->last_scr)
		SDL_FreeSurface(term->last_scr);
	free(term);
}


void terminal_draw(Terminal* term)
{
	if(term->state == CLOSED)
		return;

	SDL_Rect r = { 
		(term->ui->screen->w / 2) - (term->term_sf->w / 2),
		term->y
	};
	SDL_BlitSurface(term->term_sf, NULL, term->ui->screen, &r);
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

	if(state != CLOSED)
	{
		SDL_Surface* screen2 = SDL_CreateRGBSurface(SDL_SWSURFACE,
				term->ui->screen->w, term->ui->screen->h, 32,
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
		if(term->last_scr)
			SDL_FreeSurface(term->last_scr);
		term->last_scr = SDL_DisplayFormat(screen2);
		SDL_FreeSurface(screen2);
		SDL_BlitSurface(term->ui->screen, NULL, term->last_scr, NULL);
	}

	SDL_Rect r = { 
		(term->ui->screen->w / 2) - (term->term_sf->w / 2),
		term->y,
		term->term_sf->w,
		term->term_sf->h,
	};
	int tst = sgn(goal_y - term->y);
	while(sgn(goal_y - term->y) == tst)
	{
		r.y = term->y;

		// draw screen
		SDL_Rect r2 = { 
			r.x, r.y-STEPS, 
			term->term_sf->w,
			term->term_sf->h + (2*STEPS) 
		};
		SDL_BlitSurface(term->last_scr, &r2, term->ui->screen, &r2);

		// draw terminal
		Uint32 t = SDL_GetTicks() + 1000/60;
		SDL_BlitSurface(term->term_sf, NULL, term->ui->screen, &r);
		SDL_UpdateRect(term->ui->screen, r.x, r.y-STEPS, 
			r.w, 
			imin(r.h + (2*STEPS), term->ui->screen->h - (r.y-STEPS)));
		while(t > SDL_GetTicks())
			SDL_Delay(1);
		term->y += STEPS * sgn(goal_y - term->y);
	}

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


/* 
 * STATIC 
 */


static void terminal_draw_buffer(Terminal* term, int x, int y)
{
}
