--
-- Nation
--
Nation = {}
function Nation.new(G, name, player_type)
   local self = {}

   --
   -- Variables
   --
   self.G = G
   self.name = name
   self.player_type = player_type
   self.gold = 0
   self.units = {
      Unit.new(self.G, self, SOLDIER, 1, 1),
      Unit.new(self.G, self, SOLDIER, 1, 1)
   }


   --
   -- Initialize nation turn.
   -- --
   function self.init_turn()
      for _,u in ipairs(self.units) do
         u.new_turn()
      end
      G.selected = nil
      self.next_unit()
   end


   --
   -- Select next unit
   --
   function self.next_unit()
      -- no units
      if #self.units == 0 then 
         G.selected = nil
         return 
      end
      -- no selection
      if not G.selected then 
         G.selected = self.units[1] 
         if G.selected.moves > 0 then return end
      end
      -- find next
      local original = G.selected
      while true do
         G.selected = cnext(self.units, G.selected)
         if G.selected.moves > 0 then return end
         if G.selected == original then
            if G.selected.moves > 0 then 
               G.selected = original
            else
               G.selected = nil
               if options.auto_end_turn then self.end_turn() end
            end
            return
         end
      end
   end


   --
   -- Ends nation turn
   --
   function self.end_turn()
      self.G.next_player()
   end


   --
   -- Creation string (for serialization).
   --
   function self.dump_create()
      return string.format('Nation.new(G, %q)', self.name)
   end

   return self
end



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
   -- Return unit name.
   --
   function self.name()
      return self.military.name
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

