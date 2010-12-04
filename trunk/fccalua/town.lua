Town = {}
function Town.new(G, nation, name, x, y, unit)
   local self = {}

   --
   -- Variables
   --
   self.G = G
   self.nation = nation
   self.name = name
   self.x, self.y = x, y
   self.unit = unit

   function self.initialize()
      self.G.map(self.x, self.y).town = self
      return self
   end

   return self.initialize()
end
