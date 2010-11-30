require('fcca')

--
-- print map
--
function print_map()
  for y=0,G.map_h-1 do
    for x=0,G.map_w-1 do
      local tile = G.map(x,y)
      local units = tile.units()
      if #units == 0 then
        if tile.terrain == OCEAN then
          io.write('~~')
        elseif tile.terrain == GRASSLAND then
          io.write('  ')
        end
      else
        io.write('S*')
      end
    end
    io.write('\n')
  end
  io.write(string.format('Year: %d    Gold: $%d\n', G.year, G.player.gold))
  io.write(string.format('%s   Moves: %d\n', G.selected.military.name, G.selected.moves))
end

--
-- main loop
--
os.execute('cls')
G = Game.new(10, 10, { 'Assyria' })
running = true

while(running) do
  print_map()
  io.write('> ')
  cmd = io.read('*line')
  os.execute('cls')
  if cmd == 'q' then
    break
  elseif cmd == '1' then
    G.selected.move(-1,1)
  elseif cmd == '2' then
    G.selected.move(0,1)
  elseif cmd == '3' then
    G.selected.move(1,1)
  elseif cmd == '4' then
    G.selected.move(-1,0)
  elseif cmd == '6' then
    G.selected.move(1,0)
  elseif cmd == '7' then
    G.selected.move(-1,-1)
  elseif cmd == '8' then
    G.selected.move(0,-1)
  elseif cmd == '9' then
    G.selected.move(1,-1)
  elseif cmd == 't' then
    G.player.end_turn()
  else
    io.write('** Syntax error\n')
  end
end
