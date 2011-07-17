class Driver

  Dirs = {
    1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
    4 => [-1, 0],               6 => [ 1, 0],
    7 => [-1,-1], 8 => [ 0,-1], 3 => [ 1,-1]
  }

  DirKeys = { 
    1 => [SDL::Key::KP1, 'j'],
    2 => [SDL::Key::KP2, 'k', SDL::Key::DOWN],
    3 => [SDL::Key::KP3, 'l'],
    4 => [SDL::Key::KP4, 'u', SDL::Key::LEFT],
    6 => [SDL::Key::KP6, 'o', SDL::Key::RIGHT],
    7 => [SDL::Key::KP7, '7'],
    8 => [SDL::Key::KP8, '8', SDL::Key::UP],
    9 => [SDL::Key::KP9, '9']
  }


  def initialize
    raise 'This class is abstract.' if self.class == Driver
    @game = Game.new(10, 10)
    @tg = TileGame.new(tile_size, [40,30], :none)
    @tg.driver = self
    initialize_tiles
  end


  def run!
    check_units
    draw_map

    @tg.on_keypress = Proc.new do |key|
      case key.sym
      when 'q'.ord
        @tg.running = false
      when SDL::Key::KP2
      when SDL::Key::DOWN
        if @game.focused
          if @game.focused.move(2)
            move(@game.focused, 2)
          end
        end
      end
      check_units
      draw_map

      # test for movement
      if @game.focused
        DirKeys.each do |dir,k|
          if k.include? key.sym
            move(@game.focused, dir) if @game.focused.move(dir)
          end
        end
      end
    end

    @tg.run
  end


protected

  def check_units
    @game.nations.each do |nation|
      nation.units.each do |unit|
        if not @tg.sprite[unit]
          s = @tg.add_sprite(unit)
          s.tile = unit.military
          s.move(unit.x * 8, unit.y * 8)
        end
      end
    end
  end

  
  def draw_map
    @game.map.w.times do |x|
      @game.map.h.times do |y|
        @tg[x,y,0] = @game.map[x,y].terrain
      end
    end
    @tg.draw
    @tg.update
  end


  def tile_size; abstract; end
  def initialize_tiles; abstract; end
  def move(a,b); abstract; end


private

  def abstract; raise 'Implement this method.'; end

end
