class Selector

  attr_reader :selected

  def initialize(units)
    @units = units
  end

  def init_round
    @selected = @units[0]
  end

  def select_next
  end

end
