#include "display.h"

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

	d->active = true;

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
