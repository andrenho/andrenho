local PhysStaticObj = {}
PhysStaticObj.__index = PhysStaticObj

function PhysStaticObj:new(x, y, w, h)
   local self = setmetatable({}, PhysStaticObj)
   self.body = love.physics.newBody(phys.pworld, x, y)
   self.shape = love.physics.newRectangleShape(w, h)
   self.fixture = love.physics.newFixture(self.body, self.shape)
   return self
end

-------------
-- PRIVATE --
-------------

function PhysStaticObj:__tostring()
   return '[PhysStaticObj]'
end

function PhysStaticObj:type() return 'PhysStaticObj' end

return PhysStaticObj

-- vim: ts=3:sw=3:sts=3:expandtab
