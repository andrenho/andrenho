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
import city.city;

class DefaultGUI : GUI
{
	const uint FPS = 60;
	SDL_Surface*[string] images;
	Buttons buttons;
	
	this(City city)
	{
		initializeSDL(400, 300);
		buttons = new Buttons();
		super(city);
	}
	
	
	override void initialize()
	{
		loadConfig("etc/defaultgui.xml");
	}

	
	override void run()
	{
        cityview = new CityView(city, images);

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
						screen = SDL_SetVideoMode(e.resize.w, e.resize.h, 32, screen.flags);
						updateScreen();
						break;
			    }
			
		//	while(SDL_GetTicks() < next)
        //        SDL_Delay(1);
        }
	}
	
	
	override void displayException(Exception e)
	{
		SDL_FillRect(screen, null, 0);
		SDL_Surface* s = TTF_RenderText_Solid(mono, e.msg.toStringz(), whiteColor);
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
		SDL_Surface* image = IMG_Load(toStringz("data/art/" ~ file));
		if(image !is null)
		{
			debug writefln("Loading image %s... ok!", file);
			//SDL_SetColorKey(image, SDL_RLEACCEL, image.format.colorkey);
		}
		else
			throw new Exception(format("Error loading image %s.", file));
			
		return image;
	}

	private
	{
		SDL_Surface* screen;
		TTF_Font* mono;
		const SDL_Color whiteColor = { 255, 255, 255 };
		uint white;
        bool running = true;
        CityView cityview;
		short rel_x = 0, rel_y = 0;
		int last_x, last_y;
		
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
			if((mono = TTF_OpenFont("./data/font/04B_03__.TTF", 16)) is null)
				throw new Exception("Could not load font FIPPS___.TTF.");
			else debug
				writefln("Font FIPPS___.TTF loaded.");

			// create window
			if((screen = SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE|SDL_RESIZABLE)) == null)
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

			Button.loadImages(images);

			foreach(Element e; xml.elements)
				switch(e.tag.name)
				{
					case "images":
						break;
					case "buttons":
						foreach(Element ei; e.elements)
						{
							if(ei.tag.name == "button")
								buttons ~= new Button(ei);
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
			
			SDL_Flip(screen);
        }
		
		
		bool quit()
		{
			return false;
		}
		
		
		void mouseButton(SDL_MouseButtonEvent e)
		{
			if(e.button == SDL_BUTTON_LEFT)
			{
				if(e.x >= cast(short)(screen.w/2 - buttons.sf.w/2)
				&& e.x <= cast(short)(screen.w/2 + buttons.sf.w/2)
				&& e.y <= cast(short)buttons.sf.h)
					buttons.click(cast(short)(e.x - (screen.w/2 - buttons.sf.w/2)), e.y);
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
                    cityview.displayGrid = !cityview.displayGrid;
                    cityview.redraw();
                    break;
            }
        }
	}
}
