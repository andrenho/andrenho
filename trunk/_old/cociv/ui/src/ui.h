#ifndef UI_H
#define UI_H

#include <map>
#include "SDL.h"

#include "pen.h"
#include "messages.h"

using namespace std;

class UI
{
  public:
    void Init();
    bool Running() { return running; }
    char* AskConnectAddress();
    void Message(char* m);
    SDL_Surface* getScreen() { return screen; }
    void Close() { running = false; }

  private:
    SDL_Surface* screen;
    SDL_Color color[256];
    bool running;
    map<string, int> colors;
    Pen *pen;
    Messages *messages;

    SDL_Surface* initializeSDL();
    void loadColors();
};

#endif
