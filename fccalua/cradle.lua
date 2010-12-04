require 'util'
require 'static'
require 'map'
require 'units'
require 'town'


--
-- Options
--
options = {
   auto_end_turn = true
}


--
-- Game
--
Game = {}
function Game.new(w, h, player)
   local self = {}


   --
   -- variables
   --
   self.year = -2000
   self.map_w = w
   self.map_h = h
   self._map = {}
   self.nations = {}


   --
   -- Initialize game
   --
   function self.initialize()
      -- create map
      for i=0,(self.map_w * self.map_h)-1 do
         self._map[i] = 
               Tile.new(self, i % self.map_w, math.floor(i / self.map_w), GRASSLAND)
      end
      self.setup_map()

      -- create nations
      table.insert(self.nations, Nation.new(self, player, 'H'))
      self.player = self.nations[1]
      self.selected = self.player.units[1] -- TODO
      self.player.init_turn()

      return self
   end


   --
   -- return map tile
   --
   function self.map(x, y)
      return self._map[(y * self.map_w) + (x % self.map_w)]
   end


   -- 
   -- create the map
   --
   function self.setup_map()
      for x=3,5 do
         for y=3,5 do
            self.map(x,y).terrain = OCEAN
         end
      end 
   end


   --
   -- Select next nation to play.
   function self.next_player()
      self.player = inext(self.nations, self.player)
      if self.player == nil then
         self.year = self.year + 1
         self.player = self.nations[1]
      end
      self.player.init_turn()
   end


   --
   -- Creation string (for serialization).
   --
   function self.dump_create()
      local n = {}
      for _,nation in ipairs(self.nations) do
         table.insert(n, string.format("%q", nation.name))
      end
      return string.format("Game.new(%d, %d, { %s })", self.map_w, self.map_h,
                                     table.concat(n, ', '))
   end

   return self.initialize()
end



--------------
--------------

--dofile('temp.lua')
--[[
G = Game.new(10, 10, { 'Assyria' })
G.selected.move(1,0)
G.selected.move(1,0)
G.player.next_unit()
G.selected.move(1,0)
G.selected.move(1,0)
G.player.next_unit()
]]
--print(#G.map(2,2).units())
--print(G.nations[1].name)
--dump("G", G)
