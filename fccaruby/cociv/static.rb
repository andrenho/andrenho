require 'i18n'

class Static

  @@id = 0

  attr_reader :id

  def initialize
    @id = @@id
    @@id += 1
  end

  def inspect
    return "<##{self.class.name}:#{@name}>"
  end

  # The methods below allow that if the classes are loaded
  # twice, they remaind the same when compared or used as
  # keys in hashes. This is specially useful in marshalling
  # (serialization).

  def eql?(o)
    return false if not o.is_a? Static
    return @id == o.id
  end

  def ==(o)
    return false if not o.is_a? Static
    return @id == o.id
  end

  def hash
    @id
  end

end

# 
# Directions
DIRECTIONS = {
  1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
  4 => [-1, 0],               6 => [ 1, 0],
  7 => [-1,-1], 8 => [ 0,-1], 9 => [ 1,-1]
}

#
# Goods
# 
class Good < Static

  @@all = []

  attr_reader :name, :raw, :can_buy, :initial_prices, :raw_material, :all

  def initialize(name, raw, can_buy, initial_prices=nil, raw_material=nil)
    super()
    @name, @raw, @can_buy, @initial_prices, @raw_material = name, raw, can_buy, initial_prices, raw_material
    @@all << self
  end

  def Good.all; @@all; end

end

Food =      Good.new(_('Food'),      true,  true, [  1, 8 ])
Cotton =    Good.new(_('Cotton'),    true,  true, [  4, 6 ])
Barley =    Good.new(_('Barley'),    true,  true, [  4, 6 ])
Olives =    Good.new(_('Olives'),    true,  true, [  6, 8 ])
Wood =      Good.new(_('Wood'),      true,  true, [  1, 6 ])
Copper =    Good.new(_('Copper'),    true,  true, [  5, 8 ])
Mud =       Good.new(_('Mud'),       true,  true, [  1, 5 ])
Tin =       Good.new(_('Tin'),       true,  true, [  7, 9 ])
Gold =      Good.new(_('Gold'),      true,  true, [ 15,16 ])
Clothes =   Good.new(_('Clothes'),   false, true, [ 12,13 ], [ Cotton ])
Beer =      Good.new(_('Beer'),      false, true, [ 10,11 ], [ Barley ])
Olive_oil = Good.new(_('Olive Oil'), false, true, [ 12,13 ], [ Olives ])
Furniture = Good.new(_('Furniture'), false, true, [ 10,11 ], [ Wood ])
Utensils =  Good.new(_('Utensils'),  false, true, [ 12,13 ], [ Copper ])
Bricks =    Good.new(_('Bricks'),    false, true, [  1, 8 ], [ Mud ])
Riding =    Good.new(_('Animals'),   false, true, [  5, 8 ])
Bronze =    Good.new(_('Bronze'),    false, true, [  9,10 ], [ Copper, Tin ])
Weapons =   Good.new(_('Weapons'),   false, true, [  6, 7 ], [ Wood, Bronze ])
Scrolls =   Good.new(_('Scrolls'),   false, false)
Prayers =   Good.new(_('Prayers'),   false, false)


#
# Military classes
#
class Military < Static

  @@all = []

  attr_reader :name, :ship, :moves, :attack, :defense, :cargo

  def initialize(name, ship, moves, attack, defense, cargo)
    super()
    @name, @ship, @moves, @attack, @defense, @cargo = name, ship, moves, attack, defense, cargo
    @@all << self
  end

end

Peasant         = Military.new(_('Peasant'),                 false, 1, 0, 1, 0)
Colonist        = Military.new(_('Colonist'),                false, 1, 0, 1, 0)
Caravan         = Military.new(_('Caravan'),                 false, 2, 0, 1, 2)
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
class Job < Static

  @@all = []

  attr_reader :name, :raw
  attr_accessor :building, :raw_good, :good

  def initialize(name, raw=false, good=nil)
    super()
    @name = name
    @raw = raw
    @good = good
    @@all << self
  end

  def Job.all; @@all; end

end

