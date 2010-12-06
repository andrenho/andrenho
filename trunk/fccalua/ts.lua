require('alien')


local function load_sdl()
   SDL = alien.load('SDL.dll')

   SDL.SDL_Init:types('int', 'long')
   SDL_INIT_VIDEO = 0x00000020
   SDL.SDL_SetVideoMode:types('pointer', 'int', 'int', 'int', 'long')
   SDL.SDL_CreateRGBSurface('long', 'int', 'int', 'int', 'long', 'long',
            'long', 'long')
end


TS = {}

function TS.new(tile_w, tile_h)
   self = {}

   self.tile_w = tile_w
   self.tile_h = tile_h
   self.c = { {}, {}, {} }
   
   
   function self.init_video(w, h)
      SDL.SDL_Init(SDL_INIT_VIDEO)
      SDL.SDL_SetVideoMode(w * self.tile_w, h * self.tile_h, 0, 0)

      -- space
      white = 
   end

   
   function self.load_char(char, image, x, y)
   end

   
   load_sdl()
   return self
end
