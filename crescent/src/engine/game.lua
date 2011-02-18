package.path = package.path .. ';./src/engine/?.lua'
require 'static'

Game = {}

function Game:new(w, h)
   self.__index = self
   o = setmetatable({}, self)
   o:create_map(w, h)
   return o
end


function Game:create_map(w, h)
   self.map = {}
   for x=1,w do
      self.map[x] = {}
      for y=1,h do
         self.map[x][y] = { terrain = ocean,
                            special = false,
                            river = false,
                            road = false,
                            plow = false }
      end
   end
end
