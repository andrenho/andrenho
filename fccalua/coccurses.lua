require 'cradle'
require 'libtcodlua'

options = {
  colors = false,
  map_w = 50,
  map_h = 40,
}


chars = {
  [OCEAN] = { '~', tcod.color.white, tcod.color.darkerBlue },
  [GRASSLAND] = { ' ', tcod.color.white, tcod.color.darkerGreen },
  [SOLDIER] = { 'S' },
}

function draw()
  root:clear()
  for x=0,(options.map_w-1) do
    for y=0,(options.map_h-1) do
      -- TODO check bounds
      local units = G.map(x,y).units()
      if #units > 0 then
        root:print(x+rx, y+ry, chars[units[1].military][1])
      else
        chr = chars[G.map(x,y).terrain]
        if colors then
          root:putCharEx(x+rx, y+ry, string.byte(chr[1]),
                      chr[2], chr[3])
        else
          root:putChar(x+rx, y+ry, string.byte(chr[1]))
        end
      end
    end
  end
  tcod.console.flush()
end


function events()

  function quit()
    os.exit()
  end

  key = tcod.console.waitForKeypress(true)
  ev = {
    ['q'] = { quit }
  }
  if ev[key.Character] then ev[key.Character][1]() end
end


-- initialize
G = Game.new(options.map_w, options.map_h, 'Assyria')
rx, ry = 0, 0
tcod.console.initRoot(80, 50, 'CoC')
root=libtcod.TCODConsole_root
if not options.colors then
  root:setDefaultBackground(tcod.color.white)
  root:setDefaultForeground(tcod.color.darkGrey)
end

-- main loop
playing = true
while playing do
  draw()
  events()
end
