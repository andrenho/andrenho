-- militaries
function military()
  return {}
end
SOLDIER = military()

-- terrains
function terrain(is_sea)
  return { is_sea = is_sea, }
end
OCEAN = terrain(true)
GRASSLAND = terrain(false)


--
-- New Game
--
function new_game(w, h, nations)

  local G = {
    year = -2000,
    nations = {},
    map = {},
    nations = {},
  }

  function tile(x, y, terrain)
    return { x=x, y=y, terrain=terrain }
  end
  
  function map(w, h)
    G.map = {}
    for i=0, (w*h) do
      G.map[i] = tile(0, 0, GRASSLAND)
    end
    G.w = w
    G.h = h
  end

  function landmass()
    for x=3,5 do
      for y=3,5 do
        G.map[(y*G.w)+x].terrain = OCEAN
      end
    end
  end

  function add_nation(nation)
    local nat = {
      name = nation,
      gold = 0,
      units = {},
    }
    table.insert(G.nations, #G.nations+1, nat)
  end

  map(w, h)
  landmass()
  for _,nation in ipairs(nations) do
    add_nation(nation)
  end
  return G

end


--
-- Create unit
--
function unit(nation, military, x, y)
  
end


-- 
-- Print game information
--
function print_game(G)
  for i,t in ipairs(G.map) do
    if t.terrain == OCEAN then
      io.write('~')
    elseif t.terrain == GRASSLAND then
      io.write(' ')
    end
    if (i+1) % G.w == 0 then 
      io.write('\n')
    end
  end
end



G = new_game(10, 10, { 'Assyria' })
print_game(G)
