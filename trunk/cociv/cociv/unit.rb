class Unit

  attr_reader :x, :y, :old_x, :old_y, :nation, :military, :moves_left
  attr_accessor :extra

  def move(dir)
    $log.debug 'Moving unit...'
    fx, fy = @x + DIRECTIONS[dir][0], @y + DIRECTIONS[dir][1]
    if move_ok? fx, fy, true # true is for logging
      @old_x, @old_y = x, y
      @x, @y = fx, fy
      self.moves_left -= @game[@x,@y].cost_to_enter(self)
      self.moves_left = 0 if moves_left < 1/3.0
      discover_tiles
      $log.debug 'Movement ok!'
      return true
    end
    return false
  end

  def init_round!
    self.moves_left = @military.moves
  end

  def end_round
    self.moves_left = 0
  end

  def has_moves_left?
    DIRECTIONS.each_value do |dir|
      x,y = dir
      if @x+x >= 0 and @y+y >= 0 and @x+x < @game.map_w and @y+y < @game.map_h
        return true if move_ok? @x+x,@y+y
      end
    end
    return false
  end

  def description
    @military.name # TODO - skill/job
  end

  def inspect
    "(#{@military.name})  M:#{@moves_left}"
  end

  def tile
    @game[@x, @y]
  end

  def can_build_city?
    false
  end

  def worker?
    false
  end

  def sight
    1 # TODO
  end

protected

  def initialize(game, nation, military, x, y)
    raise 'Abstract class' if self.class == Unit
    @game = game
    @nation, @military, @x, @y = nation, military, x, y
    @old_x, @old_y = x, y
    if @military.cargo > 0
      extend Cargo
      init_cargo(@military.cargo)
    end
    $log.debug "Unit (#{@military.name}) initialized."
    discover_tiles
  end

  def generic_move_ok?(fx, fy, log)
    return false if @moves_left == 0
    tile = @game[fx,fy]
    if fx < 0 or fy < 0 or fx >= @game.map_w or fy >= @game.map_h
      $log.debug 'Movement rejected because it would go out of the map.' if log
      return false
    end
    if tile.cost_to_enter(self) > @moves_left and @moves_left != self.military.moves
      $log.debug 'Movement rejected because there are not enough moves left.' if log
      return false
    end
    return true
  end

  def discover_tiles
    (-sight..sight).each do |x|
      (-sight..sight).each do |y|
        if @x+x >= 0 and @y+y >= 0 and @x+x < @game.map_w and @y+y < @game.map_h
          @game[@x+x,@y+y].known[@nation] = true
        end
      end
    end
  end

  def moves_left=(n)
    @moves_left = n
    #$log.debug self.inspect
  end
  
end
