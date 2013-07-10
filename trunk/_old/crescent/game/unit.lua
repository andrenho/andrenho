Unit = {}

-- New game
function Unit:new(x, y, military, nation, o)
   self.__index = self
   o = setmetatable(o or {}, self)
   o.x, o.y, o.military, o.nation = x, y, military, nation
   o.state = 'normal'
   return o
end



-- Move a unit by one
function Unit:move(rx, ry)
   assert(math.abs(rx) <= 1 and math.abs(ry) <= 1)
   local ok = true
   local fx, fy = (self.x + rx), (self.y + ry)

   -- test everything
   if fx < 1 or fy < 1 or fx > game.w or fy > game.h then
      ok = false
   end

   -- do the move
   if ok then
      self.x = fx
      self.y = fy
   end
   return ok
end
