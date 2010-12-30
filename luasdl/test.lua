require 'luasdl'

SDL.Init()

video = SDL.SetVideoMode(400, 300)
print(video:Flip())