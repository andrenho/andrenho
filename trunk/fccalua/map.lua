--
-- Tile
--
Tile = {}
function Tile.new(G, x, y, terrain)
   local self = {}


   --
   -- Variables
   --
   self.G = G
   self.terrain = terrain
   self.x, self.y = x, y
   self.town = nil


   --
   -- Returns all units in a given position
   --
   function self.units()
      local units = {}
      for _,n in ipairs(G.nations) do
         for _,u in ipairs(n.units) do
            if u.x == self.x and u.y == self.y then
               table.insert(units, u)
            end
         end
      end
      return units
   end


   --
   -- Return the cost to enter a given tile
   --
   function self.cost_to_enter()
      return self.terrain.cost_to_enter
   end


   --
   -- Creation string (for serialization).
   --
   function self.dump_create()
      return string.format('Tile.new(G, %d, %d, %s)', self.x, self.y, global_name(self.terrain))
   end

   return self
end

