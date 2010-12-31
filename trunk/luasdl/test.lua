require 'luasdl'

local clock = os.clock
function sleep(n)  -- seconds
  local t0 = clock()
  while clock() - t0 <= n do end
end


SDL.Init()
video = SDL.SetVideoMode(400, 300)
SDL.WM_SetCaption("teste")

while true do
	e = SDL.WaitEvent()
	if e.type == SDL.QUIT then
		break
	elseif e.type == SDL.ACTIVEEVENT then
		print(e.gain)
	elseif e.type == SDL.KEYDOWN then
		if e.sym == SDL.q then break end
	end
end
