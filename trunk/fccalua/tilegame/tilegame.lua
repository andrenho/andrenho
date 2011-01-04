require 'map'
require 'utils'
require 'luasdl'

TileGame = TileGameMap:new()


function TileGame:wait_event()
   e = SDL.WaitEvent()
   if e.type == SDL.MOUSEBUTTONDOWN or e.type == SDL.MOUSEBUTTONUP then
      e.tile_x = math.floor(e.x / self.tile_w + self.rx)
      e.tile_y = math.floor(e.y / self.tile_h + self.ry)
   end
   return e
end


function TileGame:move(tiles, x, y, mx, my)
   assert(math.abs(mx) <= 1 and math.abs(my) <= 1, 'mx/my must be between -1 and 1')

   -- redraw screen without the tiles
   table.sort(tiles, function(x,y) 
                        return x.level < y.level 
                     end)
   -- table.remove_values(self.map[x][y], tiles)
   self.map[5][5] = {}
   self:blit_map()
   self.scr:Flip()
   
   -- create surface from original
   local r = {
      x = (x - self.rx - 1) * self.tile_w,
      y = (y - self.ry - 1) * self.tile_h,
      w = self.tile_w * 3,
      h = self.tile_h * 3
   }

   local sf = SDL.CreateRGBSurface(SDL.SWSURFACE, r.w, r.h, self.scr.format.BitsPerPixel)
   self.scr:Blit(r, sf, nil)

   --print(r.x, r.y, r.w, r.h)
   --self.scr:FillRect(r, 0)

   -- make the move
   local max = math.max(self.tile_w, self.tile_h)
   for i=1,max do
      sf:Blit(nil, self.scr, r)
      for _,tile in ipairs(tiles) do
         self:blit(tile, x, y, self.rx, self.ry, i, i) -- TBD
         self.scr:UpdateRect(r)
         SDL.Delay(10)
      end
   end

   self.scr:Flip()

   sf:Free()
end
