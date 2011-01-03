--
-- Unit
--
Unit = {}
function Unit.new(G, nation, military, x, y)
   local self = {}

   --
   -- Variables
   --
   self.G = G
   self.military = military
   self.x = x
   self.y = y
   self.moves = military.moves
   self.nation = nation
   self.town = nil


   --
   -- Move unit.
   --
   function self.move(xdir, ydir)
      -- basic checks
      assert(xdir >= -1 and xdir <= 1)
      assert(ydir >= -1 and ydir <= 1)
      fx = self.x + xdir
      fy = self.y + ydir
      if fx < 0 or fx >= self.G.map_w-1 or fy < 0 or fy >= self.G.map_h-1 then
         return false
      end
      ft = self.G.map(fx, fy)
      if self.moves < ft.cost_to_enter() then return false end

      -- land units
      if not self.military.sea_unit then
         if ft.terrain.is_water then
            return false
         end

      -- sea units
      else
         error 'Not implemented'
      end

      -- move units
      self.x = fx
      self.y = fy
      self.moves = self.moves - ft.cost_to_enter()
      if self.moves == 0 then self.nation.next_unit() end
      return true
   end


   -- 
   -- Build a new town
   --
   function self.build_town(name)
      local t = Town.new(self.G, self.nation, name, self.x, self.y, self)
      if t then table.insert(self.nation.towns, t) end
      return t == true
   end


   -- 
   -- Return unit name.
   --
   function self.name()
      return self.military.name
   end


   -- 
   -- Return true if the unit can be selected
   --
   function self.can_be_selected()
      return self.moves > 0 and not self.town
   end


   -- 
   -- Prepare unit for a new 
   --
   function self.new_turn()
      self.moves = self.military.moves
   end


   --
   -- Creation string (for serialization).
   --
   function self.dump_create()
      return string.format('Unit.new(G, %s, %d, %d)', global_name(self.military), self.x, self.y)
   end

   return self
end

