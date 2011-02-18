package.path = package.path .. ';./src/engine/?.lua'
require 'static'
require 'map'

Game = {}

function Game:new()
   self.__index = self
   o = setmetatable({}, self)
   return o
end

