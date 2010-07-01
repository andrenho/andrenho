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
import city.city;

class DefaultGUI : GUI
{
	this(City city)
	{
		Button.gui = this;
		
		initializeSDL(800, 600);
		super(city);
	}

	
	override void run()
	{
		loadConfig("etc/defaultgui.xml");
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
			SDL_SetColorKey(image, SDL_RLEACCEL, image.format.colorkey);
		}
		else
			throw new Exception(format("Error loading image %s.", file));
			
		return image;
	}

	private
	{
		SDL_Surface* screen;
		SDL_Surface*[string] images;
		TTF_Font* mono;
		const SDL_Color whiteColor = { 255, 255, 255 };
		uint white;
		Button[] buttons;
		
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
			if((screen = SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE|SDL_RESIZABLE)) == null)
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
		}


		void loadConfig(string file)
		{
			auto s = cast(string)std.file.read(file);
			check(s);
			auto xml = new Document(s);
			assert(xml.tag.name == "gui");
			foreach(Element e; xml.elements)
				switch(e.tag.name)
				{
					case "images":
						string[string] image_paths;
						foreach(Element ei; e.elements)
						{
							assert(ei.tag.name == "image");
							image_paths[ei.tag.attr["id"]] = ei.tag.attr["image"];
						}
						loadImages(image_paths);
						break;
					case "buttons":
						foreach(Element ei; e.elements)
						{
							if(ei.tag.name == "button")
								buttons ~= new Button(ei);
							else if(ei.tag.name == "separator")
								buttons ~= null;
							else
								assert(false);
						}
						break;
					default:
						assert(false);
				}
		}


		void loadImages(string[string] paths)
		{
			foreach(string key, string path; paths)
				images[key] = loadImage(path);
		}
	}
}