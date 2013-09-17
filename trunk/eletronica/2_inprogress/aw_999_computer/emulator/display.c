#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <stdbool.h>
#include <sys/shm.h>
#include <sys/stat.h>

static void update_display();


SDL_Window* win;
SDL_Renderer* ren;
SDL_Texture *display, *px, *shadow;
char* data;

int main() 
{
	// initialize
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

	// create window
	win = SDL_CreateWindow("Hippo 1", SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 450, 331, 0);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(ren);

	// load background
	SDL_Surface* sf = IMG_Load("display.jpg");
	display = SDL_CreateTextureFromSurface(ren, sf);
	SDL_FreeSurface(sf);

	// load pixel surface
	sf = IMG_Load("px.png");
	px = SDL_CreateTextureFromSurface(ren, sf);
	SDL_FreeSurface(sf);
	sf = IMG_Load("shadow.png");
	shadow = SDL_CreateTextureFromSurface(ren, sf);
	SDL_FreeSurface(sf);

	// create shared memory
	int sid = shmget(9666, 84*48, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	if(sid == -1) {
		fprintf(stderr, "It was not possible to reserve shared memory.\n");
		return -1;
	}
	data = (char*)shmat(sid, 0, 0);

	// main loop
	bool active = true;
	SDL_Event e;
	while(active) {

		// update display
		update_display();

		// check events
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) {
				active = false;
				shmdt(data);
				shmctl(sid, IPC_RMID, 0);
			}
		}
	}

	return 0;
}


static void update_display()
{
	// draw display
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, display, NULL, &(SDL_Rect) { 0, 0, 450, 331 });

	// draw pixels
	for(int d=0; d<=1; d++) {
		for(int x=0; x<84; x++) {
			for(int y=0; y<48; y++) {
				if(data[(y*84)+x]) {
					if(d == 1) {
						SDL_RenderCopy(ren, px, NULL, 
						  &(SDL_Rect) { (x*4)+55, (y*5)+51, 3, 4 });
					} else {
						SDL_RenderCopy(ren, shadow, NULL, 
						  &(SDL_Rect) { (x*4)+56, (y*5)+53, 3, 4 });
					}
				}
			}
		}
	}

	// update screen
	SDL_RenderPresent(ren);
}
