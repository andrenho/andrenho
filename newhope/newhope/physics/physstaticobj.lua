local PhysStaticObj = {}
PhysStaticObj.__index = PhysStaticObj

function PhysStaticObj:new(x, y, w, h)
  local self = setmetatable({}, PhysStaticObj)
  self.body = love.physics.newBody(physics.pworld, x, y)
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

-- vim: ts=4:sw=4:sts=4:expandtab
