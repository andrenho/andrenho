import derelict.sdl.sdl;

void draws(float x, float y, float w, float h)
{
	SDL_Rect r = {
		cast(short)(x * 100 + 10),
		cast(short)(y * 100 + 10),
		1, 1 };
	SDL_FillRect(sf, &r, 0);
}


void drawi(float x, float y, float w, float h)
{
}

SDL_Surface *sf;

void main()
{
	DerelictSDL.load();
	SDL_Init(SDL_INIT_VIDEO);
	sf = SDL_SetVideoMode(400, 300, 32, SDL_SWSURFACE);
	SDL_FillRect(sf, null, 0xffffff);
	for(float x=0; x<1; x+=.1)
		for(float y=0; y<1; y+=.1)
		{
			draws(x, y, 1, 1);
			drawi(x, y, 1, 1);
		}
	SDL_Flip(sf);
	
	SDL_Event e;
	while(1)
	{
		SDL_WaitEvent(&e);
		if(e.type == SDL_QUIT)
			return;
	}
}