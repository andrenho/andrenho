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
#
DIRECTIONS = {
  1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
  4 => [-1, 0],               6 => [ 1, 0],
  7 => [-1,-1], 8 => [ 0,-1], 9 => [ 1,-1]
}
DIRECTIONS_C = {
  1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
  4 => [-1, 0], 5 => [ 0, 0], 6 => [ 1, 0],
  7 => [-1,-1], 8 => [ 0,-1], 9 => [ 1,-1]
}

#
# Goods
# 
class Good < Static

  @@all = []

  attr_reader :name, :raw, :mined, :can_buy, :initial_prices, :raw_material, :all

  def initialize(name, raw, mined, can_buy, initial_prices=nil, raw_material=[])
    super()
    @name, @raw, @mined, @can_buy, @initial_prices, @raw_material = name, raw, mined, can_buy, initial_prices, raw_material
    @@all << self
  end

  def Good.all; @@all; end

end

Food =      Good.new(_('Food'),      true,  false, true, [  1, 8 ])
Cotton =    Good.new(_('Cotton'),    true,  false, true, [  4, 6 ])
Barley =    Good.new(_('Barley'),    true,  false, true, [  4, 6 ])
Olives =    Good.new(_('Olives'),    true,  false, true, [  6, 8 ])
Wood =      Good.new(_('Wood'),      true,  true,  true, [  1, 6 ])
Copper =    Good.new(_('Copper'),    true,  true,  true, [  5, 8 ])
Mud =       Good.new(_('Mud'),       true,  true,  true, [  1, 5 ])
Tin =       Good.new(_('Tin'),       true,  true,  true, [  7, 9 ])
Gold =      Good.new(_('Gold'),      true,  true,  [ 15,16 ])
Clothes =   Good.new(_('Clothes'),   false, false, true, [ 12,13 ], [ Cotton ])
Beer =      Good.new(_('Beer'),      false, false, true, [ 10,11 ], [ Barley ])
Olive_oil = Good.new(_('Olive Oil'), false, false, true, [ 12,13 ], [ Olives ])
Timber    = Good.new(_('Timber'),    false, false, true, [ 10,11 ], [ Wood ])
Utensils =  Good.new(_('Utensils'),  false, false, true, [ 12,13 ], [ Copper ])
Bricks =    Good.new(_('Bricks'),    false, false, true, [  1, 8 ], [ Mud ])
Riding =    Good.new(_('Animals'),   false, false, true, [  5, 8 ])
Bronze =    Good.new(_('Bronze'),    false, false, true, [  9,10 ], [ Copper, Tin ])
Weapons =   Good.new(_('Weapons'),   false, false, true, [  6, 7 ], [ Wood, Bronze ])
Scrolls =   Good.new(_('Scrolls'),   false, false, false)
Prayers =   Good.new(_('Prayers'),   false, false, false)


#
# Military classes
#
class Military < Static

  @@all = []

  attr_reader :name, :ship, :work_in_colony, :moves, :attack, :defense, :cargo

  def initialize(name, ship, work_in_colony, moves, attack, defense, cargo)
    super()
    @name, @ship, @work_in_colony, @moves, @attack, @defense, @cargo = name, ship, work_in_colony, moves, attack, defense, cargo
    @@all << self
  end

end

Peasant         = Military.new(_('Peasant'),                 false, true,  1, 0, 1, 0)
Colonist        = Military.new(_('Colonist'),                false, true,  1, 0, 1, 0)
Caravan         = Military.new(_('Caravan'),                 false, false, 2, 0, 1, 2)
Warrior         = Military.new(_('Warrior'),                 false, true,  1, 2, 2, 0)
Nomad           = Military.new(_('Nomad'),                   false, true,  4, 1, 1, 0)
Chariot         = Military.new(_('Chariot'),                 false, true,  4, 3, 3, 0)
Pikeman         = Military.new(_('Pikeman'),                 false, true,  1, 3, 3, 0)
Mtd_pikeman     = Military.new(_('Mounted Pikeman'),         false, true,  4, 4, 4, 0)
Armored_warrior = Military.new(_('Armed Warrior'),           false, true,  1, 4, 4, 0)
Cataphract      = Military.new(_('Cataphract'),              false, false, 4, 5, 5, 0)
Catapult        = Military.new(_('Catapult'),                false, false, 1, 7, 5, 0)

Clan_member     = Military.new(_('Clan Member'),             false, true,  1, 1, 1, 0)
Clan_armed      = Military.new(_('Armed Clan Member'),       false, true,  1, 2, 2, 0)
Clan_mounted    = Military.new(_('Clan Member Rider'),       false, true,  4, 2, 2, 0)
Clan_mtd_armed  = Military.new(_('Armed Clan Member Armed'), false, true,  4, 3, 3, 0)

