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

   -- check for ship on land or unit on water
   local nx, ny = self.x+fx, self.y+fy
   if self.military.ship and self.game.map[nx][ny].terrain ~= sea then 
      ok = false 
   elseif not self.military.ship and self.game.map[nx][ny].terrain == sea then 
      ok = false
   end

   -- move unit
   if ok then
      self.game.map[self.x][self.y].dirty = true
      self.x = self.x + fx
      self.y = self.y + fy
      self.game.map[self.x][self.y].dirty = true
      self.moves = self.moves - cost
      if not (self.moves > 0) then -- select next unit
         self.nation:next_unit()
         -- auto end turn
         if not self.nation.focused and self.game.options.auto_end_turn then
            self.nation:end_turn()
         end
      end
   end
   return ok
end


function Unit:selectable()
   return self.moves > 0
end


function Unit:build_city(name)
   c = City:new {
      name = name,
      x = self.x,
      y = self.y,
      nation = self.nation,
      game = self.game,
   }
   c:initialize()
   table.insert(self.nation.cities, c)
   c:auto_join_unit(self)
	return c
end
