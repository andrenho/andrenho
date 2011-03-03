package.path = package.path .. ';./game/?.lua'
require 'static'
require 'nation'

Game = {}

-- New game
function Game:new(w, h, player_nation, o)
   self.__index = self
   o = setmetatable(o or {}, self)
   o:create_map(w, h)
	o.year = -2000
	o.player = Nation:new(player_nation)
	o.nations = { o.player }
   return o
end


-- Initialize map
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

	for x=3,9 do
		for y=3,9 do
			self.map[x][y].terrain = sea
		end
	end
	for x=4,8 do
		for y=4,8 do
			self.map[x][y].terrain = plains
		end
	end
	self.map[5][5].terrain = mixed_f
	self.map[5][6].terrain = mixed_f
	self.map[6][6].terrain = desert
end


-- Return a string to be printed in the bottom of the screen
function Game:year_str()
	return (_'Year %d %s'):format(math.abs(self.year), 'B.C.')
end
