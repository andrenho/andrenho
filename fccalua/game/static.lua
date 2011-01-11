require 'i18n'

--
-- Goods
-- 
goods = {}
local function good(name, can_buy, initial_prices, raw_material)
   local g = {
      name = name,
      can_buy = can_buy,
      initial_prices = initial_prices,
      raw_material = raw_material,
   }
   table.insert(goods, g)
   return g
end

food =      good(_'Food', true, { 1,8 })
cotton =    good(_'Cotton', true, { 4,6 })
barley =    good(_'Barley', true, { 4,6 })
olives =    good(_'Olives', true, { 6,8 })
wood =      good(_'Wood', true, { 1,6 })
copper =    good(_'Copper', true, { 5,8 })
mud =       good(_'Mud', true, { 1,5 })
tin =       good(_'Tin', true, { 7,9 })
gold =      good(_'Gold', true, { 15,16 })
clothes =   good(_'Clothes', true, { 12,13 }, { cotton })
beer =      good(_'Beer', true, { 10,11 }, { beer })
olive_oil = good(_'Olive Oil', true, { 12,13 }, { olives })
furniture = good(_'Furniture', true, { 10,11 }, { wood })
utensils =  good(_'Utensils', true, { 12,13 }, { copper })
bricks =    good(_'Bricks', true, { 1,8 }, { mud })
riding =    good(_'Riding Animals', true, { 5,8 })
bronze =    good(_'Bronze', true, { 9,10 }, { copper, tin })
weapons =   good(_'Weapons', true, { 6,7 }, { wood, bronze })
scrolls =   good(_'Scrolls', false)
prayers =   good(_'Prayers', false)

-- 
-- Terrains
--
terrains = {}
local function terrain(name, cost_to_enter, defensive_bonus, production, switch_status)
local function good_production(p)
   if not p then return {} end
   local pp = {}
   for i,v in ipairs(p) do pp[goods[i]] = v end
   return pp
end
local t = {
   name = name,
   production = good_production(production),
   switch_status = switch_status,
}
if switch_status then switch_status.switch_status = t end -- swap
table.insert(terrains, t)
return t
end

--                 Name              MoveCost      Barley      Mud
--                                      Defence       Olives      Tin
--                                           Food        Wood        Gold
--                                              Cotton      Copper
tundra   = terrain(_'Tundra',        1, 0, { 2, 0, 0, 0, 0, 2, 2, 1, 0 })
desert   = terrain(_'Desert',        1, 0, { 1, 0, 0, 2, 0, 1, 3, 2, 0 })
plains   = terrain(_'Planis',        1, 0, { 4, 2, 1, 0, 0, 1, 1, 0, 0 })
prairie  = terrain(_'Prairie',       1, 0, { 3, 3, 0, 0, 0, 0, 0, 0, 0 })
steppe   = terrain(_'Steppe',        1, 0, { 2, 2, 3, 0, 0, 0, 0, 0, 0 })
marsh    = terrain(_'Marsh',         2, 1, { 3, 1, 2, 0, 0, 2, 4, 2, 0 })

boreal_f = terrain(_'Boreal forest', 2, 2, { 1, 0, 0, 0, 2, 1, 1, 1, 0 }, tundra)
scrub    = terrain(_'Scrubland',     1, 2, { 1, 0, 0, 4, 1, 1, 2, 1, 0 }, desert)
mixed_f  = terrain(_'Mixed forest',  2, 2, { 2, 1, 0, 0, 3, 0, 1, 0, 0 }, plains)
savannah = terrain(_'Savannah',      1, 1, { 1, 1, 0, 0, 2, 0, 1, 0, 0 }, prairie)
woodland = terrain(_'Woodland',      2, 2, { 1, 0, 1, 0, 2, 0, 1, 0, 0 }, steppe)
swamp    = terrain(_'Swamp',         3, 3, { 2, 0, 0, 0, 1, 1, 3, 2, 0 }, marsh)

arctic   = terrain(_'Arctic',        2, 0, { 0, 0, 0, 0, 0, 1, 0, 1, 1 })
sea      = terrain(_'Sea',           1, 0, { 3, 0, 0, 0, 0, 0, 0, 0, 0 })
ocean    = terrain(_'Ocean',         1, 0, { 3, 0, 0, 0, 0, 0, 0, 0, 0 })
hills    = terrain(_'Hills',         2, 4, { 1, 0, 0, 0, 0, 3, 0, 3, 0 })
mountain = terrain(_'Mountains',     3, 6, { 0, 0, 0, 0, 0, 3, 0, 3, 1 })

--
-- Military classes
--
militaries = {}
local function military(name, ship, moves, attack, defense, cargo)
local m = {
   name = name,
   ship = ship,
   moves = moves,
   attack = attack,
   defense = defense,
   cargo = cargo,
}
table.insert(militaries, m)
return m
end

