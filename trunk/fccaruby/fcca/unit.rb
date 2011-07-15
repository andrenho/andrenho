class Unit

  attr_reader :x, :y, :nation, :military
  attr_accessor :extra

  @@dirs = {
    1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
    4 => [-1, 0],               6 => [ 1, 0],
    7 => [-1,-1], 8 => [ 0,-1], 3 => [ 1,-1]
  }

  def move(dir)
    @x, @y = @x + @@dirs[dir][0], @y + @@dirs[dir][1]
  end

protected

  def initialize(game, nation, military, x, y)
    @game = game
    @nation, @military, @x, @y = nation, military, x, y
  end
  
end
