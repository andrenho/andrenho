module gui.gui;

import std.stdio;
import std.string;
import derelict.sdl.sdl;
import derelict.sdl.ttf;
import derelict.util.compat;

import city.city;
import city.structures;
import city.moveable;
import city.person;
import city.residence;
import city.farm;
import city.work;

class GUI
{
    const uint FPS = 30;
    const uint tileSize = 20;
    const uint moveableSize = 1;
    const short debug_w = 200;

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
        if((font = TTF_OpenFont("./ProFontWindows.ttf", 12)) is null)
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
            uint next = SDL_GetTicks() + (1000/FPS);

            city.process();
            updateScreen();

            while(SDL_PollEvent(&event))
                switch(event.type)
                {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                        manageKeyboard(event.key);
                        break;
                    default:
                        break;
                }

            while(SDL_GetTicks() < next)
                SDL_Delay(1);
        }
    }


    private void manageKeyboard(SDL_KeyboardEvent kb)
    {
    	Tile t = mouseOverTile();

    	switch(kb.keysym.sym)
	    {
    		// quit
	    	case SDLK_q:
		    	running = false;
			    break;

    		// build low class housing
	    	case SDLK_l:
			    if(t !is null)
    				if(kb.keysym.mod & KMOD_SHIFT)
                        city.build(new Residence(t.x, t.y, false, Class.LOW, Density.HIGH));
			    	else
                        city.build(new Residence(t.x, t.y, false, Class.LOW, Density.LOW));
    			break;

            // street
            case SDLK_s:
                city.build(new Street(t.x, t.y));
                break;

            // vegetable farm
            case SDLK_v:
                city.build(new VegetableFarm(t.x, t.y));
                break;

	    	default:
		    	break;
	    }
    }


    private Tile mouseOverTile()
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return city.tile(x / tileSize, y / tileSize);
    }


    private void updateScreen()
    {
        SDL_FillRect(screen, null, white);
        updateMouseOver();
        foreach(Structure s; city.structures)
            drawStructure(s);
        foreach(Moveable m; city.moveables)
            drawMoveable(m);
        SDL_Flip(screen);
    }


    private void print(string s)
    {
        SDL_Color bl = { 0, 0, 0 };
        SDL_Rect r = { cast(ushort)(w-debug_w+12), cast(ushort)debug_y, 0, 0 };
        SDL_Surface* surface = TTF_RenderUTF8_Solid(font, toStringz(s), bl);
        SDL_BlitSurface(surface, null, screen, &r);
        debug_y += TTF_FontLineSkip(font);
    }


    private void drawStructure(Structure s)
    {
        SDL_Rect r = { cast(short)(s.x*tileSize+1), cast(short)(s.y*tileSize+1),
            cast(short)(s.w*tileSize-2), cast(short)(s.h*tileSize-2) };
        SDL_FillRect(screen, &r, black);
        r.x += 1;
        r.y += 1;
        r.w -= 2;
        r.h -= 2;
        SDL_FillRect(screen, &r, white);

        SDL_Color bl = { 0, 0, 0 };
        SDL_Surface* surface = TTF_RenderUTF8_Solid(font, toStringz(s.shortDescription()), bl);
        r.x += (r.w/2) - (surface.w/2);
        r.y += (r.h/2) - (surface.h/2);
        SDL_BlitSurface(surface, null, screen, &r);
    }


    private void drawMoveable(Moveable m)
    {
        uint x = cast(uint) (m.x / 100.0f * tileSize);
        uint y = cast(uint) (m.y / 100.0f * tileSize);
        SDL_Rect r = { cast(short)(x - moveableSize), cast(short)(y - moveableSize),
            cast(short)(moveableSize * 2), cast(short)(moveableSize * 2) };
        SDL_FillRect(screen, &r, black);
        r.x += 1;
        r.y += 1;
        if(r.w < 2 || r.h < 2)
            return;
        r.w -= 2;
        r.h -= 2;
        SDL_FillRect(screen, &r, SDL_MapRGB(screen.format, 128, 128, 255));
    }


    private void updateMouseOver()
    {
        Tile t = mouseOverTile();
        SDL_Rect r = { cast(ushort)(w-debug_w), 0, 1, cast(ushort)h };
        // SDL_FillRect(screen, &r, black);

        if(t !is null)
        {
            debug_y = 12;
            print(format("%d x %d", t.x, t.y));
			if(t.structure !is null)
			{
				print(t.structure.longDescription());
				if(cast(Residence) t.structure)
				{
					auto res = cast(Residence)t.structure;
					print(format("Level: %d", res.level));
					print(format("%d dwellers", res.dwellers));
				}
				else if(cast(Workplace) t.structure)
				{
					auto work = cast(Workplace) t.structure;
					print(format("%d workers", work.workers()));
				}
			} 
        }
    }
}
