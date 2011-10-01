class Nation

  attr_reader :units, :gold, :color, :name, :cities

  def initialize(game, name, color=nil)
    @game = game
    @name = name
    @units = []
    @cities = []
    @gold = 0
    @color = color

    create_unit!(Peasant, 2, 2)
    create_unit!(Caravan, 2, 2)
  end

  def create_unit!(military, x, y)
    @units << LandUnit.new(@game, self, military, x, y) # TODO
  end

  def autoplay!
    raise 'Not implemented.'
  end

  def init_round
    @units.each { |u| u.init_round }
  end

  def end_round
    @units.each { |u| u.end_round }
  end

  def round_over?
    @units.each { |u| return false if u.has_moves_left? }
    return true
  end

end
