#include "terminal.h"

#include <stdarg.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_ttf.h"

#include "ui/resource.h"
#include "ui/ui.h"
#include "util/log.h"
#include "util/numbers.h"

#define PARTIAL_H 190
#define STEPS 20
#define TERMCOLOR ((SDL_Color) { 0, 255, 0 })
#define TEXT_X 130
#define TEXT_Y 128


static void terminal_draw_buffer(Terminal* term, int update);
static void terminal_mvaddch(Terminal* term, int ch, int col, int line);
static void terminal_advance_cursor(Terminal* term);
static void terminal_reset_fb(Terminal* term);


Terminal* terminal_init(struct UI* ui)
{
	// initialize structure
	Terminal* term = malloc(sizeof(Terminal));
	term->ui = ui;
	term->term_sf = res("terminal");
	term->state = CLOSED;
	term->y = term->ui->screen->h;
	term->last_scr = NULL;
	term->fb_sf = NULL;
	term->cur_x = term->cur_y = 0;

	// initialize framebuffer
	int tmp;
	TTF_GlyphMetrics((TTF_Font*)res("termfont_20"), 'a', &tmp, &tmp, &tmp, &tmp,
			&term->font_w);
	term->font_h = TTF_FontLineSkip((TTF_Font*)res("termfont_20"));
	terminal_reset_fb(term);

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
	terminal_draw_buffer(term, 0);
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
		term->y += STEPS * sgn(goal_y - term->y);
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
		r.x = (term->ui->screen->w / 2) - (term->term_sf->w / 2);
		SDL_BlitSurface(term->term_sf, NULL, term->ui->screen, &r);

		SDL_Rect upr = {
			r.x, r.y-STEPS,
			r.w, imin(r.h + (2*STEPS), term->ui->screen->h - (r.y-STEPS))
		};
		SDL_UpdateRect(term->ui->screen, upr.x, upr.y, upr.w, upr.h);
		while(t > SDL_GetTicks())
			SDL_Delay(1);
	}

	debug("Terminal state changed.");
	term->state = state;
}


void terminal_printf(Terminal* term, char* fmt, ...)
{
	char buf[1000];

	va_list ap;
	va_start(ap, fmt);
	int n = vsnprintf(buf, 999, fmt, ap);
	va_end(ap);

	int i;
	int cmd_mode = 0;
	for(i=0; i<n; i++)
	{
		if(!cmd_mode)
		{
			if(buf[i] == '{')
				cmd_mode = 1;
			else
			{
				terminal_mvaddch(term, buf[i], 
						term->cur_x, term->cur_y);
				terminal_advance_cursor(term);
				terminal_mvaddch(term, '_',
						term->cur_x, term->cur_y);
			}
		}
		else
		{
			if(buf[i] == 'C')
				terminal_reset_fb(term);
			else if(buf[i] == '}')
				cmd_mode = 0;
			else
				errx(1, "Invalid command %c.", buf[i]);
		}
	}
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


static void terminal_mvaddch(Terminal* term, int ch, int col, int line)
{
	// clear char
	SDL_Rect r = { (col * term->font_w), (line * term->font_h), 
		term->font_w, term->font_h };
	SDL_Rect r2 = { r.x + TEXT_X, r.y + TEXT_Y, term->font_w, term->font_h };
	SDL_BlitSurface(term->term_sf, &r2, term->fb_sf, &r);
	
	// draw char on surface
	SDL_Surface* sf = TTF_RenderUTF8_Blended(
			(TTF_Font*)res("termfont_20"), 
			(const char[]) { ch, '\0' }, TERMCOLOR);
	SDL_BlitSurface(sf, NULL, term->fb_sf, &r);
	
	// copy surface to scree
	terminal_draw_buffer(term, 1);
	
	// wait
	SDL_Delay(15);
}


static void terminal_draw_buffer(Terminal* term, int update)
{
	int x = (term->ui->screen->w / 2) - (term->term_sf->w / 2), 
	    y = term->y;
	SDL_Rect r = { x + TEXT_X, y + TEXT_Y, term->font_w, term->font_h };
	SDL_BlitSurface(term->fb_sf, NULL, term->ui->screen, &r);
	if(update)
		SDL_UpdateRect(term->ui->screen, r.x, r.y, r.w, r.h);
}


static void terminal_advance_cursor(Terminal* term)
{
	++term->cur_x;
	if(term->cur_x >= COLS)
	{
		term->cur_x = 0;
		++term->cur_y;
	}
	// TODO - overflow screen
}


static void terminal_reset_fb(Terminal* term) 
{
	term->cur_x = term->cur_y = 0;
	if(term->fb_sf)
		SDL_FreeSurface(term->fb_sf);
	SDL_Surface* sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 
			term->font_w*COLS, term->font_h*LINES, 32,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	term->fb_sf = SDL_DisplayFormat(sf);
	SDL_FreeSurface(sf);
	SDL_Rect r = { TEXT_X, TEXT_Y, term->fb_sf->w, term->fb_sf->h };
	SDL_BlitSurface(term->term_sf, &r, term->fb_sf, NULL);
}
