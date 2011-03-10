Unit = {}

-- New game
function Unit:new(x, y, military, nation, o)
   self.__index = self
   o = setmetatable(o or {}, self)
   o.x, o.y, o.military, o.nation = x, y, military, nation
   o.state = 'normal'
   return o
end

