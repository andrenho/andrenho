class Tile

  attr_reader :x, :y
  attr_accessor :terrain

  def initialize(game, x, y)
    @game = game
    @x, @y = x, y
    @terrain = Grassland
  end

  def units
    u = []
    @game.nations.each do |nation|
      nation.units.each do |unit|
        u << unit if unit.x == @x and unit.y == @y
      end
      return u if u.length > 0
    end
    return u
  end

end
