class Nation

  attr_reader :units

  def initialize(game, name)
    @game = game
    @name = name
    @units = []
    create_unit!(Colonist, 2, 2)
  end

  def create_unit!(military, x, y)
    @units << Unit.new(@game, self, military, x, y)
  end

end
