#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"

#include <stdbool.h>

SDL_Surface* surface;

int main(int argc, char** argv)
{
	const SDL_VideoInfo *videoInfo;
	int flags;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Could not initialize video: %s\n",
				SDL_GetError());
		SDL_Quit();
	}

	videoInfo = SDL_GetVideoInfo();
	flags  = SDL_OPENGL;          // Enable OpenGL in SDL
	flags |= SDL_GL_DOUBLEBUFFER; // Enable double buffering
	flags |= SDL_HWPALETTE;       // Store the palette in hardware
	flags |= SDL_RESIZABLE;       // Enable window resizing
	if(videoInfo->hw_available)
		flags |= SDL_HWSURFACE;
	else
		flags |= SDL_SWSURFACE;
	if(videoInfo->blit_hw)
		flags |= SDL_HWACCEL;
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	surface = SDL_SetVideoMode(400, 300, 24, flags);
	
	if(!surface)
	{
		fprintf(stderr, "Video mode failed: %s\n",
				SDL_GetError());
		SDL_Quit();
	}

	SDL_Event e;
	_Bool done = false;
	while(!done)
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			default:
				break;
			}
		}

	return 0;
}