Elite_soldier   = Military.new(_('Elite Soldier'),           false, true,  1, 4, 4, 0)
Elite_chariot   = Military.new(_('Elite Chariot'),           false, true,  4, 5, 5, 0)
Faraoh_soldier  = Military.new(_("Faraoh's Guard"),          false, true,  1, 5, 5, 0)
Faraoh_chariot  = Military.new(_("Faraoh's Chariot Guard"),  false, true,  4, 6, 6, 0)

Penteconter     = Military.new(_('Penteconter'),             true,  false, 4, 0, 2, 2)
Merchantman     = Military.new(_('Merchantman'),             true,  false, 6, 0, 6, 5)
Monoreme        = Military.new(_('Monoreme'),                true,  false, 4, 1, 3, 0)
Bireme          = Military.new(_('Bireme'),                  true,  false, 5, 3, 5, 0)
Trireme         = Military.new(_('Trireme'),                 true,  false, 6, 4, 6, 0)
Galley          = Military.new(_('Galley'),                  true,  false, 5, 7, 8, 6)
Pirate_ship     = Military.new(_('Pirate Ship'),             true,  false, 8, 4, 8, 2)

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
Olive_pl     = Job.new(_('Olive Planter'), true, Olives)
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

  def preferred_good
    if @suggested_job == Lumberjack
      @switch_status.suggested_job.good
    elsif self == Plains
      Cotton
    else
      @suggested_job.good
    end
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
#Sea      = Terrain.new(_('Sea'),             2, 1, 0, [ 3, 0, 0, 0, 0, 0, 0, 0, 0 ], Fisherman)
Ocean    = Terrain.new(_('Ocean'),           1, 1, 0, [ 3, 0, 0, 0, 0, 0, 0, 0, 0 ], Fisherman)
Hills    = Terrain.new(_('Hills'),           4, 2, 4, [ 1, 0, 0, 0, 0, 3, 0, 3, 0 ], Tin_miner)
Mountain = Terrain.new(_('Mountains'),       3, 3, 6, [ 0, 0, 0, 0, 0, 3, 0, 3, 1 ], Copper_miner)
# *Ovl: Overlap for terrains.


#
# Buildings
#
class BuildingType < Static

  @@all = []

  attr_reader :name, :prerequisite, :max_units, :job, :raw_good, :good, :multiplier, :cost, :copper, 
              :min_colony, :storage

  def initialize(name, prerequisite, max_units, job, raw_good, good, multiplier=1, cost=0, copper=0, 
                 min_colony=0, storage=0)
    super()
    @name, @prerequisite, @max_units, @job, @raw_good, @good, @multiplier, @cost, @copper, @min_colony, @storage = name, prerequisite, max_units, job, raw_good, good, multiplier, cost, copper, min_colony, storage
    if @job
      @job.building = self
      @job.raw_good = raw_good
      @job.good = good
    end
    @@all << self
  end

  def BuildingType.all; @@all; end

  def create_building(city)
    if @storage > 0
      return Warehouse.new(city, self)
    else
      return Building.new(city, self)
    end
  end

end

