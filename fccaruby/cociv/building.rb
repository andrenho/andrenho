class Building

  attr_reader :type, :workers

  Messages = {
    :too_many_workers => _('This building doesn\'t hold more than %d units.'),
    :no_workers => _('This building doesn\'t require workers.'),
    :production => _('(%d lds of %s)'),
  }

  def initialize(type)
    @type = type
    @workers = []
  end

  def add_worker(unit)
    return false if @workers.length == @type.max_units
    @workers << unit
    unit.worker = true
  end

  def production
    return [Beer, 3] if workers.length > 0 # TODO
    return []
  end

end
