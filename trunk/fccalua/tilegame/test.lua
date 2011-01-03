require 'map'
require 'luasdl'

SDL.Init()
scr = SDL.SetVideoMode(100, 100)
img = SDL.IMG_Load('terminal.png')
if not img then
   error 'Error loading terminal.png'
end
scr:FillRect(nil, scr.format:MapRGB(255, 255, 255))


tg = TileGameMap:new(8, 8)
tile_A = tg:tile(img, 32, 8, 1)
tg:blit(tile_A, 3, 3, 4, 4)
tg:test()

scr:Flip()



running = true
while running do
   e = SDL.WaitEvent()
   if e.type == SDL.QUIT or (e.type == SDL.KEYDOWN and e.sym == SDL.q) then
      running = false
   end
end
