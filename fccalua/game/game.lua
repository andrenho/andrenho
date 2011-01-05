--package.path = package.path .. ';./game/?.lua'

Game = {}

function Game:new(o)
   self.__index = self
   return setmetatable(o or {}, self)
end


function Game:initialize()
	assert(self.map_w and self.map_h, "Initialization parameters missing.")
	self.map = {}
	for x=1,self.map_w do
		self.map[x] = {}
		for y=1,self.map_h do
			self.map[x][y] = {
				terrain = 'grassland',
				special = false,
				forest = false,
				road = false,
				plow = false
			}
		end
	end
	self:draw_map()
end


function Game:draw_map()
	for x=4,5 do
		for y=3,5 do
			self.map[x][y].terrain = 'ocean'
		end
	end
end
