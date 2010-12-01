-----------------
--             --
--   Options   --
--             --
-----------------
options = {
  auto_end_turn = true
}

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
static = {}

-- Terrains
function terrain(char, name_unforested, name_forested, is_water, cost_to_enter)
  local t = { char = char,
              name_unforested = name_unforested,
              name_forested = name_forested,
              is_water = is_water,
              cost_to_enter = cost_to_enter}
  table.insert(static, t)
  return t
end
OCEAN = terrain('O', _("Ocean"), _("Error"), true, 1)
GRASSLAND = terrain('G', _("Grassland"), _("Forest (?)"), false, 1)

-- Militaries
function military(char, name, sea_unit, moves)
  local m = { char=char,
              name=name, 
              sea_unit=sea_unit, 
              moves=moves }
  table.insert(static, m)
  return m
end
SOLDIER = military('S', _("Soldier"), false, 2)


-------------------------
--                     --
--   Helper functions  --
--                     --
-------------------------

-- ordered next
function inext(T, i)
  if i == nil then return T[1] end
  idx = -1
  for k,v in ipairs(T) do
    if v == i then idx = k end
  end
  if idx == -1 then error 'Key not found' end
  return T[idx+1]
end

-- circular next
function cnext(T, i)
  idx = -1
  for k,v in ipairs(T) do
    if v == i then idx = k end
  end
  if T[idx+1] then
    return T[idx+1]
  else
    return T[1]
  end
end
  

--
-- Serialization
--
function global_name(value)
  for k,v in pairs(_G) do
    if v == value then
      return k
    end
  end
  return nil
end

function basicSerialize(o)
  if type(o) == 'string' then
    return string.format("%q", o)
  else   -- assume it is a string
    return tostring(o)
  end
end

function dump(name, value, saved)
  function has_value(T, val)
    for _,v in ipairs(T) do
      if v == val then
        return true
      end
    end
    return false
  end

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
    elseif has_value(static, value) then
      io.write(global_name(value) .. '\n')
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

-----------------
--             --
--   Classes   --
--             --
-----------------

--
-- Game
--
Game = {}
function Game.new(w, h, human_players, computer_players)
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
    self.setup_map()

    -- create nations
    for _,n in ipairs(human_players) do
      table.insert(self.nations, Nation.new(self, n, 'H'))
    end
    self.player = self.nations[1]
    self.selected = self.player.units[1] -- TODO
    self.player.init_turn()

    return self
  end

  function self.map(x, y)
    return self._map[(y * self.map_w) + (x % self.map_w)]
  end

  function self.setup_map()
    for x=3,5 do
      for y=3,5 do
        self.map(x,y).terrain = OCEAN
      end
    end 
  end

  function self.next_player()
    self.player = inext(self.nations, self.player)
    if self.player == nil then
      self.year = self.year + 1
      self.player = self.nations[1]
    end
    self.player.init_turn()
  end

  function self.dump_create()
    local n = {}
    for _,nation in ipairs(self.nations) do
      table.insert(n, string.format("%q", nation.name))
    end
    return string.format("Game.new(%d, %d, { %s })", self.map_w, self.map_h,
                         table.concat(n, ', '))
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

  function self.cost_to_enter()
    return self.terrain.cost_to_enter
  end

  function self.dump_create()
    return string.format('Tile.new(G, %d, %d, %s)', self.x, self.y, global_name(self.terrain))
  end

  return self
end

--
-- Nation
--
Nation = {}
function Nation.new(G, name, player_type)
  local self = {}

  self.G = G
  self.name = name
  self.player_type = player_type
  self.gold = 0
  self.units = {
    Unit.new(self.G, self, SOLDIER, 1, 1),
    Unit.new(self.G, self, SOLDIER, 1, 1)
  }

  function self.dump_create()
    return string.format('Nation.new(G, %q)', self.name)
  end

  function self.init_turn()
    for _,u in ipairs(self.units) do
      u.new_turn()
    end
    G.selected = nil
    self.next_unit()
  end

  function self.next_unit()
    -- no units
    if #self.units == 0 then 
      G.selected = nil
      return 
    end
    -- no selection
    if not G.selected then 
      G.selected = self.units[1] 
      if G.selected.moves > 0 then return end
    end
    -- find next
    local original = G.selected
    while true do
      G.selected = cnext(self.units, G.selected)
      if G.selected.moves > 0 then return end
      if G.selected == original then
        if G.selected.moves > 0 then 
          G.selected = original
        else
          G.selected = nil
          if options.auto_end_turn then self.end_turn() end
        end
        return
      end
    end
  end

  function self.end_turn()
    self.G.next_player()
  end

  return self
end

--
-- Unit
--
Unit = {}
function Unit.new(G, nation, military, x, y)
  local self = {}

  self.G = G
  self.military = military
  self.x = x
  self.y = y
  self.moves = military.moves
  self.nation = nation

  --
  -- move unit
  --
  function self.move(xdir, ydir)
    -- basic checks
    assert(xdir >= -1 and xdir <= 1)
    assert(ydir >= -1 and ydir <= 1)
    fx = self.x + xdir
    fy = self.y + ydir
    if fx < 0 or fx >= self.G.map_w-1 or fy < 0 or fy >= self.G.map_h-1 then
      return false
    end
    ft = self.G.map(fx, fy)
    if self.moves < ft.cost_to_enter() then return false end

    -- land units
    if not self.military.sea_unit then
      if ft.terrain.is_water then
        return false
      end

    -- sea units
    else
      error 'Not implemented'
    end

    -- move units
    self.x = fx
    self.y = fy
    self.moves = self.moves - ft.cost_to_enter()
    if self.moves == 0 then self.nation.next_unit() end
    return true
  end

  function self.name()
    return self.military.name
  end

  function self.new_turn()
    self.moves = self.military.moves
  end

  function self.dump_create()
    return string.format('Unit.new(G, %s, %d, %d)', global_name(self.military), self.x, self.y)
  end

  return self
end

--------------
--------------

--dofile('temp.lua')
--[[
G = Game.new(10, 10, { 'Assyria' })
G.selected.move(1,0)
G.selected.move(1,0)
G.player.next_unit()
G.selected.move(1,0)
G.selected.move(1,0)
G.player.next_unit()
]]
--print(#G.map(2,2).units())
--print(G.nations[1].name)
--dump("G", G)
