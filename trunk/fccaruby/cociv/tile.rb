class Tile

  attr_reader :x, :y
  attr_accessor :terrain, :city

  def initialize(game, x, y)
    @game = game
    @x, @y = x, y
    @terrain = Prairie
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

  def city
    @game.nations.each do |nation|
      nation.cities.each do |city|
        return city if city.x == @x and city.y == @y
      end
    end
    nil
  end

  def cost_to_enter(unit)
    @terrain.cost_to_enter # TODO - rivers, etc
  end

  def can_build_city?
    return true # TODO
  end

end
