local Physics = {}
Physics.__index = Physics

function Physics:new()
   local self = setmetatable({}, Physics)
   love.physics.setMeter(16)
   self.pworld = love.physics.newWorld(0, 0, true)
   self.objects = {}
   return self
end

function Physics:add_object(obj)
   self.objects[#self.objects+1] = obj
end

-------------
-- PRIVATE --
-------------

function Physics:__tostring()
   return '[Physics]'
end

function Physics:type() return 'Physics' end

return Physics

-- vim: ts=3:sw=3:sts=3:expandtab
