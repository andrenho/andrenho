require 'landunit'

# 
# Represents a unit that can do work.
#
class WorkerUnit < LandUnit

  # Unit's job.
  attr_accessor :job

  # Tile or building where the unit is working (nil if not working).
  attr_accessor :working_on

  # Skills that the unit has.
  attr_reader :skills

  #
  # Create a new worker unit.
  #
  def initialize(game, nation, military, x, y)
    super(game, nation, military, x, y)
    @skills = []
    @experience = {} # a hash containing the number of rounds that a unit 
                     # worked in a job
    Job.all.each { |j| @experience[j] = 0 }
  end

  #
  # Returns if the unit can build a city.
  #
  def can_build_city?
    true # TODO
  end

  # 
  # Build a city.
  # 
  def build_city(name)
    $log.debug "Building a new city called #{name}."
    city = CityPlayer.new(@game, @nation, name, @x, @y)
    nation.cities << city
    city
  end

  # 
  # Makes the unit abandon its job.
  #
  def abandon_job!
    if @working_on.is_a? Building
      @working_on.workers.delete(self)
    elsif @working_on.is_a? Tile
      @working_on.worker = nil
    end
    $log.debug 'Unit abandoned job.' if @working_on
    @working_on = nil
  end

  # 
  # Returns true if the unit is working.
  #
  def worker?
    @working_on != nil
  end

  #
  # Do what needs to be done at the end of the round (gets more experienced).
  #
  def end_round
    super
    if self.worker?
      @experience[@job] += 1
      if not @skills.include? @job and @experience[@job] > 100
        @skills << @job
        if @working_on.is_a? Building
          city = @working_on.city
        elsif @working_on.is_a? Tile
          city = @working_on.belongs_to
        end
        $ui.messages << _('In %s, a peasant has become skilled as a %s.') % [city.name, @job.name]
      end
    end
  end

  #
  # Called before the unit dies.
  #
  def prepare_to_die!
    abandon_job!
  end

end 
