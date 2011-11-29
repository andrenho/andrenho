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
    SDL_Color* color;
    int x, y;
    int w;
    int fontSize;
    int backgroundColor;
    int foregroundColor;
    SDL_Surface *destiny;

    Pen(SDL_Color* color) : color(color) { }
    void Init(SDL_Surface *destiny, int backgroundColor, int foregroundColor);
    void Write(string text);

  private:
    map<int, TTF_Font*> fonts;
    set<int> loadedSizes;
};

#endif
