require 'landunit'

class WorkerUnit < LandUnit

  attr_accessor :job
  attr_accessor :working_on
  attr_reader :skills

  def initialize(game, nation, military, x, y)
    super(game, nation, military, x, y)
    @skills = []
    @experience = {} # a hash containing the number of rounds that a unit 
                     # worked in a job
    Job.all.each { |j| @experience[j] = 0 }
  end

  def can_build_city?
    true # TODO
  end

  def build_city(name)
    $log.debug "Building a new city called #{name}."
    city = CityPlayer.new(@game, @nation, name, @x, @y)
    nation.cities << city
    city
  end

  def abandon_job!
    if @working_on.is_a? Building
      @working_on.workers.delete(self)
    elsif @working_on.is_a? Tile
      @working_on.worker = nil
    end
    $log.debug 'Unit abandoned job.' if @working_on
    @working_on = nil
  end

  def worker?
    @working_on != nil
  end

  def end_round
    super
    if self.worker?
      @experience[@job] += 1
      if not @skills.include? @job and @experience[@job] > 100 and rand(50) == 0
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

end 
