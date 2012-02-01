#include "ui/UI.h"

#include "ui/Util.h"


UI::UI(City* city)
    : city(city), m_active(true), m_ticks(SDL_GetTicks())
{
    // initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        error("Could not intiialize SDL: %s.\n", SDL_GetError());

    // initialize video
    if(!(m_scr = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE)))
        error("Could not set video mode: %s.\n", SDL_GetError());

    InitializeColors();

    SDL_WM_SetCaption("city.cpp", "city.cpp");
}


void 
UI::Draw()
{
    DrawGround();
    DrawBuildings();
    SDL_Flip(m_scr);
}


void 
UI::Input()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                m_active = false;
                break;
        }
    }
}


void
UI::Wait()
{
    if(m_ticks + FRAME_TICKS < SDL_GetTicks())
        SDL_Delay(1);
    m_ticks = SDL_GetTicks();
}


void
UI::InitializeColors()
{
    SDL_Color colors[] = {
        {   0,   0,   0 },
        { 255, 255, 255 },
    };
    SDL_SetColors(m_scr, colors, 0, 255);
}


void 
UI::DrawGround()
{
    SDL_FillRect(m_scr, NULL, 1);
    int x = 0, y = 0;
    while(x < m_scr->w)
    {
        y = 0;
        while(y < m_scr->h)
        {
            int p = x + (y * m_scr->w);
            ((Uint8*)m_scr->pixels)[p] = 0;
            y += BLOCK_SIZE;
        }
        x += BLOCK_SIZE;
    }
}


void
UI::DrawBuildings()
{
}
