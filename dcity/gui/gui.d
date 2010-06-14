module gui.gui;

import std.stdio;
import std.string;
import derelict.sdl.sdl;
import derelict.util.compat;

import city.city;

class GUI
{
    const uint fps = 30;
    const uint tileSize = 20;

    bool running = true;
    City city;
    SDL_Surface* screen;

    this(City city)
    {
        this.city = city;

        // load libraries
        try
        {
            DerelictSDL.load();
            debug
                writefln("DirectSDL loaded.");
        }
        catch(Exception e)
        {
            writefln("Error loading DerelictSDL.");
        }
    }


    void initialize(uint w, uint h)
    {
        // initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
            throw new Exception("Could not initialize SDL.");
        else debug
            writefln("SDL initialized.");

        // create window
        if((screen = SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE)) == null)
            throw new Exception("Failed to set video mode: " ~ toDString(SDL_GetError()));
        else debug
            writefln("Window created.");

        // clear window
        SDL_FillRect(screen, null, SDL_MapRGB(screen.format, 255, 255, 255));
        SDL_Flip(screen);
    }


    void main()
    {
        while(running)
        {
            SDL_Event event;
            uint next = SDL_GetTicks() + fps;

            city.process();
            updateScreen();
            updateMouseOver();

            while(SDL_PollEvent(&event))
                switch(event.type)
                {
                    case SDL_QUIT:
                        running = false;
                        break;
                    default:
                        break;
                }

            while(SDL_GetTicks() < next)
                SDL_Delay(1);
        }
    }


    private Tile mouseOverTile()
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return city.tile(x / tileSize, y / tileSize);
    }


    private void updateMouseOver()
    {
        Tile t = mouseOverTile();
    }

    private void updateScreen()
    {
    }
}
