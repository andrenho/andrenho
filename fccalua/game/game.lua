require 'nation'
require 'static'

Game = {}

function Game:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Game:initialize()
   assert(self.map_w and self.map_h and self.year and self.options, 
         "Initialization parameters missing.")
   self.map = {}
   self.nations = {}
   self.current = nil
   for x=1,self.map_w do
      self.map[x] = {}
      for y=1,self.map_h do
         self.map[x][y] = {
            terrain = plains,
            special = false,
            forest = false,
            road = false,
            plow = false,
            dirty = true,
         }
      end
   end
   self:draw_map()
end


function Game:draw_map()
   -- TODO
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


function Game:cost_to_enter(x,y)
   return 1
end


function Game:add_nation(name)
   local n = Nation:new { name=name, game=self }
   n:initialize()
   self.current = self.current or n
   table.insert(self.nations, n)
   return n
end


function Game:next_player()
   local k = table.find_key(self.nations, self.current)
   local nk = next(self.nations, k)
   if nk then
      self.current = self.nations[nk]
   else
      self.year = self.year + 1
      self.current = self.nations[1]
   end
   assert(self.current)
   self.current:init_turn()
end
