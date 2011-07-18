require 'i18n'

#
# Goods
# 
class Good

  @@all = []

  attr_reader :name, :can_buy, :initial_prices, :raw_material, :all

  def initialize(name, can_buy, initial_prices=nil, raw_material=nil)
    @name, @can_buy, @initial_prices, @raw_material = name, can_buy, initial_prices, raw_material
    @@all << self
  end

  def Good.all; @@all; end

end

Food =      Good.new(_('Food'),      true, [  1, 8 ])
Cotton =    Good.new(_('Cotton'),    true, [  4, 6 ])
Barley =    Good.new(_('Barley'),    true, [  4, 6 ])
Olives =    Good.new(_('Olives'),    true, [  6, 8 ])
Wood =      Good.new(_('Wood'),      true, [  1, 6 ])
Copper =    Good.new(_('Copper'),    true, [  5, 8 ])
Mud =       Good.new(_('Mud'),       true, [  1, 5 ])
Tin =       Good.new(_('Tin'),       true, [  7, 9 ])
Gold =      Good.new(_('Gold'),      true, [ 15,16 ])
Clothes =   Good.new(_('Clothes'),   true, [ 12,13 ], [ Cotton ])
Beer =      Good.new(_('Beer'),      true, [ 10,11 ], [ Barley ])
Olive_oil = Good.new(_('Olive Oil'), true, [ 12,13 ], [ Olives ])
Furniture = Good.new(_('Furniture'), true, [ 10,11 ], [ Wood ])
Utensils =  Good.new(_('Utensils'),  true, [ 12,13 ], [ Copper ])
Bricks =    Good.new(_('Bricks'),    true, [  1, 8 ], [ Mud ])
Riding =    Good.new(_('Animals'),   true, [  5, 8 ])
Bronze =    Good.new(_('Bronze'),    true, [  9,10 ], [ Copper, Tin ])
Weapons =   Good.new(_('Weapons'),   true, [  6, 7 ], [ Wood, Bronze ])
Scrolls =   Good.new(_('Scrolls'),   false)
Prayers =   Good.new(_('Prayers'),   false)

# 
# Terrains
#
class Terrain

  @@all = []

  attr_reader :all, :name, :ovl, :cost_to_enter, :defensive_bonus, :production
  attr_accessor :switch_status

  def initialize(name, ovl, cost_to_enter, defensive_bonus, production, 
                 switch_status=nil)
    @name, @ovl, @cost_to_enter, @defensive_bonus, @switch_status =
      name, ovl, cost_to_enter, defensive_bonus, switch_status
    @production = {}
    i = 0
    Good.all.each do |good|
      @production[good] = production[i]
      i += 1
    end
    @switch_status.switch_status = self if @switch_status
    @@all << self
  end

end

#                      Name                    MoveCost       Barley      Mud
#                                           Ovl*   Defence       Olives      Tin
#                                                       Food        Wood        Gold
#                                                          Cotton      Copper
Tundra   = Terrain.new(_('Tundra'),          1, 0, 0, [ 2, 0, 0, 0, 0, 2, 2, 1, 0 ])
Desert   = Terrain.new(_('Desert'),         13, 1, 0, [ 1, 0, 0, 2, 0, 1, 3, 2, 0 ])
Plains   = Terrain.new(_('Planis'),         14, 1, 0, [ 4, 2, 1, 0, 0, 1, 1, 0, 0 ])
Prairie  = Terrain.new(_('Prairie'),        15, 1, 0, [ 3, 3, 0, 0, 0, 0, 0, 0, 0 ])
Steppe   = Terrain.new(_('Steppe'),         16, 1, 0, [ 2, 2, 3, 0, 0, 0, 0, 0, 0 ])
Marsh    = Terrain.new(_('Marsh'),          17, 2, 1, [ 3, 1, 2, 0, 0, 2, 4, 2, 0 ])

Boreal_f = Terrain.new(_('Boreal forest'),   6, 2, 2, [ 1, 0, 0, 0, 2, 1, 1, 1, 0 ], Tundra)
Scrub    = Terrain.new(_('Scrubland'),       7, 1, 2, [ 1, 0, 0, 4, 1, 1, 2, 1, 0 ], Desert)
Mixed_f  = Terrain.new(_('Mixed forest'),    8, 2, 2, [ 2, 1, 0, 0, 3, 0, 1, 0, 0 ], Plains)
Savannah = Terrain.new(_('Savannah'),        9, 1, 1, [ 1, 1, 0, 0, 2, 0, 1, 0, 0 ], Prairie)
Woodland = Terrain.new(_('Woodland'),       10, 2, 2, [ 1, 0, 1, 0, 2, 0, 1, 0, 0 ], Steppe)
Swamp    = Terrain.new(_('Swamp'),          11, 3, 3, [ 2, 0, 0, 0, 1, 1, 3, 2, 0 ], Marsh)

