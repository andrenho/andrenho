class Driver

  @@dirs = {
    1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
    4 => [-1, 0],               6 => [ 1, 0],
    7 => [-1,-1], 8 => [ 0,-1], 3 => [ 1,-1]
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
        if @game.focused
          if @game.focused.move(2)
            move(@game.focused, 2)
          end
        end
      end
      check_units
      draw_map
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
