#ifndef UI_H
#define UI_H

#include "city/City.h"
#include <SDL.h>

class UI
{
public:
    UI(City* city);

    virtual void Draw();
    virtual void Input();
    virtual void Wait();

    virtual inline bool Active() { return m_active; }


protected:
    virtual void InitializeColors();
    virtual void DrawGround();
    virtual void DrawBuildings();

    
private:
    static const int FRAME_TICKS = (1.0f / 60.0f * 1000);
    static const int BLOCK_SIZE = 32;

    City*        city;
    SDL_Surface* m_scr;
    bool         m_active;
    Uint32       m_ticks;
};

#endif
