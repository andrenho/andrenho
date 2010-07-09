/* TODO:
 * 
 * - Interface
 * - Minimap / info window
 * - Fullscreen
 * - Configurable keys
 * - File packing
 * - About
 * - Window decorations
 * - I18N
 * - city earth
 * - save city on exit
 * - initial screen, region
 * - documentation
 */

module gui.defaultgui;

import  std.stdio,
        std.xml,
		std.string;

import derelict.sdl.sdl;
import derelict.sdl.ttf;
import derelict.sdl.image;
import derelict.util.compat;

import gui.gui;
import gui.button;
import gui.cityview;
import gui.dialog;
import util.sdl;
import city.city;

class DefaultGUI : GUI
{
	const uint FPS = 60;
	SDL_Surface*[string] images;
	SDL_Surface* screen;
	Buttons buttons;
	TTF_Font* monoBig, monoSmall, titleFont, titleSmall;
	
	this(City city)
	{
		version(test)
			initializeSDL(400, 300);
		else
			initializeSDL(800, 600);
		buttons = new Buttons();
		super(city);
	}
	
	
	override void initialize()
	{
		Button.initialize();
		loadConfig("etc/defaultgui.xml");
		dialog = new Dialog(this);
        cityview = new CityView(city, images);
	}

	
	override void run()
	{
        SDL_Event e;
        while(running)
        {
			uint next = SDL_GetTicks() + (1000/FPS);
			updateScreen();
			
            while(SDL_PollEvent(&e))
    			final switch(e.type)
	    		{
		    		case SDL_QUIT:
			    		running = quit();
				    	break;
    				case SDL_MOUSEBUTTONDOWN:
	    			case SDL_MOUSEBUTTONUP:
		        		mouseButton(e.button);
				    	break;
    				case SDL_MOUSEMOTION:
	    				mouseMotion(e.motion);
		    			break;
                    case SDL_KEYDOWN:
                        keyPress(e.key);
                        break;
					case SDL_VIDEORESIZE:
						if(!fullscreen)
						{
							screen = SDL_SetVideoMode(e.resize.w, e.resize.h, 32, screen.flags);
							windowW = e.resize.w;
							windowH = e.resize.h;
							updateScreen();
						}
						break;
			    }
			
		//	while(SDL_GetTicks() < next)
        //        SDL_Delay(1);
        }
	}
	
	
	override void displayException(Exception e)
	{
		SDL_FillRect(screen, null, 0);
		SDL_Surface* s = TTF_RenderText_Solid(monoBig, e.msg.toStringz(), whiteColor);
		SDL_Rect r = { cast(short)((screen.w/2) - (s.w/2)), 
		               cast(short)((screen.h/2) - (s.h/2)) };
		SDL_BlitSurface(s, null, screen, &r);
		SDL_Flip(screen);

		SDL_Event ev;
		bool done = false;
		while(!done)
		{
			SDL_WaitEvent(&ev);
			if(ev.type == SDL_KEYDOWN || ev.type == SDL_QUIT)
				done = true;
		}
		
		throw e;
	}
	
	
	SDL_Surface* loadImage(string file)
	{
		SDL_Surface* image2, image1 = IMG_Load(toStringz("data/art/" ~ file));
		if(image1 !is null)
		{
			debug writefln("Loading image %s... ok!", file);
			image2 = SDL_ConvertSurface(image1, screen.format, SDL_SWSURFACE);
			SDL_FreeSurface(image1);
			SDL_SetColorKey(image2, SDL_SRCCOLORKEY|SDL_RLEACCEL, image2.format.colorkey);
			return image2;
		}
		else
			throw new Exception(format("Error loading image %s.", file));
	}

