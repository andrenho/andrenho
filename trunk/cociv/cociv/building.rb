# Each one of the buildings in a city.
class Building

  # BuildingType
  attr_reader :type

  # Array of people working on this building
  attr_reader :workers

  # List of messages
  Messages = {
    :too_many_workers => _('This building doesn\'t hold more than %d units.'),
    :no_workers => _('This building doesn\'t require workers.'),
  }

  # Create a new building
  def initialize(city, type)
    @city = city
    @type = type
    @workers = []
  end

  # Add a worker to the building
  def add_worker(unit)
    return false if @workers.length == @type.max_units
    unit.abandon_job!
    unit.job = @type.job
    @workers << unit
    unit.working_on = self
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
