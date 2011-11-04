# Each one of the buildings in a city.
class Building

  # BuildingType
  attr_reader :type

  # Array of people working on this building
  attr_reader :workers

  attr_reader :city

  # Create a new building
  def initialize(city, type)
    @city = city
    @type = type
    @workers = []
  end

  # Add a worker to the building
  def employ(unit)
    if @workers.length == @type.max_units
      return CocivMessage.new(_('Too many workers in this building.'))
    end
    unit.abandon_job!
    unit.job = @type.job
    @workers << unit
    unit.working_on = self
    $log.debug "Unit #{unit.military.name} was put to work on #{@type.name}."
  end

  # Calculate the production of the building
  def production
    n = 0
    @workers.each do |worker|
      pr = 3
      pr *= 2 if worker.skill and worker.skill.good == job.good
      n += pr
    end
    return [@type.good, n]
  end

end
