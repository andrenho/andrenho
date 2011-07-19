class Unit

  attr_reader :x, :y, :old_x, :old_y, :nation, :military, :moves_left
  attr_accessor :extra

  @@dirs = {
    1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
    4 => [-1, 0],               6 => [ 1, 0],
    7 => [-1,-1], 8 => [ 0,-1], 9 => [ 1,-1]
  }

  def move(dir)
    fx, fy = @x + @@dirs[dir][0], @y + @@dirs[dir][1]
    if move_ok? fx, fy
      @old_x, @old_y = x, y
      @x, @y = fx, fy
      @moves_left -= @game.map[@x,@y].cost_to_enter(self)
      return true
    end
    return false
  end

  def init_round
    @moves_left = @military.moves
  end

  def end_round
    @moves_left = 0
  end

  def has_moves_left?
    (-1..1).each do |x|
      (-1..1).each do |y|
        unless x == 0 and y == 0
          if @x+x >= 0 and @y+y >= 0 and @x+x < @game.map.w and @y+y < @game.map.h
            return true if @game.map[@x+x,@y+y].cost_to_enter(self) <= @moves_left
          end
        end
      end
    end
    return false
  end

  def inspect
    return "(#{@military.name})  M:#{@moves_left}"
  end

protected

  def initialize(game, nation, military, x, y)
    raise 'Abstract class' if self.class == Unit
    @game = game
    @nation, @military, @x, @y = nation, military, x, y
    @old_x, @old_y = x, y
  end

  def generic_move_ok?(fx, fy)
    tile = @game.map[fx,fy]
    return false if fx < 0 or fy < 0 or fx >= @game.map.w or fy >= @game.map.h
    return false if tile.cost_to_enter(self) > @moves_left
    return true
  end
  
end
