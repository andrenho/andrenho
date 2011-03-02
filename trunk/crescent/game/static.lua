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

food =      good(_'Food',      true, {  1, 8 })
cotton =    good(_'Cotton',    true, {  4, 6 })
barley =    good(_'Barley',    true, {  4, 6 })
olives =    good(_'Olives',    true, {  6, 8 })
wood =      good(_'Wood',      true, {  1, 6 })
copper =    good(_'Copper',    true, {  5, 8 })
mud =       good(_'Mud',       true, {  1, 5 })
tin =       good(_'Tin',       true, {  7, 9 })
gold =      good(_'Gold',      true, { 15,16 })
clothes =   good(_'Clothes',   true, { 12,13 }, { cotton })
beer =      good(_'Beer',      true, { 10,11 }, { beer })
olive_oil = good(_'Olive Oil', true, { 12,13 }, { olives })
furniture = good(_'Furniture', true, { 10,11 }, { wood })
utensils =  good(_'Utensils',  true, { 12,13 }, { copper })
bricks =    good(_'Bricks',    true, {  1, 8 }, { mud })
riding =    good(_'Animals',   true, {  5, 8 })
bronze =    good(_'Bronze',    true, {  9,10 }, { copper, tin })
weapons =   good(_'Weapons',   true, {  6, 7 }, { wood, bronze })
scrolls =   good(_'Scrolls',   false)
prayers =   good(_'Prayers',   false)

-- 
-- Terrains
--
terrains = {}
local function terrain(name, code, ovl, cost_to_enter, defensive_bonus, production, switch_status)
   local function good_production(p)
      if not p then return {} end
      local pp = {}
      for i,v in ipairs(p) do pp[goods[i]] = v end
      return pp
   end
   local t = {
      name = name,
		ovl = ovl,
      code = code,
      production = good_production(production),
      switch_status = switch_status,
   }
   if switch_status then switch_status.switch_status = t end -- swap
   table.insert(terrains, t)
   return t
end

--                 Name               Code  MoveCost      Barley      Mud
--                                        Ovl*  Defence       Olives      Tin
--                                                  Food        Wood        Gold
--                                                     Cotton      Copper
tundra   = terrain(_'Tundra',         1, 12, 1, 0, { 2, 0, 0, 0, 0, 2, 2, 1, 0 })
desert   = terrain(_'Desert',         2, 13, 1, 0, { 1, 0, 0, 2, 0, 1, 3, 2, 0 })
plains   = terrain(_'Planis',         3, 14, 1, 0, { 4, 2, 1, 0, 0, 1, 1, 0, 0 })
prairie  = terrain(_'Prairie',        4, 15, 1, 0, { 3, 3, 0, 0, 0, 0, 0, 0, 0 })
steppe   = terrain(_'Steppe',         5, 16, 1, 0, { 2, 2, 3, 0, 0, 0, 0, 0, 0 })
marsh    = terrain(_'Marsh',          6, 17, 2, 1, { 3, 1, 2, 0, 0, 2, 4, 2, 0 })

boreal_f = terrain(_'Boreal forest',  7,  6, 2, 2, { 1, 0, 0, 0, 2, 1, 1, 1, 0 }, tundra)
scrub    = terrain(_'Scrubland',      8,  7, 1, 2, { 1, 0, 0, 4, 1, 1, 2, 1, 0 }, desert)
mixed_f  = terrain(_'Mixed forest',   9,  8, 2, 2, { 2, 1, 0, 0, 3, 0, 1, 0, 0 }, plains)
savannah = terrain(_'Savannah',      10,  9, 1, 1, { 1, 1, 0, 0, 2, 0, 1, 0, 0 }, prairie)
woodland = terrain(_'Woodland',      11, 10, 2, 2, { 1, 0, 1, 0, 2, 0, 1, 0, 0 }, steppe)
swamp    = terrain(_'Swamp',         12, 11, 3, 3, { 2, 0, 0, 0, 1, 1, 3, 2, 0 }, marsh)

