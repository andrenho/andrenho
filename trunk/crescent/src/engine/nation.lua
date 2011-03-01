Nation = {}

-- New nation
function Nation:new(name)
   self.__index = self
   o = setmetatable({}, self)
	o.name = name
	o.gold = 0
   return o
end

