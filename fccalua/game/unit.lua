Unit = {}


function Unit:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Unit:init_turn()
   self.moves = self.military.moves
end


function Unit:focus_order()
   return 1
end


function Unit:move(fx, fy)
   assert(math.abs(fx) <= 1 and math.abs(fy) <= 1)
   local ok = true
   local cost = self.game:cost_to_enter(self.x+fx, self.y+fy)

   if ok then
      self.x = self.x + fx
      self.y = self.y + fy
      self.moves = self.moves - cost
      if not (self.moves > 0) then
         self.nation:next_unit()
      end
   end
   return ok
end


function Unit:selectable()
   return self.moves > 0
end
