#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "game.h"
#include "ui.h"

class Environment 
{
  public:
    virtual void Redraw() = 0;
    virtual Environment* Input() = 0;
  protected:
    Game *game;
    UI *ui;
    Environment(Game *game, UI *ui) : game(game), ui(ui) { }
};

#endif
