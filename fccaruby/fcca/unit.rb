class Unit

  attr_reader :x, :y, :nation, :military

protected

  def initialize(game, nation, military, x, y)
    @game = game
    @nation, @military, @x, @y = nation, military, x, y
  end
  
end
