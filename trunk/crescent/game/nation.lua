Nation = {}

-- New nation
function Nation:new(name, o)
   self.__index = self
   o = setmetatable(o or {}, self)
	o.name = name
	o.gold = 0
   o.tax = 0
   o.units = {}
   return o
end


-- Create new unit
function Nation:create_unit(x, y, military)
   local u = Unit:new(x, y, military, self)
   table.insert(self.units, u)
   return u
end
