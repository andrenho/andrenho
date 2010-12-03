Town = {}
function Town.new(G, nation, name, x, y, unit)
   local self = {}

   --
   -- Variables
   --
   self.nation = nation
   self.name = name
   self.x, self.y = x, y
   self.unit = unit

   return self
end
