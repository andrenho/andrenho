module gui.button;

import derelict.sdl.sdl;
import derelict.sdl.ttf;

import std.xml, std.string, std.stdio;

import gui.defaultgui;


class Buttons
{
	private const int separatorLength;

	private Button[] buttons;
	SDL_Surface* sf, optionMenu;
	int optionMenuX;
	int w, h;

	void opOpAssign(string s)(Button b) if (s == "~")
	{
		buttons ~= b;
		w += b.sf.w;
		if(b.sf.h > h)
			h = b.sf.h;
	}

	void addSeparator()
	{
		buttons ~= null;
		w += separatorLength;
	}

	void initialize()
	{
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
        uint magenta = SDL_MapRGB(sf.format, 255, 0, 255);
        SDL_FillRect(sf, null, magenta);
        SDL_SetColorKey(sf, SDL_SRCCOLORKEY, magenta);
        drawButtons();
	}


    void click(short x, short y)
	{
        foreach(Button b; buttons)
            if(b.x <= x && (b.x + b.sf.w) > x)
            {
                unclickAll();
                b.setState(Button.State.PRESSED);
                drawButtons();
				optionMenuX = b.x;
                return;
            }
	}


    void unclickAll()
    {
        foreach(Button b; buttons)
			b.setState(Button.State.RELEASED);
		drawButtons();
		optionMenuX = -1;
    }


    void drawOptions(SDL_Surface* screen, short x)
    {
        Button set;
        foreach(Button b; buttons)
            if(b.state == Button.State.PRESSED)
                set = b;
        if(!set)
            return;

        foreach(Option o; set.options)
        {
            SDL_Rect r = { cast(short)(x + set.x), cast(short)set.sf.h };
            SDL_BlitSurface(o.sf, null, screen, &r);
        }
    }


    private
    {
        void drawButtons()
        {
		    int x = 0;
		    foreach(Button b; buttons)
		    {
			    SDL_Rect r = { cast(short) x, 0 };
			    SDL_BlitSurface(b.sf, null, sf, &r);
			    b.x = x;
			    x += w;
		    }
        }
    }
}



class Button
{
	enum State { PRESSED, RELEASED };

	private static SDL_Surface*[string] images;
	private static SDL_Surface* imagePressed, imageMiddle, imageUnpressed;
	public uint x;

	static void loadImages(SDL_Surface*[string] images)
	{
		this.images = images;
		imagePressed = images["buttonpressed"];
		imageMiddle = images["buttonmiddle"];
		imageUnpressed = images["buttonunpressed"];
	}


	SDL_Surface* sf, image;
	private State state;
	Option[] options;

	this(Element e, DefaultGUI gui)
	{
		// load XML
		assert(e.tag.name == "button");
        image = gui.loadImage(e.tag.attr["image"]);
		foreach(Element eb; e.elements)
			options ~= new Option(eb, gui);

		// create button surface
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, imageUnpressed.w, imageUnpressed.h, 32, 0, 0, 0, 0);
        uint magenta = SDL_MapRGB(sf.format, 255, 0, 255);
        SDL_FillRect(sf, null, magenta);
        SDL_SetColorKey(sf, SDL_SRCCOLORKEY, magenta);

		setState(State.RELEASED);
	}


	void setState(Button.State state)
	{
		SDL_Rect r = { cast(short)(sf.w/2 - image.w/2 - 1), cast(short)(sf.h/2 - image.h/2) };
		final switch(state)
		{
			case State.PRESSED:
				SDL_BlitSurface(imagePressed, null, sf, null);
				SDL_BlitSurface(image, null, sf, &r);
				break;
			case State.RELEASED:
                r.x++;
				SDL_BlitSurface(imageUnpressed, null, sf, null);
				SDL_BlitSurface(image, null, sf, &r);
				break;
		}
	}
}


class Option
{
	const uint w = 300;
	const uint yellow = 0xffffa0; // light yellow
    const SDL_Color black = { 0, 0, 0 };

	SDL_Surface* sf;
	string title, description;

	this(Element e, DefaultGUI gui)
	{
		assert(e.tag.name == "option");
		foreach(Element et; e.elements)
		{
			switch(et.tag.name)
			{
				case "title":
					title = et.text();
					version(Windows)
						title = title.replace("$OS", "Windows");
					version(linux)
						title = title.replace("$OS", "Linux");
					else
						title = title.replace("$OS", "System");
					break;
				case "description":
					description = et.text();
					break;
				default:
					throw new Exception(format("Invalid element <%s> in XML.", et.tag.name));
			}
		}

		SDL_Surface *icon = gui.loadImage(e.tag.attr["image"]);
		assert(icon.w == 32 && icon.h == 32, "Icon image must be 32x32");
		createImage(icon, gui);
	}

	void createImage(SDL_Surface* icon, DefaultGUI gui)
	{
		string[] text = description.wrap(80).split("\n");
		uint h = 100 + (text.length * TTF_FontLineSkip(gui.monoSmall));
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
		SDL_FillRect(sf, null, yellow);
		SDL_Rect r1 = { 20, 20 };
        SDL_BlitSurface(icon, null, sf, &r1);

        SDL_Surface* txt = TTF_RenderText_Solid(gui.titleFont, title.toStringz(), black);
        SDL_Rect r2 = { 65, 12 };
        SDL_BlitSurface(txt, null, sf, &r2);
        SDL_FreeSurface(txt);

        short y = 24;
        foreach(string t; text)
        {
            txt = TTF_RenderText_Solid(gui.monoSmall, t.toStringz(), black);
            r2.y = y;
            SDL_BlitSurface(txt, null, sf, &r2);
            SDL_FreeSurface(txt);
            y += TTF_FontLineSkip(gui.monoSmall);
        }
	}
}
