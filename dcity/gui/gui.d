module gui.gui;

import std.stdio;
import std.string;
import derelict.sdl.sdl;
import derelict.sdl.ttf;
import derelict.util.compat;

import city.city;

class GUI
{
    const uint fps = 30;
    const uint tileSize = 20;
    const short debug_w = 150;

    private
    {
        bool running = true;
        City city;
        uint black, white;
        uint w, h;
        uint debug_y;

        SDL_Surface* screen;
        TTF_Font* font;
    }

    this(City city)
    {
        this.city = city;

        // load libraries
        try
        {
            DerelictSDL.load();
            DerelictSDLttf.load();
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
        this.w = w;
        this.h = h;

        // initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
            throw new Exception("Could not initialize SDL.");
        else debug
            writefln("SDL initialized.");

        // initialize SDL_ttf
        if(TTF_Init() < 0)
            throw new Exception("Could not initialize SDL_ttf.");
        else debug
            writefln("SDL_ttf initialized.");

        // load font
        if((font = TTF_OpenFont("./atari.ttf", 8)) is null)
            throw new Exception("Could not load font.");
        else debug
            writefln("Font loaded.");

        // create window
        if((screen = SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE)) == null)
            throw new Exception("Failed to set video mode: " ~ toDString(SDL_GetError()));
        else debug
            writefln("Window created.");

        // setup colors
        white = SDL_MapRGB(screen.format, 255, 255, 255);
        black = SDL_MapRGB(screen.format, 0, 0, 0);

        // clear window
        SDL_FillRect(screen, null, white);
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
        SDL_Rect r = { cast(ushort)(w-debug_w), 0, 1, cast(ushort)h };
        SDL_FillRect(screen, &r, black);

        if(t !is null)
        {
            debug_y = 12;
            print(format("%d x %d", t.x, t.y));
        }
    }


    private void updateScreen()
    {
        SDL_FillRect(screen, null, white);
        updateMouseOver();
        SDL_Flip(screen);
    }


    private void print(string s)
    {
        SDL_Color bl = { 0, 0, 0 };
        SDL_Color wh = { 255, 255, 255 };
        SDL_Rect r = { cast(ushort)(w-debug_w+12), cast(ushort)debug_y, 0, 0 };
        SDL_Surface* surface = TTF_RenderUTF8_Solid(font, toStringz(s), bl);
        SDL_BlitSurface(surface, null, screen, &r);
        debug_y += TTF_FontLineSkip(font);
    }
}
