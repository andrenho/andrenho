class Unit

  attr_reader :x, :y, :old_x, :old_y, :nation, :military, :moves_left
  attr_accessor :extra, :worker

  @@dirs = {
    1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
    4 => [-1, 0],               6 => [ 1, 0],
    7 => [-1,-1], 8 => [ 0,-1], 9 => [ 1,-1]
  }
  def Unit.dirs ; @@dirs ; end

  def move(dir)
    fx, fy = @x + @@dirs[dir][0], @y + @@dirs[dir][1]
    if move_ok? fx, fy
      @old_x, @old_y = x, y
      @x, @y = fx, fy
      @moves_left -= @game[@x,@y].cost_to_enter(self)
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
          if @x+x >= 0 and @y+y >= 0 and @x+x < @game.map_w and @y+y < @game.map_h
            return true if @game[@x+x,@y+y].cost_to_enter(self) <= @moves_left
          end
        end
      end
    end
    return false
  end

  def description
    return @military.name # TODO - skill/job
  end

  def inspect
    s = "(#{@military.name})  M:#{@moves_left}"
    return s
  end

  def tile
    return @game[@x, @y]
  end

  def leave_city!
    if @worker 
      city = tile.city
      if city
        city.buildings.each { |b| b.workers.delete(self) if b.workers.include? self }
      end
      @worker = false
    end
  end

protected

  def initialize(game, nation, military, x, y)
    raise 'Abstract class' if self.class == Unit
    @game = game
    @nation, @military, @x, @y = nation, military, x, y
    @old_x, @old_y = x, y
    @worker = false
    if @military.cargo > 0
      extend Cargo
      init_cargo(@military.cargo)
    end
  end

  def generic_move_ok?(fx, fy)
    tile = @game[fx,fy]
    return false if fx < 0 or fy < 0 or fx >= @game.map_w or fy >= @game.map_h
    return false if tile.cost_to_enter(self) > @moves_left
    return true
  end
  
end
