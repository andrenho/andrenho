require 'military'
require 'unit'
require 'util'

Nation = {}

local initial_pos = { x=2, y=2 }


function Nation:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Nation:initialize()
   self.units = {}
   self.cities = {}
   for i=1,1 do
      local u = Unit:new {
         x = initial_pos.x,
         y = initial_pos.y,
         nation = self,
         military = warrior,
         nation = self,
         game = self.game,
      }
      table.insert(self.units, u)
   end
   self:init_turn()
end


function Nation:init_turn()
   for _,u in ipairs(self.units) do 
      u:init_turn() 
   end
   table.sort(self.units, function(i,j) 
                             return i:focus_order() < j:focus_order() 
                          end)
   self.focused = self.units[1]
end


function Nation:end_turn()
   self.game:next_player()
end


function Nation:next_unit()
   local us = table.select(self.units, function(u) return u:selectable() end)
   if #us == 0 then
      self.focused = nil
   else
      k = table.find_key(us, self.focused)
      if not k or not next(us, k) then
         self.focused = us[1]
      else
         self.focused = us[next(us, k)]
      end
   end
end
