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

-- vim: ts=4:sw=4:sts=4:expandtab
