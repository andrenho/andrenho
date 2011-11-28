#include <iostream>
#include <cstdlib>
#include "SDL.h"

#include "game.h"
#include "ui.h"
#include "worldenvironment.h"

int main(int argc, char *argv[])
{
  // initialize game
  Game *game = new Game();

  // initialize UI
  UI *ui = new UI();
  try
  {
    ui->Init();
  }
  catch(std::string s)
  {
    std::cerr << s << std::endl;
    return EXIT_FAILURE;
  }

  // connect to server
  while(ui->Running())
  {
    if(!game->Connect(ui->AskConnectAddress()))
      ui->Message("Could not connect to server.");
    else
      break;
  }

  // main loop
  Environment *e = new WorldEnvironment(game, ui);
  while(ui->Running())
  {
    e->Redraw();
    Environment *e2 = e->Input();
    if(e2)
      e = e2;
  }

  // finish
  game->Disconnect();
  ui->Close();
  return EXIT_SUCCESS;
}
