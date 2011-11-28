#ifndef WORLDENVIRONMENT_H
#define WORLDENVIRONMENT_H

#include "environment.h"

class WorldEnvironment : public Environment
{
  public:
    WorldEnvironment(Game *game, UI *ui) : Environment(game, ui) { }
    virtual void Redraw();
    virtual Environment* Input();
};

#endif
