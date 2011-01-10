City = {}


function City:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function City:initialize()
   assert(self.name and self.x and self.y and self.nation and self.game,
      'One of the initialization parameters is missing.')
end


function City:auto_join_unit(unit)
   unit.city = self
end
