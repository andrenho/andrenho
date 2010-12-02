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



