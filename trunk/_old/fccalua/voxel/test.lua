require 'voxel'
require 'luasdl'

print 'starting...'

SDL.Init()
sf = SDL.SetVideoMode(400, 300)
sf:FillRect(nil, sf.format:MapRGB(255,255,255))
sf:Flip()


v = {
   map = {},
   inclination = 6
}

for x=1,100 do
   v.map[x] = {}
   for y=1,100 do
      v.map[x][y] = { h = 20, middle = { 91, 46, 0 }, top = { 0, math.random(90,110), 0 } }
   end
end
gsf = voxel(v)
gsf:Blit(nil, sf, nil)
sf:Flip()

print 'ok'

repeat
   e = SDL.WaitEvent()
until (e.type == SDL.QUIT) or (e.type == SDL.KEYDOWN and e.sym == SDL.q)
