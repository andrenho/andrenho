class Tile

  Messages = {
    :produce => _('What should the %s work on?'),
  }

  attr_reader :x, :y
  attr_reader :known
  
  # Terrain of this tile
  attr_accessor :terrain
  
  # City construncted on this tile
  attr_accessor :city

  # who is working on this tile
  attr_reader :worker

  # to what city this tile belongs to
  attr_accessor :belongs_to

  # Create a new tile
  def initialize(game, x, y)
    @game = game
    @x, @y = x, y
    @terrain = Prairie
    @city = nil
    @worker = nil
    @belongs_to = nil
    @known = {}
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
    # TODO - assertions
    if @worker
      w = @worker
      @worker = nil
      w.abandon_job!  # original worker leaves tile
    end
    if unit # new worker abandons old job
      unit.abandon_job!
      unit.working_on = self
      unit.job = @terrain.suggested_job
    end
    @worker = unit # unit assigned to tile
  end

  # Return the current production of this tile in the format [Good, amount].
  def production
    if @city
      pr_food = abs_productivity(Food)
      pr_other = abs_productivity(@terrain.preferred_good)
      return [[Food, (pr_food*3/2).to_i], [@terrain.preferred_good, (pr_other*3/2).to_i]]
    elsif @worker
      pr = abs_productivity(@worker.job.good)
      pr *= 2 if @worker.skill and @worker.skill.good == job.good
      return [[@worker.job.good, pr]]
    else
      []
    end
  end

  # Return what would be the production of this tile, 
  # if the unit were working on it.
  def productivity_job(unit, job)
    n = self.abs_productivity(job.good) # TODO - rivers, etc
    n *= 2 if unit.skill and unit.skill.good == job.good
    n
  end

  # Return the absolute production of this tile for a given good.
  def abs_productivity(good)
    return @terrain.production[good]
  end

end
