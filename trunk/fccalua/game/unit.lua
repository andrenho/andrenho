Unit = {}


function Unit:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Unit:focus_order()
   return 1
end


function Unit:move(fx, fy)
   self.x = self.x + fx
   self.y = self.y + fy
   return true
end


function Unit:selectable()
   return true
end