peasant         = military(_'Peasant',                 false, 1, 0, 1, 0)
colonist        = military(_'Colonist',                false, 1, 0, 1, 0)
warrior         = military(_'Warrior',                 false, 1, 2, 2, 0)
nomad           = military(_'Nomad',                   false, 4, 1, 1, 0)
chariot         = military(_'Chariot',                 false, 4, 3, 3, 0)
pikeman         = military(_'Pikeman',                 false, 1, 3, 3, 0)
mtd_pikeman     = military(_'Mounted Pikeman',         false, 4, 4, 4, 0)
armored_warrior = military(_'Armed Warrior',           false, 1, 4, 4, 0)
cataphract      = military(_'Cataphract',              false, 4, 5, 5, 0)
catapult        = military(_'Catapult',                false, 1, 7, 5, 0)

clan_member     = military(_'Clan Member',             false, 1, 1, 1, 0)
clan_armed      = military(_'Armed Clan Member',       false, 1, 2, 2, 0)
clan_mounted    = military(_'Clan Member Rider',       false, 4, 2, 2, 0)
clan_mtd_armed  = military(_'Armed Clan Member Armed', false, 4, 3, 3, 0)

elite_soldier   = military(_'Elite Soldier',           false, 1, 4, 4, 0)
elite_chariot   = military(_'Elite Chariot',           false, 4, 5, 5, 0)
faraoh_soldier  = military(_"Faraoh's Guard",          false, 1, 5, 5, 0)
faraoh_chariot  = military(_"Faraoh's Chariot Guard",  false, 4, 6, 6, 0)

penteconter     = military(_'Penteconter',             true,  4, 0, 2, 2)
merchantman     = military(_'Merchantman',             true,  6, 0, 6, 5)
monoreme        = military(_'Monoreme',                true,  4, 1, 3, 0)
bireme          = military(_'Bireme',                  true,  5, 3, 5, 0)
trireme         = military(_'Trireme',                 true,  6, 4, 6, 0)
galley          = military(_'Galley',                  true,  5, 7, 8, 6)
pirate_ship     = military(_'Pirate Ship',             true,  8, 4, 8, 2)


-- 
-- Jobs
--
local function job(name)
   return {
      name = name,
   }
end

farmer       = job(_'Farmer')
cotton_pl    = job(_'Cotton Planter')
barley_pl    = job(_'Barley Planter')
olive_pl     = job(_'Olives Planter')
lumberjack   = job(_'Lumberjack')
copper_miner = job(_'Copper Miner')
mudder       = job(_'Mudder')
tin_miner    = job(_'Tin Miner')
prospector   = job(_'Prospector')
weaver       = job(_'Weaver')
brewer       = job(_'Brewer')
oil_presser  = job(_'Oil Presser')
carpenter    = job(_'Carpenter')
coppersmith  = job(_'Coppersmith')
brickmaker   = job(_'Brickmaker')
metallurgic  = job(_'Metallurgic')
weaponsmith  = job(_'Weaponsmith')
scribe       = job(_'Scribe')
priest       = job(_'Priest')

--
-- Buildings
--
local function building(name, job, raw_good, good, multiplier, cost, 
      copper, min_colony)
   local b = {
      name = name,
      job = job,
      raw_good = raw_good,
      good = good,
      multiplier = mutiplier or 1, -- 3 = factory double production
      cost = cost or 0, -- 0 = starting building
      copper = copper or 0,
      min_colony = min_colony or 0,
   }
   if job then 
      job.building = b
      job.raw_good = raw_good
      job.good = good
   end
   return b
end

weaver_1    = building(_"Weaver's House", weaver, cotton, clothes)
weaver_2    = building(_"Weaver's Shop", weaver, cotton, clothes, 2, 64)a
weaver_3    = building(_"Weaver's Factory", weaver, 
brewer_1    = building(_"
brewer_2    = building(_"
brewer_3    = building(_"
oil_1       = building(_"
oil_2       = building(_"
oil_3       = building(_"
carpenter_1 = building(_"
carpenter_2 = building(_"
copper_1    = building(_"
copper_2    = building(_"
copper_3    = building(_"
brick_1     = building(_"
brick_2     = building(_"
brick_3     = building(_"
stable      = building(_"
bronze_1    = building(_"
bronze_2    = building(_"
bronze_3    = building(_"
scribe_1    = building(_"
scribe_2    = building(_"
scribe_3    = building(_"
temple_1    = building(_"
temple_2    = building(_"
temple_3    = building(_"
embassy     = building(_"
docks_1     = building(_"
docks_2     = building(_"
docks_3     = building(_"
wall_1      = building(_"
wall_2      = building(_"
wall_3      = building(_"
library     = building(_"
oracle      = building(_"
warehouse_1 = building(_"
warehouse_2 = building(_"
palace      = building(_"
monument    = building(_"
