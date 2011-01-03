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
      Unit.new(self.G, self, PEASANT, 1, 1),
   }
   self.towns = {}


   --
   -- Initialize nation turn.
   -- --
   function self.init_turn()
      for _,u in ipairs(self.units) do
         u.new_turn()
      end
      G.selected = nil
      self.next_unit(true)
   end


   --
   -- Select next unit
   --
   function self.next_unit(from_init_turn)
      -- no units
      if #self.units == 0 then 
         G.selected = nil
         return 
      end
      -- no selection
      if not G.selected then 
         G.selected = self.units[1] 
         if G.selected.can_be_selected() then return end
      end
      -- find next
      local original = G.selected
      while true do
         G.selected = cnext(self.units, G.selected)
         if G.selected.can_be_selected() then return end
         if G.selected == original then
            if G.selected.can_be_selected() then 
               G.selected = original
            else
               G.selected = nil
               if options.auto_end_turn and not from_init_turn then 
                  self.end_turn() 
               end
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
