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
    :production => _('(%d lds of %s)'),
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
    # remove worker from previous job
    @city.buildings.each { |b| b.workers.delete(unit) if b.workers.include? unit }
    # add to the building
    @workers << unit
    unit.worker = true
  end

  # Calculate the production of the building
  def production
    return [Beer, 3] if workers.length > 0 # TODO
    return []
  end

end
