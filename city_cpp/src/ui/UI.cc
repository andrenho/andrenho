#include "ui/UI.h"

#include "ui/Util.h"

UI::UI(City* city)
  : city(city)
{
  // initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    error("Could not intiialize SDL: %s.\n", SDL_GetError());

  // initialize video
  if(!(Screen = SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE)))
    error("Could not set video mode: %s.\n", SDL_GetError());
}
