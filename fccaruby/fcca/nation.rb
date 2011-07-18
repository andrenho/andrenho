class Nation

  attr_reader :units, :selector

  def initialize(game, name)
    @game = game
    @name = name
    @units = []
    @selector = Selector.new(@units)
    create_unit!(Colonist, 2, 2)
    create_unit!(Peasant, 2, 1)
  end

  def selected
    @selector.selected
  end

  def create_unit!(military, x, y)
    @units << LandUnit.new(@game, self, military, x, y) # TODO
  end

  def autoplay!
    raise 'Not implemented.'
  end

  def init_round
    @units.each { |u| u.init_round }
    @selector.init_round
  end

  def end_round
    @units.each { |u| u.end_round }
  end

  def round_over?
    @units.each { |u| return false if u.has_moves_left? }
    return true
  end

end
