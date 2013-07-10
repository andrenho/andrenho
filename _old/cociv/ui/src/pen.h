#ifndef PEN_H
#define PEN_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <set>
#include <map>

using namespace std;

class Pen
{
  public:
    unsigned int x, y;
    unsigned int w;
    unsigned int fontSize;
    unsigned int backgroundColor;
    unsigned int foregroundColor;
    SDL_Surface *destiny;

    Pen(SDL_Color* color) : color(color) { }
    void Init(SDL_Surface *destiny, int backgroundColor, int foregroundColor);
    void Write(string text);
    unsigned int Height(string text);

  private:
    SDL_Color* color;
    map<int, TTF_Font*> fonts;
    set<int> loadedSizes;
};

#endif