	private
	{
		Dialog dialog;
		const SDL_Color whiteColor = { 255, 255, 255 };
		uint white;
        bool running = true;
        CityView cityview;
		short rel_x = 0, rel_y = 0;
		int last_x, last_y;
		uint screenFlags;
		uint desktopW, desktopH;
		uint windowW, windowH;
		bool fullscreen = false;
		
		void initializeSDL(uint w, uint h)
		{
			// initialize SDL
            DerelictSDL.load();
			if(SDL_Init(SDL_INIT_VIDEO))
				throw new Exception("Error initializing SDL.");
			else debug
				writefln("SDL initialized.");
	
			// initialize SDL_ttf
            DerelictSDLttf.load();
			if(TTF_Init() < 0)
				throw new Exception("Could not initialize SDL_ttf.");
			else debug
				writefln("SDL_ttf initialized.");
				
			// load font
			if((monoBig = TTF_OpenFont("./data/font/04B_03__.TTF", 16)) is null)
				throw new Exception("Could not load font 04B_03__.TTF.");
			else debug
				writefln("Font 04B_03__.TTF loaded.");
			if((monoSmall = TTF_OpenFont("./data/font/04B_03__.TTF", 8)) is null)
				throw new Exception("Could not load font 04B_03__.TTF.");
			else debug
				writefln("Font 04B_03__.TTF loaded.");
			if((titleFont = TTF_OpenFont("./data/font/Hardpixel.OTF", 20)) is null)
				throw new Exception("Could not load font Hardpixel.OTF.");
			else debug
				writefln("Font Hardpixel.OTF loaded.");
			if((titleSmall = TTF_OpenFont("./data/font/Hardpixel.OTF", 10)) is null)
				throw new Exception("Could not load font Hardpixel.OTF.");
			else debug
				writefln("Font Hardpixel.OTF loaded.");

			// get desktop size
			const SDL_VideoInfo* info = SDL_GetVideoInfo(); 
			desktopW = info.current_w; 
			desktopH = info.current_h; 
	
			// create window
			screenFlags = SDL_SWSURFACE|SDL_RESIZABLE;
			windowW = w;
			windowH = h;
			if((screen = SDL_SetVideoMode(w, h, 32, screenFlags)) == null)
				throw new Exception("Failed to set video mode: " ~ toDString(SDL_GetError()));
			else debug
				writefln("Window created.");
				
			// initialize SDL_image
            DerelictSDLImage.load();
			if(!IMG_Init(IMG_INIT_PNG))
				throw new Exception("Could not initialize SDL_image.");
			else debug
				writefln("SDL_image initialized.");
	
			// setup colors
			white = SDL_MapRGB(screen.format, 255, 255, 255);
			
			// get pointer position
			SDL_GetMouseState(&last_x, &last_y);
		}


		void loadConfig(string file)
		{
			auto s = cast(string)std.file.read(file);
			check(s);
			auto xml = new Document(s);
			assert(xml.tag.name == "gui");
			foreach(Element e; xml.elements)
				if(e.tag.name == "images")
				{
					string[string] image_paths;
					foreach(Element ei; e.elements)
					{
						assert(ei.tag.name == "image");
						image_paths[ei.tag.attr["id"]] = ei.tag.attr["image"];
					}
					loadImages(image_paths);
				}

			foreach(Element e; xml.elements)
				switch(e.tag.name)
				{
					case "images":
						break;
					case "buttons":
						foreach(Element ei; e.elements)
						{
							if(ei.tag.name == "button")
								buttons ~= new Button(ei, this);
							else if(ei.tag.name == "separator")
								buttons.addSeparator();
							else
								assert(false);
						}
						break;
					default:
						assert(false);
				}
				
			buttons.initialize();
		}


		void loadImages(string[string] paths)
		{
			foreach(string key, string path; paths)
				images[key] = loadImage(path);
		}
		
		
		void updateScreen()
		{
			// draw cityview
			SDL_Rect r = { rel_x, rel_y };
			SDL_BlitSurface(cityview, null, screen, &r);
			
			// draw buttons
			SDL_Rect r2 = { cast(short)(screen.w/2 - buttons.sf.w/2), 0 };
			SDL_BlitSurface(buttons.sf, null, screen, &r2);

            // draw options
            buttons.drawOptions(screen, r2.x);
			
			SDL_Flip(screen);
        }
		
		
		bool quit()
		{
			version(test)
				return 0;
			else 
			{			
				string os;
				version(Windows)
					os = "Windows";
				else version(linux)
					os = "Linux";
				else
					os = "the Operating System";
				return !dialog.yesNo("Are you sure you want to quit to " ~ os ~ "?", Dialog.Image.WARNING, true);
			}
		}
		
		
		void mouseButton(SDL_MouseButtonEvent e)
		{
			if(e.button == SDL_BUTTON_LEFT && e.state == SDL_PRESSED)
			{
				string command;
				
				if(e.x >= cast(short)(screen.w/2 - buttons.sf.w/2)
				&& e.x <= cast(short)(screen.w/2 + buttons.sf.w/2)
				&& e.y <= cast(short)buttons.sf.h)
					buttons.click(cast(short)(e.x - (screen.w/2 - buttons.sf.w/2)), e.y);
				else if((command = buttons.optionClicked(e.x, e.y)) !is null)
				{
					buttons.unclickAll();
					doCommand(command);
				}
				else
					buttons.unclickAll();
			}
		}
		
		
		void mouseMotion(SDL_MouseMotionEvent e)
		{
            int xrel = e.x - last_x;
			int yrel = e.y - last_y;
                
            last_x = e.x;
			last_y = e.y;
			
			// right button pressed
			if(e.state & SDL_BUTTON(3))
			{
                if(cityview.w < screen.w)
                    rel_x = 0;
                else if(rel_x + xrel > 0)
					rel_x = 0;
				else if(rel_x + xrel < (screen.w - cityview.w))
					rel_x = cast(short)(screen.w - cityview.w);
				else
					rel_x += xrel;
					
                if(cityview.h < screen.h)
                    rel_y = 0;
                else if(rel_y + yrel > 0)
					rel_y = 0;
				else if(rel_y + yrel < (screen.h - cityview.h))
					rel_y = cast(short)(screen.h - cityview.h);
				else
					rel_y += yrel;
			}
		}


        void keyPress(SDL_KeyboardEvent e)
        {
            final switch(e.keysym.sym)
            {
                case SDLK_g:
					doCommand("grid");
                    break;
            }
        }


		void doCommand(string command)
		{
			switch(command)
			{
				case "grid":
                    cityview.displayGrid = !cityview.displayGrid;
                    cityview.redraw();
					break;
					
                case "fullscreen":
					if(!fullscreen)
					{
						writefln("%d x %d", desktopW, desktopH);
						screen = SDL_SetVideoMode(desktopW, desktopH, 32, screenFlags ^ SDL_FULLSCREEN);
                        if(screen is null)
                            screen = SDL_SetVideoMode(windowW, windowH, 32, screenFlags);
						else
							fullscreen = true;
					}
					else
					{
						screen = SDL_SetVideoMode(windowW, windowH, 32, screenFlags);
						fullscreen = false;
					}
                    assert(screen);
                    updateScreen();
                    break;

				case "quit":
					running = quit();
					break;
					
				default:
					assert(false, format("Unknown command '%s'.", command));
			}
		}
	}
}
