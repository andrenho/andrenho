class Map

  attr_reader :w, :h

  def initialize(game, w, h)
    @game = game
    @w, @h = w, h
    @tiles = []
    (w*h).times { |i| @tiles[i] = Tile.new(game, i % @w, i / @w) }
    3.upto(4) { |x| 3.upto(4) { |y| self[x,y].terrain = Ocean } }
  end

  def [](x, y)
    @tiles[x + (y * @w)]
  end

end
