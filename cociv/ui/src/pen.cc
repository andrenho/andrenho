#include "pen.h"

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

  // write text
  SDL_Surface* s = TTF_RenderUTF8_Shaded(fonts[fontSize], text.c_str(), 
      color[foregroundColor], color[backgroundColor]);
  SDL_Rect r = { x, y, 0, 0 };
  SDL_BlitSurface(s, NULL, destiny, &r);
  x += s->w;
  SDL_FreeSurface(s);
}
