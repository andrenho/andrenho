Nation = {}

-- New nation
function Nation:new(name, o)
   self.__index = self
   o = setmetatable(o or {}, self)
	o.name = name
	o.gold = 0
   return o
end

