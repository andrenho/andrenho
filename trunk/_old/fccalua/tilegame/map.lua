require 'raw'

TileGameMap = TileGameRaw:new()


function TileGameMap:initialize()
   self:clear_map()
   assert(self.tile_w and self.tile_h and self.map_w and self.map_h and
          self.scr and self.rx and self.ry,
          "Initialization parameters missing.")
end


function TileGameMap:clear_map()
   self.map = {}
   for x=1,self.map_w do
      self.map[x] = {}
      for y=1,self.map_h do
         self.map[x][y] = {}
      end
   end
end


function TileGameMap:blit_map(fine_x, fine_y)
   local fine_x = fine_x or 0
   local fine_y = fine_y or 0

   if not self.last_map then
      self.last_map = {}
      for x=1,self.map_w do
         self.last_map[x] = {}
         for y=1,self.map_h do
            self.last_map[x][y] = {}
         end
      end
   end

   for x=math.max(self.rx,1),self.map_w do
      for y=math.max(self.ry,1),self.map_h do
         if not table.shallow_compare(self.last_map[x][y], self.map[x][y]) then
            table.sort(self.map[x][y], function(x,y) 
                                          return x.level < y.level 
                                       end)
            if #self.map[x][y] == 0 then
               assert(self.blank)
               self:blit(self.blank, x, y, self.rx, self.ry, fine_x, fine_y)
            else 
               for _,tile in ipairs(self.map[x][y]) do
                  self:blit(tile, x, y, self.rx, self.ry, fine_x, fine_y)
               end
            end
            self.last_map[x][y] = clone(self.map[x][y])
         end
      end
   end
end
