class City

  attr_reader :game, :nation, :name, :x, :y

  def initialize(game, nation, name, x, y)
    @game, @nation, @name, @x, @y = game, nation, name, x, y
    @game.map[x,y].city = self
  end

end
