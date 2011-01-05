Unit = {}


function Unit:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end
