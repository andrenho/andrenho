local Game = {}
Game.__index = Game

function Game:new(world_)
   local self = setmetatable({}, Game)
   world = world_
   return self
end

-------------
-- PRIVATE --
-------------

function Game:__tostring()
   return '[Game]'
end

function Game:type() return 'Game' end

return Game

-- vim: ts=3:sw=3:sts=3:expandtab
