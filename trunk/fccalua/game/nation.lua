Nation = {}


function Nation:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Nation:initialize()
   self.units = {}
   for i=1,2 do
      -- TODO
   end
end
