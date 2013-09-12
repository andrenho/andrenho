#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "SDL.h"

#define W 1024
#define H 768

static SDL_Surface *scr, *icons;
struct {
	int us_pixel; 		// numer of microsseconds by pixel
	int trigger_active;
	double trigger;
} ctl = { 1, 0, 0.0 };
int last_x, last_y;
double last_v = 0;
double last_trigger = 0.0;
int triggered = 0;

enum Colors { BG=0, FG, LINE1, N_COLORS };

static int osc_y(double v)
{
	return H/2 - (v * ((H-100) / 12));
}


static void init_video()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	scr = SDL_SetVideoMode(W, H, 8, SDL_SWSURFACE);

	SDL_Color c[] = {
		{ 0x00, 0x00, 0x00 }, // background
		{ 0x00, 0xff, 0x00 }, // foreground (green)
		{ 0xff, 0x7f, 0x00 }, // line 1 (orange)
	};
	SDL_SetColors(scr, c, 0, N_COLORS);

	icons = SDL_LoadBMP("./icons.bmp");
	SDL_SetColorKey(icons, SDL_SRCCOLORKEY, 0);

	last_y = H/2;
}


static void draw_line(int x0, int y0, int x1, int y1, int c, int thickness)
{
	int sx = (x0<x1) ? 1 : -1, sy = (y0<y1) ? 1 : -1, 
	    dx = abs(x1-x0), dy = abs(y1-y0),
	    err = dx-dy;

	while(1)
	{
		int x, y;
		for(x=0; x<thickness; x++)
			for(y=0; y<thickness; y++)
				*((Uint8*)(scr->pixels + ((y0 + y) * scr->pitch) + x0 + x)) = c;
		if(x0 == x1 && y0 == y1)
			break;
		int e2 = err * 2;
		if(e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if(x0 == x1 && y0 == y1)
		{
			*((Uint8*)(scr->pixels + y0 * scr->pitch + x0)) = c;
			break;
		}
		if(e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}


static void draw_board()
{
	// clear screen
	SDL_FillRect(scr, NULL, BG);

	// window
	SDL_FillRect(scr, &((SDL_Rect){ 50, 50, H-100, H-100 }), FG);
	SDL_FillRect(scr, &((SDL_Rect){ 53, 53, H-106, H-106 }), BG);

	// horizontal lines
	for(int i=50, j=0; i<H-100; i += (H-150) / 11, j++)
	{
		if(j == 6)
			SDL_FillRect(scr, &((SDL_Rect){ 50, i, H-100, 2 }), FG);
		else
		{
			int x;
			for(x=50; x<H-50; x += 3)
				*((Uint8*)(scr->pixels + i * scr->pitch + x)) = FG;
		}
	}

	// vertical lines
	for(int x=50; x<H-100; x += ctl.us_pixel * 50)
	{
		int y;
		for(y=50; y<H-50; y += 3)
			*((Uint8*)(scr->pixels + y * scr->pitch + x)) = FG;
	}

	// trigger indicator
	if(ctl.trigger_active)
	{
		int y = osc_y(ctl.trigger);
		SDL_BlitSurface(icons, &((SDL_Rect){ 0, 0, 18, 7 }),
				scr,   &((SDL_Rect){ 30, y }));
	}

	// initialize trace
	last_x = 50;
	triggered = 0;
}


static double read_next_value()
{
	int v;
	scanf("%d", &v);
	double d = (double)v / 1024.0 * 5.0;
	if(d > 5.0)
		return 5.0;
	else if(d < -5.0)
		return -5.0;
	else
		return d;
}


static void set_trigger(int active, double v)
{
	if(active)
	{
		ctl.trigger = v;
		ctl.trigger_active = 1;
		triggered = 0;
	}
	else
		ctl.trigger_active = 0;
	draw_board();
	SDL_Flip(scr);
}


static void update_osc()
{
	// read data
	float v = read_next_value();

	// check trigger
	if(ctl.trigger_active && !triggered)
	{
		if(last_v < ctl.trigger && v >= ctl.trigger)
			triggered = 1;
		else
		{
			last_v = v;
			return;
		}
	}

	// calculate position
	int x = last_x + ctl.us_pixel;
	int y = osc_y(v);

	// draw
	if(x < H-50) // still inside scope
	{
		draw_line(last_x, last_y, x, y, LINE1, 3);
		SDL_UpdateRect(scr, last_x, 0, x-last_x, scr->h-1);
		last_x = x;
		last_y = y;
	}
	else // line outside scope
	{
		draw_board();
	}

	// store last voltage
	last_v = v;
}


static void check_events()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_t:
				if(!ctl.trigger_active)
					set_trigger(1, last_trigger);
				else
				{
					last_trigger = ctl.trigger;
					set_trigger(0, 0.0);
				}
				break;
			case SDLK_g:
				set_trigger(ctl.trigger_active, ctl.trigger+0.1);
				break;
			case SDLK_b:
				set_trigger(ctl.trigger_active, ctl.trigger-0.1);
				break;
			default:
				break;
			}
			break;
		}
	}
}


int main(int argc, char** argv)
{
	init_video();
	draw_board();
	SDL_Flip(scr);

	while(1)
	{
		check_events();
		update_osc();
	}
}