Weaver_1    = BuildingType.new(_("Weaver's House"), nil, 2, Weaver, Cotton, Clothes)
Weaver_2    = BuildingType.new(_("Weaver's Shop"), Weaver_1, 3, Weaver, Cotton, Clothes, 2, 64, 20)
Weaver_3    = BuildingType.new(_("Cloth Mill"), 3, Weaver_2, Weaver, Cotton, Clothes, 3, 160, 100, 8)
Brewer_1    = BuildingType.new(_("Brewer's House"), nil, 2, Brewer, Barley, Beer)
Brewer_2    = BuildingType.new(_("Brewer's Shop"), Brewer_1, 3, Brewer, Barley, Beer, 2, 64, 20)
Brewer_3    = BuildingType.new(_("Beer Mill"), Brewer_2, 3, Brewer, Barley, Beer, 3, 160, 100, 8)
Oil_1       = BuildingType.new(_("Small Oil Press"), nil, 2, Oil_presser, Olives, Olive_oil)
Oil_2       = BuildingType.new(_("Big Oil Press"), Oil_1, 3, Oil_presser, Olives, Olive_oil, 2, 64, 20)
Oil_3       = BuildingType.new(_("Olive Oil Mill"), Oil_2, 3, Oil_presser, Olives, Olive_oil, 3, 160, 100, 8)
Carpenter_1 = BuildingType.new(_("Carpenter's House"), nil, 2, Carpenter, Wood, Timber)
Carpenter_2 = BuildingType.new(_("Carpenter's Shop"), Carpenter_1, 3, Carpenter, Wood, Timber, 2, 64, 20)
Carpenter_3 = BuildingType.new(_("Lumber Mill"), Carpenter_2, 3, Carpenter, Wood, Timber, 3, 160, 100, 8)
Copper_1    = BuildingType.new(_("Coppersmith's House"), nil, 2, Coppersmith, Copper, Utensils)
Copper_2    = BuildingType.new(_("Coppersmith's Shop"), Copper_1, 3, Coppersmith, Copper, Utensils, 2, 64, 20)
Copper_3    = BuildingType.new(_("Utensils Factory"), Copper_2, 3, Coppersmith, Copper, Utensils, 3, 160, 100, 8)
Brick_1     = BuildingType.new(_("Small Klin"), nil, 2, Potter, Mud, Bricks)
Brick_2     = BuildingType.new(_("Big Klin"), Brick_1, 3, Potter, Mud, Bricks, 2, 64, 20)
Brick_3     = BuildingType.new(_("Brick Factory"), Brick_2, 3, Potter, Mud, Bricks, 3, 160, 100, 8)
Stable      = BuildingType.new(_("Stable"), nil, 0, nil, Food, Riding, 2, 64, 20)
Bronze_1    = BuildingType.new(_("Metallurgic's Shop"), nil, 2, Metallurgic, [ Copper, Tin ], Bronze)
Bronze_2    = BuildingType.new(_("Metalworks"), Bronze_1, 3, Metallurgic, [ Copper, Tin ], Bronze, 2, 64, 20)
Bronze_3    = BuildingType.new(_("Machine Shop"), Bronze_2, 3, Metallurgic, [ Copper, Tin ], Bronze, 3, 160, 100, 8)
Scribe_1    = BuildingType.new(_("Tablet House"), nil, 2, Scribe, nil, Scrolls)
Scribe_2    = BuildingType.new(_("Gymnasium"), Scribe_1, 3, Scribe, nil, Scrolls, 2, 64, 20)
Scribe_3    = BuildingType.new(_("Academy"), Scribe_2, 3, Scribe, nil, Scrolls, 3, 160, 100, 8)
Temple_1    = BuildingType.new(_("Worship Yard"), nil, 1, Priest, nil, Prayers, 1, 80)
Temple_2    = BuildingType.new(_("Shrine"), Temple_1, 3, Priest, nil, Prayers, 2, 64, 20)
Temple_3    = BuildingType.new(_("Temple"), Temple_2, 3, Priest, nil, Prayers, 3, 160, 100, 8)
Embassy     = BuildingType.new(_("Embassy"), nil, 0, nil, nil, nil, 3, 160, 100, 8)
Docks_1     = BuildingType.new(_("Docks"), nil, 0, nil, nil, nil, 1, 52)
Docks_2     = BuildingType.new(_("Drydock"), Docks_1, 0, nil, nil, nil, 1, 80, 50, 4)
Docks_3     = BuildingType.new(_("Shipyard"), Docks_2, 0, nil, nil, nil, 1, 240, 100, 8)
Wall_1      = BuildingType.new(_("Wooden Wall"), nil, 0, nil, nil, nil, 1, 64)
Wall_2      = BuildingType.new(_("Stone Wall"), Wall_1, 0, nil, nil, nil, 2, 120, 100)
Wall_3      = BuildingType.new(_("Masonry Wall"), Wall_2, 0, nil, nil, nil, 3, 240, 200)
Library     = BuildingType.new(_("Library"), nil, 0, nil, nil, nil, 0, 120, 20)
Oracle      = BuildingType.new(_("Oracle"), Library, 0, nil, nil, nil, 0, 120, 20)
Storage     = BuildingType.new(_("Storage Area"), nil, 0, nil, nil, nil, nil, 1, 0, 0, 100)
Warehouse_1 = BuildingType.new(_("Warehouse"), Storage, 0, nil, nil, nil, 2, 80, 0, 0, 200)
Warehouse_2 = BuildingType.new(_("Big Warehouse"), Warehouse_1, 0, nil, nil, nil, 3, 120, 20, 0, 300)
Palace      = BuildingType.new(_("Palace"), nil, 0, nil, nil, nil, 0, 240, 200)
Monument    = BuildingType.new(_("Monument"), nil, 0, nil, nil, nil, 0, 320, 300)

InitialBuildings = [ Weaver_1, Brewer_1, Oil_1, Carpenter_1, Copper_1, Brick_1, Bronze_1, Storage ]

# Nation
Israel = nil