arctic   = terrain(_'Arctic',        13,  5, 2, 0, { 0, 0, 0, 0, 0, 1, 0, 1, 1 })
sea      = terrain(_'Sea',           14,  2, 1, 0, { 3, 0, 0, 0, 0, 0, 0, 0, 0 })
ocean    = terrain(_'Ocean',         15,  1, 1, 0, { 3, 0, 0, 0, 0, 0, 0, 0, 0 })
hills    = terrain(_'Hills',         16,  4, 2, 4, { 1, 0, 0, 0, 0, 3, 0, 3, 0 })
mountain = terrain(_'Mountains',     17,  3, 3, 6, { 0, 0, 0, 0, 0, 3, 0, 3, 1 })
-- *Ovl: Overlap for terrains.


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
fisherman    = job(_'Fisherman')
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
potter       = job(_'Potter')
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
weaver_2    = building(_"Weaver's Shop", weaver, cotton, clothes, 2, 64, 20)
weaver_3    = building(_"Cloth Mill", weaver, cotton, clothes, 3, 160, 100, 8)
brewer_1    = building(_"Brewer's House", brewer, barley, beer)
brewer_2    = building(_"Brewer's Shop", brewer, barley, beer, 2, 64, 20)
brewer_3    = building(_"Beer Mill", brewer, barley, beer, 3, 160, 100, 8)
oil_1       = building(_"Small Oil Press", oil_presser, olives, olive_oil)
oil_2       = building(_"Big Oil Press", oil_presser, olives, olive_oil, 2, 64, 20)
oil_3       = building(_"Olive Oil Mill", oil_presser, olives, olive_oil, 3, 160, 100, 8)
carpenter_1 = building(_"Carpenter's House", carpenter, wood, furniture)
carpenter_2 = building(_"Carpenter's Shop", carpenter, wood, furniture, 2, 64, 20)
carpenter_3 = building(_"Lumber Mill", carpenter, wood, furniture, 3, 160, 100, 8)
copper_1    = building(_"Coppersmith's House", coppersmith, copper, utensils)
copper_2    = building(_"Coppersmith's Shop", coppersmith, copper, utensils, 2, 64, 20)
copper_3    = building(_"Utensils Factory", coppersmith, copper, utensils, 3, 160, 100, 8)
brick_1     = building(_"Small Klin", potter, mud, bricks)
brick_2     = building(_"Big Klin", potter, mud, bricks, 2, 64, 20)
brick_3     = building(_"Brick Factory", potter, mud, bricks, 3, 160, 100, 8)
stable      = building(_"Stable", nil, food, horses, 2, 64, 20)
bronze_1    = building(_"Metallurgic's Shop", metallurgic, { copper, tin }, bronze)
bronze_2    = building(_"Metalworks", metallurgic, { copper, tin }, bronze, 2, 64, 20)
bronze_3    = building(_"Machine Shop", metallurgic, { copper, tin }, bronze, 3, 160, 100, 8)
scribe_1    = building(_"Tablet House", scribe, nil, scrolls)
scribe_2    = building(_"Gymnasium", scribe, nil, scrolls, 2, 64, 20)
scribe_3    = building(_"Academy", scribe, nil, scrolls, 3, 160, 100, 8)
temple_1    = building(_"Worship Yard", priest, nil, prayers, 1, 80)
temple_2    = building(_"Shrine", priest, nil, prayers, 2, 64, 20)
temple_3    = building(_"Temple", priest, nil, prayers, 3, 160, 100, 8)
embassy     = building(_"Embassy", nil, nil, nil, 3, 160, 100, 8)
docks_1     = building(_"Docks", nil, nil, nil, 1, 52)
docks_2     = building(_"Drydock", nil, nil, nil, 1, 80, 50, 4)
docks_3     = building(_"Shipyard", nil, nil, nil, 1, 240, 100, 8)
wall_1      = building(_"Wooden Wall", nil, nil, nil, 1, 64)
wall_2      = building(_"Stone Wall", nil, nil, nil, 2, 120, 100)
wall_3      = building(_"Masonry Wall", nil, nil, nil, 3, 240, 200)
library     = building(_"Library", nil, nil, nil, 0, 120, 20)
oracle      = building(_"Oracle", nil, nil, nil, 0, 120, 20)
warehouse_1 = building(_"Warehouse", nil, nil, nil, 2, 80)
warehouse_2 = building(_"Big Warehouse", nil, nil, nil, 3, 120, 20)
palace      = building(_"Palace", nil, nil, nil, 0, 240, 200)
monument    = building(_"Monument", nil, nil, nil, 0, 320, 300)
