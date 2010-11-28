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
		create_unit(G, nat, SOLDIER, 1, 1)
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
function create_unit(G, nation, military, x, y)
	table.insert(nation.units, #nation.units+1, {
		military = military,
		x = x,
		y = y,
	})
	return G
end


--
-- Unit in position x,y
--
function units_in_xy(G, x, y)
	units = {}
	for _,nation in ipairs(G.nations) do
		for _,unit in ipairs(nation.units) do
			if unit.x == x and unit.y == y then
				table.insert(units, 0, unit)
			end
		end
	end
	return units
end


-- 
-- Print game information
--
function print_game(G)
  for i,t in ipairs(G.map) do
		units = units_in_xy(G, (i+1) % G.w, (i+1) / G.h)
		if #units == 0 then
			if t.terrain == OCEAN then
				io.write('~')
			elseif t.terrain == GRASSLAND then
				io.write(' ')
			end
		else
			io.write('S')
		end
    if (i+1) % G.w == 0 then 
      io.write('\n')
    end
  end
end



G = new_game(10, 10, { 'Assyria' })
print_game(G)
