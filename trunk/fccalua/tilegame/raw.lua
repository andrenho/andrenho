require 'luasdl'

TileGameRaw = { max_level = 0 }
TileGameRaw.__index = TileGameRaw

function TileGameRaw:new(tile_w, tile_h)
   -- check SDL
   assert(SDL.WasInit(), "SDL was not initialized.")

   o = setmetatable({}, self)
   o.scr = assert(SDL.GetVideoSurface(), "SDL screen not initialized.")
   o.tile_w = tile_w
   o.tile_h = tile_h

   return o
end


function TileGameRaw:tile(sf, x, y, level, off_x, off_y, w, h)
   assert(sf and x and y and level)
   off_x = off_x or 0
   off_y = off_y or 0
   w = w or self.tile_w
   h = h or self.tile_h
   if level > TileGameRaw.max_level then
      TileGameRaw.max_level = level
   end
   return { sf=sf, x=x, y=y, level=level, off_x=off_x, off_y=off_y, w=w, h=h }
end


function TileGameRaw:blit(tile, x, y, rx, ry, fine_x, fine_y)
   assert(tile and x and y)
   rx = rx or 0
   ry = ry or 0
   fine_x = fine_x or 0
   fine_y = fine_y or 0
   
   r_src = {
      x = tile.x - tile.off_x,
      y = tile.y - tile.off_y,
      w = tile.w,
      h = tile.h
   }
   r_dst = {
      x = ((x-rx) * self.tile_w) + fine_x,
      y = ((y-ry) * self.tile_h) + fine_y,
      w = r_src.w,
      h = r_src.h
   }
   print(r_dst.x, r_dst.y, r_dst.w, r_dst.h)

   if r_dst.x + r_dst.w >= 0 and r_dst.y + r_dst.h >= 0  and 
         r_dst.x < self.scr.w and r_dst.y < self.scr.h then
      tile.sf:Blit(r_src, self.scr, r_dst)
   end

   return r_dst
end
