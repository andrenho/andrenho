require 'luasdl'

TileGameRaw = { levels = {} }

function TileGameRaw:new(o)
   assert(SDL.WasInit(), "SDL was not initialized.")
   self.__index = self
   return setmetatable(o or {}, self)
end


function TileGameRaw:tile(sf, x, y, level, off_x, off_y, w, h)
   assert(sf and x and y and level)
   return { 
      sf = sf, 
      x = x, 
      y = y, 
      level = level, 
      off_x = off_x or 0, 
      off_y = off_y or 0, 
      w = w or self.tile_w, 
      h = h or self.tile_h 
   }
end


function TileGameRaw:blit(tile, x, y, rx, ry, fine_x, fine_y)
   assert(tile and x and y)
   local rx = rx or 0
   local ry = ry or 0
   local fine_x = fine_x or 0
   local fine_y = fine_y or 0
   
   local r_src = {
      x = tile.x - tile.off_x,
      y = tile.y - tile.off_y,
      w = tile.w,
      h = tile.h
   }
   local r_dst = {
      x = ((x-rx) * self.tile_w) + fine_x,
      y = ((y-ry) * self.tile_h) + fine_y,
      w = r_src.w,
      h = r_src.h
   }

   if r_dst.x + r_dst.w >= 0 and r_dst.y + r_dst.h >= 0  and 
         r_dst.x < self.scr.w and r_dst.y < self.scr.h then
      tile.sf:Blit(r_src, self.scr, r_dst)
   end

   return r_dst
end