Farmer       = Job.new(_('Farmer'), true, Food)
Fisherman    = Job.new(_('Fisherman'), true, Food)
Cotton_pl    = Job.new(_('Cotton Planter'), true, Cotton)
Barley_pl    = Job.new(_('Barley Planter'), true, Barley)
Olive_pl     = Job.new(_('Olives Planter'), true, Olives)
Lumberjack   = Job.new(_('Lumberjack'), true, Wood)
Copper_miner = Job.new(_('Copper Miner'), true, Copper)
Mudder       = Job.new(_('Mudder'), true, Mud)
Tin_miner    = Job.new(_('Tin Miner'), true, Tin)
Prospector   = Job.new(_('Prospector'), true, Gold)
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
# Terrains
#
class Terrain < Static

  @@all = []

  attr_reader :all, :name, :ovl, :cost_to_enter, :defensive_bonus, :production, :suggested_job
  attr_accessor :switch_status

  def initialize(name, ovl, cost_to_enter, defensive_bonus, production, 
                 suggested_job, switch_status=nil)
    super()
    @name, @ovl, @cost_to_enter, @defensive_bonus, @switch_status, @suggested_job =
      name, ovl, cost_to_enter, defensive_bonus, switch_status, suggested_job
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
Tundra   = Terrain.new(_('Tundra'),          1, 0, 0, [ 2, 0, 0, 0, 0, 2, 2, 1, 0 ], Copper_miner)
Desert   = Terrain.new(_('Desert'),         13, 1, 0, [ 1, 0, 0, 2, 0, 1, 3, 2, 0 ], Mudder)
Plains   = Terrain.new(_('Planis'),         14, 1, 0, [ 4, 2, 1, 0, 0, 1, 1, 0, 0 ], Farmer)
Prairie  = Terrain.new(_('Prairie'),        15, 1, 0, [ 3, 3, 0, 0, 0, 0, 0, 0, 0 ], Cotton_pl)
Steppe   = Terrain.new(_('Steppe'),         16, 1, 0, [ 2, 2, 3, 0, 0, 0, 0, 0, 0 ], Barley_pl)
Marsh    = Terrain.new(_('Marsh'),          17, 2, 1, [ 3, 1, 2, 0, 0, 2, 4, 2, 0 ], Mudder)

Boreal_f = Terrain.new(_('Boreal forest'),   6, 2, 2, [ 1, 0, 0, 0, 2, 1, 1, 1, 0 ], Lumberjack, Tundra)
Scrub    = Terrain.new(_('Scrubland'),       7, 1, 2, [ 1, 0, 0, 4, 1, 1, 2, 1, 0 ], Olive_pl, Desert)
Mixed_f  = Terrain.new(_('Mixed forest'),    8, 2, 2, [ 2, 1, 0, 0, 3, 0, 1, 0, 0 ], Lumberjack, Plains)
Savannah = Terrain.new(_('Savannah'),        9, 1, 1, [ 1, 1, 0, 0, 2, 0, 1, 0, 0 ], Lumberjack, Prairie)
Woodland = Terrain.new(_('Woodland'),       10, 2, 2, [ 1, 0, 1, 0, 2, 0, 1, 0, 0 ], Lumberjack, Steppe)
Swamp    = Terrain.new(_('Swamp'),          11, 3, 3, [ 2, 0, 0, 0, 1, 1, 3, 2, 0 ], Mudder, Marsh)

Arctic   = Terrain.new(_('Arctic'),          5, 2, 0, [ 0, 0, 0, 0, 0, 1, 0, 1, 1 ], Prospector)
Sea      = Terrain.new(_('Sea'),             2, 1, 0, [ 3, 0, 0, 0, 0, 0, 0, 0, 0 ], Fisherman)
Ocean    = Terrain.new(_('Ocean'),           1, 1, 0, [ 3, 0, 0, 0, 0, 0, 0, 0, 0 ], Fisherman)
Hills    = Terrain.new(_('Hills'),           4, 2, 4, [ 1, 0, 0, 0, 0, 3, 0, 3, 0 ], Tin_miner)
Mountain = Terrain.new(_('Mountains'),       3, 3, 6, [ 0, 0, 0, 0, 0, 3, 0, 3, 1 ], Copper_miner)
# *Ovl: Overlap for terrains.


#
# Buildings
#
class BuildingType < Static

  @@all = []

  attr_reader :name, :max_units, :job, :raw_good, :good, :multiplier, :cost, :Copper, 
              :min_colony

  def initialize(name, max_units, job, raw_good, good, multiplier=1, cost=0, copper=0, 
                 min_colony=0)
    super()
    @name, @max_units, @job, @raw_good, @good, @multiplier, @cost, @copper, @min_colony = 
      name, max_units, job, raw_good, good, multiplier, cost, copper, min_colony
    if @job
      @job.building = self
      @job.raw_good = raw_good
      @job.good = good
    end
    @@all << self
  end

  def BuildingType.all; @@all; end

end

