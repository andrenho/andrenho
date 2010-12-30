require 'luasdl'

SDL.Init()

video = SDL.SetVideoMode(400, 300)
print(video.c_data)
video2 = SDL.CreateRGBSurface(SDL.SWSURFACE, 100, 80, 8)
print(video2.c_data)
video:UpdateRect()
video2:UpdateRect()