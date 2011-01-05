require 'military'
require 'unit'

Nation = {}

local initial_pos = { x=2, y=2 }


function Nation:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Nation:initialize()
   self.units = {}
   for i=1,2 do
      local u = Unit:new {
         x = initial_pos.x,
         y = initial_pos.y,
         nation = self,
         military = SOLDIER,
      }
      table.insert(self.units, u)
   end
end