Weaver_1    = BuildingType.new(_("Weaver's House"), 2, Weaver, Cotton, Clothes)
Weaver_2    = BuildingType.new(_("Weaver's Shop"), 3, Weaver, Cotton, Clothes, 2, 64, 20)
Weaver_3    = BuildingType.new(_("Cloth Mill"), 3, Weaver, Cotton, Clothes, 3, 160, 100, 8)
Brewer_1    = BuildingType.new(_("Brewer's House"), 2, Brewer, Barley, Beer)
Brewer_2    = BuildingType.new(_("Brewer's Shop"), 3, Brewer, Barley, Beer, 2, 64, 20)
Brewer_3    = BuildingType.new(_("Beer Mill"), 3, Brewer, Barley, Beer, 3, 160, 100, 8)
Oil_1       = BuildingType.new(_("Small Oil Press"), 2, Oil_presser, Olives, Olive_oil)
Oil_2       = BuildingType.new(_("Big Oil Press"), 3, Oil_presser, Olives, Olive_oil, 2, 64, 20)
Oil_3       = BuildingType.new(_("Olive Oil Mill"), 3, Oil_presser, Olives, Olive_oil, 3, 160, 100, 8)
Carpenter_1 = BuildingType.new(_("Carpenter's House"), 2, Carpenter, Wood, Furniture)
Carpenter_2 = BuildingType.new(_("Carpenter's Shop"), 3, Carpenter, Wood, Furniture, 2, 64, 20)
Carpenter_3 = BuildingType.new(_("Lumber Mill"), 3, Carpenter, Wood, Furniture, 3, 160, 100, 8)
Copper_1    = BuildingType.new(_("Coppersmith's House"), 2, Coppersmith, Copper, Utensils)
Copper_2    = BuildingType.new(_("Coppersmith's Shop"), 3, Coppersmith, Copper, Utensils, 2, 64, 20)
Copper_3    = BuildingType.new(_("Utensils Factory"), 3, Coppersmith, Copper, Utensils, 3, 160, 100, 8)
Brick_1     = BuildingType.new(_("Small Klin"), 2, Potter, Mud, Bricks)
Brick_2     = BuildingType.new(_("Big Klin"), 3, Potter, Mud, Bricks, 2, 64, 20)
Brick_3     = BuildingType.new(_("Brick Factory"), 3, Potter, Mud, Bricks, 3, 160, 100, 8)
Stable      = BuildingType.new(_("Stable"), 0, nil, Food, Riding, 2, 64, 20)
Bronze_1    = BuildingType.new(_("Metallurgic's Shop"), 2, Metallurgic, [ Copper, Tin ], Bronze)
Bronze_2    = BuildingType.new(_("Metalworks"), 3, Metallurgic, [ Copper, Tin ], Bronze, 2, 64, 20)
Bronze_3    = BuildingType.new(_("Machine Shop"), 3, Metallurgic, [ Copper, Tin ], Bronze, 3, 160, 100, 8)
Scribe_1    = BuildingType.new(_("Tablet House"), 2, Scribe, nil, Scrolls)
Scribe_2    = BuildingType.new(_("Gymnasium"), 3, Scribe, nil, Scrolls, 2, 64, 20)
Scribe_3    = BuildingType.new(_("Academy"), 3, Scribe, nil, Scrolls, 3, 160, 100, 8)
Temple_1    = BuildingType.new(_("Worship Yard"), 1, Priest, nil, Prayers, 1, 80)
Temple_2    = BuildingType.new(_("Shrine"), 3, Priest, nil, Prayers, 2, 64, 20)
Temple_3    = BuildingType.new(_("Temple"), 3, Priest, nil, Prayers, 3, 160, 100, 8)
Embassy     = BuildingType.new(_("Embassy"), 0, nil, nil, nil, 3, 160, 100, 8)
Docks_1     = BuildingType.new(_("Docks"), 0, nil, nil, nil, 1, 52)
Docks_2     = BuildingType.new(_("Drydock"), 0, nil, nil, nil, 1, 80, 50, 4)
Docks_3     = BuildingType.new(_("Shipyard"), 0, nil, nil, nil, 1, 240, 100, 8)
Wall_1      = BuildingType.new(_("Wooden Wall"), 0, nil, nil, nil, 1, 64)
Wall_2      = BuildingType.new(_("Stone Wall"), 0, nil, nil, nil, 2, 120, 100)
Wall_3      = BuildingType.new(_("Masonry Wall"), 0, nil, nil, nil, 3, 240, 200)
Library     = BuildingType.new(_("Library"), 0, nil, nil, nil, 0, 120, 20)
Oracle      = BuildingType.new(_("Oracle"), 0, nil, nil, nil, 0, 120, 20)
Warehouse_1 = BuildingType.new(_("Warehouse"), 0, nil, nil, nil, 2, 80)
Warehouse_2 = BuildingType.new(_("Big Warehouse"), 0, nil, nil, nil, 3, 120, 20)
Palace      = BuildingType.new(_("Palace"), 0, nil, nil, nil, 0, 240, 200)
Monument    = BuildingType.new(_("Monument"), 0, nil, nil, nil, 0, 320, 300)

InitialBuildings = [ Weaver_1, Brewer_1, Oil_1, Carpenter_1, Copper_1, Brick_1, Bronze_1 ]

# Nation
Israel = nil
