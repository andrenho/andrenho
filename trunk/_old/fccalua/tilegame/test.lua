require 'event'
require 'luasdl'

SDL.Init()
scr = SDL.SetVideoMode(100, 100)
img = SDL.IMG_Load('terminal.png')
if not img then
   error 'Error loading terminal.png'
end
scr:FillRect(nil, scr.format:MapRGB(255, 255, 255))


tg = TileGameEvent:new { 
   tile_w = 8, 
   tile_h = 8,
   map_w = 10,
   map_h = 10,
   rx = 2,
   ry = 2,
   scr = scr
}
tg.blank = tg:tile(img, 0, 0, 1)
tg:initialize()

tile_A = tg:tile(img, 32, 8, 1)
tile_pt = tg:tile(img, 24, 96, 1)
tg.map[4][4] = { tile_pt }
tg.map[4][5] = { tile_pt }
tg.map[4][6] = { tile_pt }
tg.map[5][4] = { tile_pt }
tg.map[5][6] = { tile_pt }
tg.map[6][4] = { tile_pt }
tg.map[6][5] = { tile_pt }
tg.map[6][6] = { tile_pt }
tg.map[5][5] = { tile_A }
tg:blit_map(0, 0)

scr:Flip()



running = true
while running do
   e = tg:wait_event()
   if e.type == SDL.QUIT or (e.type == SDL.KEYDOWN and e.sym == SDL.q) then
      running = false
   elseif (e.type == SDL.KEYDOWN and e.key == SDL.K) then
      tg:move({ tile_A }, 5, 5, 1, 1)
   end
end
