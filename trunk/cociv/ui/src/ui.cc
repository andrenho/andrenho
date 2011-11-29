#include "ui.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

void
UI::Init()
{
  running = true;

  // initialize SDL
  screen = initializeSDL();
  if(!screen)
    throw string(SDL_GetError());
  loadColors();

  // initialize fonts
  pen = new Pen(color);
  pen->Init(screen, colors["base3"], colors["base00"]);
  pen->fontSize = 24;
}

/////////////////////////////////////////////////////////////

char* 
UI::AskConnectAddress()
{
  SDL_FillRect(screen, NULL, colors["base3"]);
  pen->fontSize = 100;
  pen->Write("Cradle of\nCivilization");
  return 0x0;
}

/////////////////////////////////////////////////////////////

void 
UI::Message(char* m)
{
}

/////////////////////////////////////////////////////////////

SDL_Surface*
UI::initializeSDL()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    return 0x0;
  return SDL_SetVideoMode(800, 600, 8, SDL_SWSURFACE);
}

/////////////////////////////////////////////////////////////

void
UI::loadColors()
{
  colors = map<string, int>();

  ifstream file(DATA_DIR "/palette.gpl");
  if(file.is_open())
  {
    // ignore header
    char s[256];
    do
    {
      if(file.eof())
        throw new string("Invalid palette file.");
      file.getline(s, 255);
    } while(strcmp(s, "#"));

    // read data
    string line;
    int i = 0;
    while(getline(file, line))
    {
      int r, g, b;
      string s;
      stringstream str(line);
      
      str >> r >> g >> b >> s;
      
      color[i].r = r;
      color[i].g = g;
      color[i].b = b;
      colors[s] = i;

      i++;
    }
  }
  else
    throw new string("Unable to open palette file.");

  if(SDL_SetColors(screen, color, 0, 256) == 0)
    throw new string("Could not setup colors.");
}
