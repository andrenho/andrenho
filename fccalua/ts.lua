require('alien')


local function load_sdl()
   SDL = alien.load('SDL.dll')

   SDL.SDL_Init:types('int', 'long')
   SDL_INIT_VIDEO = 0x00000020
   SDL.SDL_SetVideoMode:types('pointer', 'int', 'int', 'int', 'long')
   SDL.SDL_CreateRGBSurface:types('pointer', 'long', 'int', 'int', 'int', 'long', 'long', 'long', 'long')
end

local function get_color(r, g, b)
end


TS = {}

function TS.new(tile_w, tile_h)
   self = {}

   self.tile_w = tile_w
   self.tile_h = tile_h
   self.c = { {}, {}, {} }
   
   
   function self.init_video(w, h)
      SDL.SDL_Init(SDL_INIT_VIDEO)
      video = SDL.SDL_SetVideoMode(w * self.tile_w, h * self.tile_h, 0, 0)
      

      -- space
--      white = SDL.SDL_CreateRGBSurface(0, self.tile_w, self.tile_h, 32, 0, 0, 0, 0)

      self.load_char(1, ' ', white, 0, 0)
   end

   
   function self.load_char(level, char, image, x, y)
   end

   
   load_sdl()
   return self
end
