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

      # beginning of the round: select first unit
      selected = @game.player.units.select { |u| u.has_moves_left? }[0]

      @game.nations.each do |nation|

        if nation == @game.player # human player

          while not nation.round_over?

            redraw = false

            e = @tg.next_event

            # test quitting
            exit if e.is_a? SDL::Event::Quit or (e.is_a? SDL::Event::KeyDown and e.sym == 'q'.ord)

            # game events
            case e
            when SDL::Event::KeyDown
              case e.sym

              # wait
              when 'w'.ord
                selected = select_next(selected)
                redraw = true

              # tests
              when 'b'.ord
                selected.load Food, 10
                redraw = true

              else 
                # test for movement
                if selected
                  DirKeys.each do |dir,k|
                    if k.include? e.sym and selected.move(dir)
                      move(selected, dir)
                      selected = select_next(selected) if not selected.has_moves_left?
                      redraw = true
                    end
                  end
                end
              end
            end

            # post-processing
            if redraw
              check_units
              draw_map

              puts '----------------------------------------------------'
              p @game
              p selected if selected
            end
          end

        else # computer player
          nation.autoplay!

        end

      end
      @game.advance_round!

    end

  end


protected

  # See if a new unit was created and, thus, a new sprite must be added.
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

  
  # Draw all the tiles.
  def draw_map
    @game.map_w.times do |x|
      @game.map_h.times do |y|
        if @game[x,y].city
          @tg[x,y,0] = :city
        else
          @tg[x,y,0] = @game[x,y].terrain
        end
      end
    end
    @tg.draw
    @tg.update
  end


  # Select the next unit.
  def select_next(selected)
    avail_units = @game.player.units.select { |u| u.has_moves_left? or u == selected }
    if avail_units.length == 0
      return nil
    end
    started = false
    avail_units.cycle 2 do |u|
      if not started
        started = true if u == selected
      else
        return u if u != selected
      end
    end
  end


  def tile_size; abstract; end
  def initialize_tiles; abstract; end
  def move(a,b); abstract; end


private

  def abstract; raise 'Implement this method.'; end

end
