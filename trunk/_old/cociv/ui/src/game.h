#ifndef GAME_H
#define GAME_H

class Game
{
  public:
    Game();
    bool Connect(char* address);
    void Disconnect();
};

#endif
