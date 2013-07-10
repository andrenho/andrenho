#include "pen.h"

#include <vector>
#include <string>

#include "util.h"

void 
Pen::Init(SDL_Surface *destiny, int backgroundColor, int foregroundColor)
{
  if(TTF_Init() == -1)
    throw new string(TTF_GetError());
  x = y = w = 0;
  fontSize = 20;
  fonts = map<int, TTF_Font*>();
  loadedSizes = set<int>();
  this->destiny = destiny;
  this->foregroundColor = foregroundColor;
  this->backgroundColor = backgroundColor;
}


unsigned int 
Pen::Height(string text)
{
  unsigned int h = 0;

  // parse text
  if(w > 0)
    text = wrap(text, w);
  vector<string>* v = split(text, '\n');

  // calculate height
  for(vector<string>::iterator it=v->begin(); it < v->end(); it++)
    h += TTF_FontLineSkip(fonts[fontSize]);

  return h;
}

 
void
Pen::Write(string text)
{
  // check if size was used, if not, load
  if(loadedSizes.find(fontSize) == loadedSizes.end())
  {
    fonts[fontSize] = TTF_OpenFont(DATA_DIR "/font.ttf", fontSize);
    if(!fonts[fontSize])
      throw new string("Could not load font.");
    loadedSizes.insert(fontSize);
  }

  // parse text
  if(w > 0)
    text = wrap(text, w);
  vector<string>* v = split(text, '\n');

  // write text
  int orig_x = x;
  for(vector<string>::iterator it=v->begin(); it < v->end(); it++)
  {
    SDL_Surface* s = TTF_RenderUTF8_Shaded(fonts[fontSize], (*it).c_str(), 
        color[foregroundColor], color[backgroundColor]);
    SDL_Rect r = { x, y, 0, 0 };
    SDL_BlitSurface(s, NULL, destiny, &r);
    x += s->w;
    if(it != v->end())
    {
      x = orig_x;
      y += TTF_FontLineSkip(fonts[fontSize]);
    }
    SDL_FreeSurface(s);
  }

  delete v;
}
