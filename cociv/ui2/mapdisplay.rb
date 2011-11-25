require 'display'
require 'cityworkersdisplay'

class MapDisplay < Display
  
  def initialize(driver, scr)
    super(driver, scr)
    @rx, @ry = 0, 0    # relative positions
  end

  
  def redraw
    super
    @scr.clear

    # draw things
    draw_info
    x, y = draw_map
    redraw if $ui.show_messages

    # set focused unit
    if x
      @scr.x = x + @rx + 1
      @scr.y = y + @ry + 1
      @scr.show_cursor = true
    else
      @scr.show_cursor = false
    end
  end

  def manage_city(city)
    display = CityWorkersDisplay.new(@driver, city, @scr)
    loop do
      return if display.is_a? MapDisplay
      display.redraw
      d = display.input
      if d == :exit
        break
      elsif d
        display = d
      end
    end
  end

  def inform_end_of_turn
  end
  
protected #################################

  def key_list
    {
      'C' => _('Manage a city'),
      'w' => _('Select next unit'),
      'B' => _('(Unit) Build new city'),
      'S' => _('Save game and exit'),
      'Q' => _('Abandon game'),
    }
  end


  # Choose a city to manage
  def input_C
    return nil if @game.player.cities.empty?
    options = []
    @game.player.cities.each { |city| options << [city, city.name] }
    choice = $ui.menu(_('Choose a city to manage:'), options)
    manage_city(choice) if choice
  end


  # save and exit
  def input_S
    @game.save!
    @scr.exit
    exit 0
  end

  
  # abandon game
  def input_Q
    if $ui.ask_yn(_('Do you want to abandond the game?'))
      return :abandon
    end
    nil
  end


  # build new city
  def input_B
    if @driver.focused and @driver.focused.can_build_city?
      name = $ui.ask_s(_('What is the name of the new city?'))
      if name
        return [:build_city, name]
      end
    end
    nil
  end

  # wait
  def input_w
    return [:wait]
  end

  # others keys (such as movement)
  def input_other(ch)

    # move
    d = NETHACK_KEYS[ch] if NETHACK_KEYS.has_key? ch
    if DIRECTIONS.has_key? d
      return [:move, d]

    # rest
    elsif ch == ' '
      return [:rest]

    end

    # move screen
    if CONTROL_NETHACK_KEYS.has_key? ch
      fx,fy = DIRECTIONS[CONTROL_NETHACK_KEYS[ch]]
      @rx += fx
      @ry += fy
    end
    nil
  end


private ##################################

  # draw status on the left of the screen
  def draw_info
    def ppair(a,b)
      @scr.puts '<message>' + a + (' ' * (18-a.length-b.to_s.length)) + '<value>' + b.to_s
    end
    # game info
    @scr.x = @scr.y = 0
    @scr.puts '<info>' + @game.player.name
    ppair _('Year'), @game.year.abs.to_s + _(' B.C.')
    @scr.puts
    # selected unit
    if (u = @driver.focused)
      @scr.puts '<info>' + u.military.name
      if u.skills.empty?
        @scr.puts _('No skills')
      else
        u.skills.each { |sk| @scr.puts sk.name }
      end
      ppair _('Moves left'), u.moves_left
    end
  end


  # draw the tiles of the world map
  def draw_map
    x = 18

    # draw box
    @scr.box x, 0, @scr.w-x-1, @scr.h-3
    t = ' ' + _('World Map') + ' '
    @scr.puts ((@scr.w-x-1)/2 - t.length/2) + x, 0, "<title>#{t}"

    # draw tiles
    (1..(@scr.h-4)).each do |y|
      @scr.x = x+1
      @scr.y = y
      (1..(@scr.w-x-2)).each do |x|
        tx = x - @rx - 1
        ty = y - @ry - 1
        if tx >= 0 and ty >= 0 and tx < @game.map_w and ty < @game.map_h
          @scr.print "[tile #{tx} #{ty}]" if @game[tx,ty]
        #elsif tx == -1 or ty == -1 or tx == (@game.map_w) or ty == (@game.map_h)
        #  @scr.print '#'
        else
          @scr.print ' '
        end
      end
    end

    # set focus
    if @driver.focused
      return @driver.focused.x+x, @driver.focused.y
    else
      return nil
    end

  end

end
