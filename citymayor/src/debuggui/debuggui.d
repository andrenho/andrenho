module debuggui.debuggui;

import std.stdio;
import derelict.sdl.sdl;
import derelict.sdl.ttf;
import derelict.util.compat;

import gui.gui;
import city.city;
import city.structure;
import city.tile;
import city.road;

class DebugGUI : GUI
{
	private
	{
		const uint FPS = 60;
        SDL_Surface* scr;
        TTF_Font* font;
		uint white, grey;
		bool running = true;
		uint tileSize = 20;
    }


	this(City city, uint w, uint h)
	{
		super(city);

        DerelictSDL.load();
        DerelictSDLttf.load();

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
        if((font = TTF_OpenFont("./data/font/ProFontWindows.ttf", 12)) is null)
            throw new Exception("Could not load font.");
        else debug
            writefln("Font loaded.");

        // create window
        if((scr = SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE)) == null)
            throw new Exception("Failed to set video mode: " ~ toDString(SDL_GetError()));
        else debug
            writefln("Window created.");

        // setup colors
        white = SDL_MapRGB(scr.format, 255, 255, 255);
		grey = SDL_MapRGB(scr.format, 168, 168, 168);

        // clear window
        SDL_FillRect(scr, null, white);
        SDL_Flip(scr);
	}
	
	
	override void initialize() { }
	
	
	override void run()
	{
        while(running)
        {
            SDL_Event event;
            uint next = SDL_GetTicks() + (1000/FPS);

            //city.process();
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


	private
	{
		void updateScreen()
		{
			SDL_FillRect(scr, null, white);
			//drawGrid();
			drawStructures();
			SDL_Flip(scr);
		}
		
		
		void drawGrid()
		{
			for(uint x=0; x<city.w; x++)
				for(uint y=0; y<city.h; y++)
				{
					SDL_Rect r = { cast(short)(x*tileSize), cast(short)(y*tileSize), 1, 1 };
					SDL_FillRect(scr, &r, grey);
				}
		}
		
		
		void drawStructures()
		{
			foreach(Structure s; city.structures)
			{
				SDL_Rect r = {
					cast(short) (s.tile.x * tileSize + 1),
					cast(short) (s.tile.y * tileSize + 1),
					cast(short) (s.dt.w * tileSize - 1),
					cast(short) (s.dt.h * tileSize - 1)
				};
				SDL_FillRect(scr, &r, grey);
				r.x++; r.y++; r.w-=2; r.h-=2;
				SDL_FillRect(scr, &r, white);
			}
		}
	
	
		Tile mouseOverTile()
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			return city.tile[x / tileSize][y / tileSize];
		}
		
		
		void manageKeyboard(SDL_KeyboardEvent kb)
		{
			Tile t = mouseOverTile();
			
			switch(kb.keysym.sym)
			{
				// quit
				case SDLK_q:
					running = false;
					break;
	
				// save city
				case SDLK_s:
					if(kb.keysym.mod & KMOD_CTRL)
						saveCity("city.xml");
                    else
                        city.build(new Road(Road.data["street"]), t);
					break;
					
				// load city
				case SDLK_l:
					if(kb.keysym.mod | KMOD_CTRL)
						loadCity("city.xml");
					break;
		
				default:
					break;
			}
		}
	}
}