Arctic   = Terrain.new(_('Arctic'),          5, 2, 0, [ 0, 0, 0, 0, 0, 1, 0, 1, 1 ])
Sea      = Terrain.new(_('Sea'),             2, 1, 0, [ 3, 0, 0, 0, 0, 0, 0, 0, 0 ])
Ocean    = Terrain.new(_('Ocean'),           1, 1, 0, [ 3, 0, 0, 0, 0, 0, 0, 0, 0 ])
Hills    = Terrain.new(_('Hills'),           4, 2, 4, [ 1, 0, 0, 0, 0, 3, 0, 3, 0 ])
Mountain = Terrain.new(_('Mountains'),       3, 3, 6, [ 0, 0, 0, 0, 0, 3, 0, 3, 1 ])
# *Ovl: Overlap for terrains.


#
# Military classes
#
class Military

  @@all = []

  attr_reader :name, :ship, :moves, :attack, :defense, :cargo

  def initialize(name, ship, moves, attack, defense, cargo)
    @name, @ship, @moves, @attack, @defense, @cargo = name, ship, moves, attack, defense, cargo
    @@all << self
  end

end

Peasant         = Military.new(_('Peasant'),                 false, 1, 0, 1, 0)
Colonist        = Military.new(_('Colonist'),                false, 1, 0, 1, 0)
Warrior         = Military.new(_('Warrior'),                 false, 1, 2, 2, 0)
Nomad           = Military.new(_('Nomad'),                   false, 4, 1, 1, 0)
Chariot         = Military.new(_('Chariot'),                 false, 4, 3, 3, 0)
Pikeman         = Military.new(_('Pikeman'),                 false, 1, 3, 3, 0)
Mtd_pikeman     = Military.new(_('Mounted Pikeman'),         false, 4, 4, 4, 0)
Armored_warrior = Military.new(_('Armed Warrior'),           false, 1, 4, 4, 0)
Cataphract      = Military.new(_('Cataphract'),              false, 4, 5, 5, 0)
Catapult        = Military.new(_('Catapult'),                false, 1, 7, 5, 0)

Clan_member     = Military.new(_('Clan Member'),             false, 1, 1, 1, 0)
Clan_armed      = Military.new(_('Armed Clan Member'),       false, 1, 2, 2, 0)
Clan_mounted    = Military.new(_('Clan Member Rider'),       false, 4, 2, 2, 0)
Clan_mtd_armed  = Military.new(_('Armed Clan Member Armed'), false, 4, 3, 3, 0)

Elite_soldier   = Military.new(_('Elite Soldier'),           false, 1, 4, 4, 0)
Elite_chariot   = Military.new(_('Elite Chariot'),           false, 4, 5, 5, 0)
Faraoh_soldier  = Military.new(_("Faraoh's Guard"),          false, 1, 5, 5, 0)
Faraoh_chariot  = Military.new(_("Faraoh's Chariot Guard"),  false, 4, 6, 6, 0)

Penteconter     = Military.new(_('Penteconter'),             true,  4, 0, 2, 2)
Merchantman     = Military.new(_('Merchantman'),             true,  6, 0, 6, 5)
Monoreme        = Military.new(_('Monoreme'),                true,  4, 1, 3, 0)
Bireme          = Military.new(_('Bireme'),                  true,  5, 3, 5, 0)
Trireme         = Military.new(_('Trireme'),                 true,  6, 4, 6, 0)
Galley          = Military.new(_('Galley'),                  true,  5, 7, 8, 6)
Pirate_ship     = Military.new(_('Pirate Ship'),             true,  8, 4, 8, 2)


# 
# Jobs
#
class Job

  attr_reader :name
  attr_accessor :building, :raw_good, :good

  def initialize(name)
    @name = name
  end

end

Farmer       = Job.new(_('Farmer'))
Fisherman    = Job.new(_('Fisherman'))
Cotton_pl    = Job.new(_('Cotton Planter'))
Barley_pl    = Job.new(_('Barley Planter'))
Olive_pl     = Job.new(_('Olives Planter'))
Lumberjack   = Job.new(_('Lumberjack'))
Copper_miner = Job.new(_('Copper Miner'))
Mudder       = Job.new(_('Mudder'))
Tin_miner    = Job.new(_('Tin Miner'))
Prospector   = Job.new(_('Prospector'))
Weaver       = Job.new(_('Weaver'))
Brewer       = Job.new(_('Brewer'))
Oil_presser  = Job.new(_('Oil Presser'))
Carpenter    = Job.new(_('Carpenter'))
Coppersmith  = Job.new(_('Coppersmith'))
Potter       = Job.new(_('Potter'))
Metallurgic  = Job.new(_('Metallurgic'))
Weaponsmith  = Job.new(_('Weaponsmith'))
Scribe       = Job.new(_('Scribe'))
Priest       = Job.new(_('Priest'))

