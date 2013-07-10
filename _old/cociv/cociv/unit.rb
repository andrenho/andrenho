class Unit

  # Unit position
  attr_reader :x, :y
  
  # Previous unit position.
  attr_reader :old_x, :old_y

  # Unit's nation.
  attr_reader :nation
  
  # Unit military class.
  attr_reader :military
  
  # Number of moves the unit has left.
  attr_reader :moves_left

  attr_accessor :extra

  #
  # Move the unit to a given direction. This method calls the method `move_ok?` from the siblings.
  #
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

  # 
  # Do what needs to be done in the beginning of the round.
  # 
  def init_round!
    self.moves_left = @military.moves
  end

  # 
  # Do what needs to be done in the end of the round.
  #
  def end_round
    self.moves_left = 0
  end

  #
  # Return if the unit still can move.
  #
  def has_moves_left?
    return false if self.worker?
    DIRECTIONS.each_value do |dir|
      x,y = dir
      if @x+x >= 0 and @y+y >= 0 and @x+x < @game.map_w and @y+y < @game.map_h
        return true if move_ok? @x+x,@y+y
      end
    end
    return false
  end

  #
  # Return a description of the unit, that'll be used in the GUI.
  #
  def description
    @military.name # TODO - skill/job
  end

  def inspect
    "(#{@military.name})  M:#{@moves_left}"
  end

  #
  # Return the tile the unit is currently standing on.
  #
  def tile
    @game[@x, @y]
  end

  # 
  # Return if a city can be built here by this unit.
  #
  def can_build_city?
    false
  end

  # 
  # Return if the unit is working somewhere.
  #
  def worker?
    false
  end

  # 
  # Return how far the unit can see.
  #
  def sight
    1 # TODO
  end

  def prepare_to_die!
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
