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
terrains = {}
local function terrain(name, production, switch_status)
   local function good_production(p)
      if not p then return {} end
      local pp = {}
      for i,v in ipairs(p) do pp[goods[i] ] = v end
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

tundra = terrain(_'Tundra', { 1 })
