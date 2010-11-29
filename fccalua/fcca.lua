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
function terrain(lua_name, name_unforested, name_forested, is_water)
  return { lua_name = lua_name, 
           name_unforested = name_unforested,
           name_forested = name_forested,
           is_water = is_water }
end
OCEAN = terrain('OCEAN', _("Ocean"), _("Error"), true)
GRASSLAND = terrain('GRASSLAND', _("Grassland"), _("Forest (?)"), false)

-- Militaries
function military(lua_name, name)
  return { lua_name = lua_name, name = name }
end
SOLDIER = military('SOLDIER', _("Soldier"))

static = { OCEAN, GRASSLAND, SOLDIER }


-----------------
--             --
--   Classes   --
--             --
-----------------

--
-- Serialization
--
function basicSerialize(o)
  if type(o) == 'string' then
    return string.format("%q", o)
  else   -- assume it is a string
    return tostring(o)
  end
end

function dump(name, value, saved)
  saved = saved or {}
  if type(value) == 'function' then return end
  io.write(name, ' = ')
  if type(value) == "number" or type(value) == "string" 
  or type(value) == "boolean" then
   io.write(basicSerialize(value), "\n")
  elseif type(value) == 'string' then
    io.write(string.format('%q', value))
  elseif type(value) == 'table' then
    if saved[value] then
      io.write(saved[value], '\n')
    else
      saved[value] = name
      if value.dump_create then
        io.write(value.dump_create() .. '\n')
      else
        io.write('{}\n')
      end
      for k,v in pairs(value) do
        local fieldname = string.format('%s[%s]', name,
                                        basicSerialize(k))
        dump(fieldname, v, saved)
      end
    end
  else
    error('cannot save a ' .. type(value))
  end
end

--
-- Game
--
Game = {}
function Game.new(w, h, nation_names)
  local self = {}

  self.year = -2000
  self.map_w = w
  self.map_h = h
  self._map = {}
  self.nations = {}

  function self.initialize()
    -- create map
    for i=0,(self.map_w * self.map_h)-1 do
      self._map[i] = 
          Tile.new(self, i % self.map_w, math.floor(i / self.map_w), GRASSLAND)
    end

    -- create nations
    for _,n in ipairs(nation_names) do
      table.insert(self.nations, Nation.new(self, n))
    end

    return self
  end

  function self.dump_create()
    local n = {}
    for nat in ipairs(self.nations) do
      table.insert(n, string.format("%q", 'Assyria')) -- TODO nat.name))
    end
    return string.format("Game.new(%d, %d, { %s })", self.map_w, self.map_h,
                         table.concat(n, ', '))
  end

  function self.map(x, y)
    return self._map[(y * self.map_w) + (x % self.map_w)]
  end

  return self.initialize()
end

--
-- Tile
--
Tile = {}
function Tile.new(G, x, y, terrain)
  local self = {}

  self.G = G
  self.terrain = terrain
  self.x, self.y = x, y

  function self.units()
    local units = {}
    for _,n in ipairs(G.nations) do
      for _,u in ipairs(n.units) do
        if u.x == self.x and u.y == self.y then
          table.insert(units, u)
        end
      end
    end
    return units
  end

  function self.dump_create()
    return string.format('Tile.new(G, %d, %d, %s)', self.x, self.y, self.terrain.lua_name)
  end

  return self
end

--
-- Nation
--
Nation = {}
function Nation.new(G, name)
  local self = {}

  self.G = G
  self.name = name
  self.gold = 0
  self.units = {
    Unit.new(G, SOLDIER, 2, 2)
  }

  function self.dump_create()
    return string.format('Nation.new(G, %q)', self.name)
  end

  return self
end

--
-- Unit
--
Unit = {}
function Unit.new(G, military, x, y)
  local self = {}

  self.G = G
  self.military = military
  self.x = x
  self.y = y

  function self.dump_create()
    return string.format('Unit.new(G, %s, %d, %d)', self.military.lua_name, self.x, self.y)
  end

  return self
end

--------------
--------------

dofile('temp.lua')
print(#G.map(2,2).units())
--G = Game.new(3, 3, { 'Assyria' })
--dump("G", G)
