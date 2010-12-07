require 'tileset'
require 'game'

char = {
   sea = 176,
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
   T.set_char(0, char.sea, 0, 1)
   T.set_char(0, char.sea, 1, 1)
   T.set_char(2, 'A', 1, 1)
   T.set_char(2, char.sea, 2, 1)
   T.update()
end


--
-- draw map
--
function draw()
end


--
-- parse events
--
function event()
   e = T.get_event()
   if e.type == 'quit' or (e.type == 'key' and e.key == 'q') then
      running = false
   end
end


--
-- initialize game
--
init_tileset_bw()
G = Game.new(10, 10)

running = true
while running do
   draw()
   event()
end
