class Tile

  attr_reader :x, :y
  
  # Terrain of this tile
  attr_accessor :terrain
  
  # City construncted on this tile
  attr_accessor :city

  # who is working on this tile
  attr_reader :worker

  # to what city this tile belongs to
  attr_accessor :belongs_to

  # Create a new city
  def initialize(game, x, y)
    @game = game
    @x, @y = x, y
    @terrain = Prairie
    @city = nil
    @worker = nil
    @belongs_to = nil
  end

  # Returns a Array containing the units in this tile
  def units
    u = []
    @game.nations.each do |nation|
      nation.units.select{ |_u| not _u.working_on }.each do |unit|
        u << unit if unit.x == @x and unit.y == @y
      end
      return u if u.length > 0
    end
    return u
  end

  # Move cost to enter this tile
  def cost_to_enter(unit)
    @terrain.cost_to_enter # TODO - rivers, etc
  end

  # Can a city be built on this tile?
  def can_build_city?
    return true # TODO
  end
  
  # Assing a worker (for producing raw goods) to this tile.
  def worker=(unit)
    @worker.abandon_job! if @worker # original worker leaves tile
    if unit # new worker abandons old job
      unit.abandon_job!
      unit.working_on = self
      unit.job = @terrain.suggested_job
    end
    @worker = unit # unit assigned to tile
  end

  # Return the production of this tile.
  def production(unit=nil)
    prod = {}
    Good.all.select{ |g| g.raw }.each do |good|
      n = @terrain.production[good] # TODO - rivers, etc
      n *= 2 if unit and unit.job and unit.job.good == good
    end
  end

end
