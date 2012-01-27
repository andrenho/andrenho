#ifndef UI_H
#define UI_H

#include "city/City.h"
#include <SDL.h>

class UI
{
  public:
    UI(City* city);
    SDL_Surface* Screen;
    
  private:
    City* city;
};

#endif
