City = {}


function City:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function City:initialize()
   assert(self.name and self.x and self.y and self.nation and self.game,
      'One of the initialization parameters is missing.')
   self.buildings = { weaver_1, brewer_1, oil_1, carpenter_1, copper_1,
                      brick_1, bronze_1, scribe_1 }
   self.storage = {}
   self.workers = {}
   self.building_now = { building = docks_1, hammers = 0 }
   for _,g in ipairs(goods) do
      if g.can_buy then
         self.storage[g] = 0
      end
   end
end


function City:auto_join_unit(unit)
   unit.city = self
   -- TODO - give a job
end
