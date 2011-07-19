class Driver

  Dirs = {
    1 => [-1, 1], 2 => [ 0, 1], 3 => [ 1, 1],
    4 => [-1, 0],               6 => [ 1, 0],
    7 => [-1,-1], 8 => [ 0,-1], 9 => [ 1,-1]
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

    while true
      @game.nations.each do |nation|

        puts '----------------------------------------------------'
        p @game
        p nation.selected if nation.selected

        if nation == @game.player # human player

          while not nation.round_over?
            e = @tg.next_event

            # test quitting
            exit if e.is_a? SDL::Event::Quit or (e.is_a? SDL::Event::KeyDown and e.sym == 'q'.ord)

            # game events
            case e
            when SDL::Event::KeyDown
              case e.sym
              when 'w'.ord
                nation.select_next!
              else 
                # test for movement
                if nation.selected
                  DirKeys.each do |dir,k|
                    if k.include? e.sym and nation.selected.move(dir)
                      move(nation.selected, dir)
                      nation.select_next! if not nation.selected.has_moves_left?
                    end
                  end
                end
              end
            end

            # post-processing
            check_units
            draw_map
          end

        else # computer player
          nation.autoplay!

        end

      end
      @game.advance_round!

    end

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
