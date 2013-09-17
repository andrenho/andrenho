#include "display.h"

#include <assert.h>

#include "SDL2/SDL_image.h"

Display* display_init()
{
	Display* d = malloc(sizeof(Display));

	// initialize
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

	// create window
	d->win = SDL_CreateWindow("Hippo 1", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 450, 331, 0);
	d->ren = SDL_CreateRenderer(d->win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(d->ren);

	// load background
	SDL_Surface* sf = IMG_Load("display.jpg");
	d->display = SDL_CreateTextureFromSurface(d->ren, sf);
	SDL_FreeSurface(sf);

	// load pixel surface
	sf = IMG_Load("px.png");
	d->px = SDL_CreateTextureFromSurface(d->ren, sf);
	SDL_FreeSurface(sf);
	sf = IMG_Load("shadow.png");
	d->shadow = SDL_CreateTextureFromSurface(d->ren, sf);
	SDL_FreeSurface(sf);

	// load charmap
	sf = IMG_Load("chars.png");
	for(int x=0; x<64; x++) {
		for(int y=0; y<96; y++) {
			d->charmap[x+(y*64)] = !((char*)sf->pixels)[x+(y*64)];
		}
	}
	SDL_FreeSurface(sf);

	d->active = true;
	d->cur_x = d->cur_y;

	return d;
}


void display_check_events(Display* d)
{
	SDL_Event e;
	// check events
	while(SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT) {
			d->active = false;
		}
	}
}


void display_draw_char(Display* d, char c, int x, int y)
{
	assert(x >= 0 && x < 21 && y >= 0 && y < 8);
	for(int px=0; px<4; px++) {
		for(int py=0; py<6; py++) {
			d->data[(x*4+px)+((y*6+py)*84)] = d->charmap[((c%16)*4+px) + ((c/16)*6+py)*64];
		}
	}
}


void display_update(Display* d)
{
	// draw display
	SDL_RenderClear(d->ren);
	SDL_RenderCopy(d->ren, d->display, NULL, &(SDL_Rect) { 0, 0, 450, 331 });

	// draw pixels
	for(int e=0; e<=1; e++) {
		for(int x=0; x<84; x++) {
			for(int y=0; y<48; y++) {
				if(d->data[(y*84)+x]) {
					if(e == 1) {
						SDL_RenderCopy(d->ren, d->px, NULL, 
						  &(SDL_Rect) { (x*4)+55, (y*5)+51, 3, 4 });
					} else {
						SDL_RenderCopy(d->ren, d->shadow, NULL, 
						  &(SDL_Rect) { (x*4)+56, (y*5)+53, 3, 4 });
					}
				}
			}
		}
	}

	// update screen
	SDL_RenderPresent(d->ren);
}


void display_send_command(Display* d, char* str)
{
	if(str[0] == 0) {
		return;
	}

	if(str[0] != 27) {
		display_draw_char(d, str[0], d->cur_x++, d->cur_y);
		if(d->cur_x > 20) {
			d->cur_x = 0;
			d->cur_y++;
		}
		if(d->cur_y > 7) {
			abort();
		}
	}
}
