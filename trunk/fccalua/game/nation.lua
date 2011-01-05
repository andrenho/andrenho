Nation = {}


function Nation:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Nation:initialize()

end
