--package.path = package.path .. ';./game/?.lua'

require 'nation'

Game = {}

function Game:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Game:initialize()
   assert(self.map_w and self.map_h, "Initialization parameters missing.")
   self.map = {}
   self.nations = {}
   for x=1,self.map_w do
      self.map[x] = {}
      for y=1,self.map_h do
         self.map[x][y] = {
            terrain = 'grassland',
            special = false,
            forest = false,
            road = false,
            plow = false
         }
      end
   end
   self:draw_map()
end


function Game:draw_map()
   for x=4,5 do
      for y=3,5 do
         self.map[x][y].terrain = 'ocean'
      end
   end
end


function Game:units(x,y)
   local t = {}
   for _,n in ipairs(self.nations) do
      for _,u in ipairs(n.units) do
         if u.x == x and u.y == y then
            table.insert(t, u)
         end
      end
   end
   return t
end


function Game:add_nation(name)
   local n = Nation:new { name=name }
   n:initialize()
   table.insert(self.nations, n)
end
