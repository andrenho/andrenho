#include "worldenvironment.h"

void 
WorldEnvironment::Redraw()
{
  SDL_Flip(ui->getScreen());
}


Environment* 
WorldEnvironment::Input()
{
  SDL_Event e;
  while(SDL_WaitEvent(&e))
  {
    switch(e.type)
    {
      case SDL_QUIT:
        ui->Close();
        return 0x0;
    }
  }
  return 0x0;
}
