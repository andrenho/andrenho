class Building

  attr_reader :type

  def initialize(type)
    @type = type
    @workers = []
  end

end
