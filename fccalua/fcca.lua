---------------------
--                 --
--   Translation   --
--                 --
---------------------
function _(s)
  return s
end


---------------------
--                 --
--   Static Data   --
--                 --
---------------------

-- Terrains
function terrain(name_unforested, name_forested, is_water)
  return { name_unforested = name_unforested,
           name_forested = name_forested,
           is_water = is_water }
end
OCEAN = terrain(_("Ocean"), _("Error"), true)
GRASSLAND = terrain(_("Grassland"), _("Forest (?)"), false)

-- Militaries
function military(name)
  return { name = name }
end
SOLDIER = military(_("Soldier"))

static = { OCEAN, GRASSLAND, SOLDIER }


-----------------
--             --
--   Classes   --
--             --
-----------------

--
-- Game
--
Game = {}
function Game.new(w, h, nation_names)
  local self = {}

  self.year  = -2000
  self.map_w = w
  self.map_h = h
  self._map = {}
  self.nations = {}

  function self.map(x, y)
    return self._map[(y * self.map_w) + (math.floor(x % self.map_w))]
  end

  -- create map
  for i=0,(self.map_w * self.map_h)-1 do
    table.insert(self._map, tile(GRASSLAND))
  end

  -- create nations
  for _,n in ipairs(nation_names) do
    table.insert(self.nations, Nation.new(n))
  end

  return self
end

--
-- Tile
--
function tile(terrain)
  return { terrain = terrain }
end

--
-- Nation
--
Nation = {}
function Nation.new(name)
  local self = {}

  self.name = name
  self.gold = 0
  self.units = {}

  return self
end

--
-- Unit
--
Unit = {}
function Unit.new(military, x, y)
  local self = {}

  self.military = military
  self.x = x
  self.y = y

  return self
end

--------------
--------------

G = Game.new(10, 10, { 'Assyria' })
print(G.year)
print(G.map(2,3).terrain.name_unforested)