#
# Buildings
#
class Building

  attr_reader :name, :job, :raw_good, :good, :multiplier, :cost, :Copper, 
              :min_colony

  def initialize(name, job, raw_good, good, multiplier=1, cost=0, copper=0, 
                 min_colony=0)
    @name, @job, @raw_good, @good, @multiplier, @cost, @copper, @min_colony = 
      name, job, raw_good, good, multiplier, cost, copper, min_colony
    if @job
      @job.building = self
      @job.raw_good = raw_good
      @job.good = good
    end
  end

end

Weaver_1    = Building.new(_("Weaver's House"), Weaver, Cotton, Clothes)
Weaver_2    = Building.new(_("Weaver's Shop"), Weaver, Cotton, Clothes, 2, 64, 20)
Weaver_3    = Building.new(_("Cloth Mill"), Weaver, Cotton, Clothes, 3, 160, 100, 8)
Brewer_1    = Building.new(_("Brewer's House"), Brewer, Barley, Beer)
Brewer_2    = Building.new(_("Brewer's Shop"), Brewer, Barley, Beer, 2, 64, 20)
Brewer_3    = Building.new(_("Beer Mill"), Brewer, Barley, Beer, 3, 160, 100, 8)
Oil_1       = Building.new(_("Small Oil Press"), Oil_presser, Olives, Olive_oil)
Oil_2       = Building.new(_("Big Oil Press"), Oil_presser, Olives, Olive_oil, 2, 64, 20)
Oil_3       = Building.new(_("Olive Oil Mill"), Oil_presser, Olives, Olive_oil, 3, 160, 100, 8)
Carpenter_1 = Building.new(_("Carpenter's House"), Carpenter, Wood, Furniture)
Carpenter_2 = Building.new(_("Carpenter's Shop"), Carpenter, Wood, Furniture, 2, 64, 20)
Carpenter_3 = Building.new(_("Lumber Mill"), Carpenter, Wood, Furniture, 3, 160, 100, 8)
Copper_1    = Building.new(_("Coppersmith's House"), Coppersmith, Copper, Utensils)
Copper_2    = Building.new(_("Coppersmith's Shop"), Coppersmith, Copper, Utensils, 2, 64, 20)
Copper_3    = Building.new(_("Utensils Factory"), Coppersmith, Copper, Utensils, 3, 160, 100, 8)
Brick_1     = Building.new(_("Small Klin"), Potter, Mud, Bricks)
Brick_2     = Building.new(_("Big Klin"), Potter, Mud, Bricks, 2, 64, 20)
Brick_3     = Building.new(_("Brick Factory"), Potter, Mud, Bricks, 3, 160, 100, 8)
Stable      = Building.new(_("Stable"), nil, Food, Riding, 2, 64, 20)
Bronze_1    = Building.new(_("Metallurgic's Shop"), Metallurgic, [ Copper, Tin ], Bronze)
Bronze_2    = Building.new(_("Metalworks"), Metallurgic, [ Copper, Tin ], Bronze, 2, 64, 20)
Bronze_3    = Building.new(_("Machine Shop"), Metallurgic, [ Copper, Tin ], Bronze, 3, 160, 100, 8)
Scribe_1    = Building.new(_("Tablet House"), Scribe, nil, Scrolls)
Scribe_2    = Building.new(_("Gymnasium"), Scribe, nil, Scrolls, 2, 64, 20)
Scribe_3    = Building.new(_("Academy"), Scribe, nil, Scrolls, 3, 160, 100, 8)
Temple_1    = Building.new(_("Worship Yard"), Priest, nil, Prayers, 1, 80)
Temple_2    = Building.new(_("Shrine"), Priest, nil, Prayers, 2, 64, 20)
Temple_3    = Building.new(_("Temple"), Priest, nil, Prayers, 3, 160, 100, 8)
Embassy     = Building.new(_("Embassy"), nil, nil, nil, 3, 160, 100, 8)
Docks_1     = Building.new(_("Docks"), nil, nil, nil, 1, 52)
Docks_2     = Building.new(_("Drydock"), nil, nil, nil, 1, 80, 50, 4)
Docks_3     = Building.new(_("Shipyard"), nil, nil, nil, 1, 240, 100, 8)
Wall_1      = Building.new(_("Wooden Wall"), nil, nil, nil, 1, 64)
Wall_2      = Building.new(_("Stone Wall"), nil, nil, nil, 2, 120, 100)
Wall_3      = Building.new(_("Masonry Wall"), nil, nil, nil, 3, 240, 200)
Library     = Building.new(_("Library"), nil, nil, nil, 0, 120, 20)
Oracle      = Building.new(_("Oracle"), nil, nil, nil, 0, 120, 20)
Warehouse_1 = Building.new(_("Warehouse"), nil, nil, nil, 2, 80)
Warehouse_2 = Building.new(_("Big Warehouse"), nil, nil, nil, 3, 120, 20)
Palace      = Building.new(_("Palace"), nil, nil, nil, 0, 240, 200)
Monument    = Building.new(_("Monument"), nil, nil, nil, 0, 320, 300)
