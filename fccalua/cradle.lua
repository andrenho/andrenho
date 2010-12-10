require 'tileset'
require 'game'

char = {
   sea = '~',
   grass = ' ',
   soldier = 'S',
   peasant = '@',
}

--
-- initialize tileset
--
function init_tileset_bw()
   T = Tileset.new(8, 8)
   for i=0,255 do
      T.load_image(0, i, 'terminal.png', math.floor(i/16) * 8, (i%16) * 8)
   end
   for i=0,255 do
      T.load_image(2, i, 'terminal2.png', math.floor(i/16) * 8, (i%16) * 8)
   end
   T.update()
end


--
-- draw map
--
rx, ry = 0, 0
function draw()
   -- draw map
   for x=0,(G.map_w-1) do
      for y=0,(G.map_h-1) do
         t = G.map(x,y)
         if t.terrain == GRASSLAND then
            T.set_char(0, char.grass, x, y)
         elseif t.terrain == OCEAN then
            T.set_char(0, char.sea, x, y)
         end
         if #t.units() > 0 then
            u = t.units()[1]
            if u.military == SOLDIER then
               T.set_char(0, char.soldier, x, y)
            elseif u.military == PEASANT then
               T.set_char(0, char.peasant, x, y)
            end
         end
      end
   end

   -- draw other info
   T.print(2, 
      string.format("%s   Year: %d B.C.", G.player.name, -G.year), 
      1, T.h()-2)
   if G.selected then
      local u = G.selected
      T.print(2,
         string.format("%s   Moves: %d", u.military.name, u.moves),
         1, T.h()-1)
   end

   T.update()
end


--
-- parse events
--
function move_unit(e)
   local u = G.selected
   local keys = {
      { 'kp_1', nil,    -1, 1 },
      { 'kp_2', 'down',  0, 1 },
      { 'kp_3', nil,     1, 1 },
      { 'kp_4', 'left', -1, 0 },
      { 'kp_6', 'right', 1, 0 },
      { 'kp_7', nil,    -1,-1 },
      { 'kp_8', 'up',    0,-1 },
      { 'kp_9', nil,     1,-1 },
   }
   for _,a in ipairs(keys) do
      if e.key == a[1] or e.key == a[2] then
         u.move(a[3], a[4])
         return true
      end
   end
   return false
end

function event()
   local e = T.get_event()
   if e.type == 'quit' or (e.type == 'key' and e.key == 'q') then
      running = false
   elseif e.type == 'key' then
      -- unit keystrokes
      if G.selected then
         if move_unit(e) then 
            return 
         end
      end
   end
end


--
-- initialize game
--
init_tileset_bw()
G = Game.new(10, 10, 'Assyria')

running = true
while running do
   draw()
   event()
end
