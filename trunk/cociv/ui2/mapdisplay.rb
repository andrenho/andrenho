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
    x, y = draw_map
    show_last_message

    # set focused unit
    if x
      @scr.x = x - @rx + 1
      @scr.y = y - @rx + 1
      @scr.show_cursor = true
    else
      @scr.show_cursor = false
    end
  end
  
protected #################################

  def key_list
    {
      'C' => _('Manage a city'),
      'b' => _('(Unit) Build new city'),
      'S' => _('Save game and exit'),
      'Q' => _('Abandon game'),
    }
  end


  # Choose a city to manage
  def input_C
    return nil if @game.player.cities.empty?
    options = []
    @game.player.cities.each { |city| options << [city, city.name] }
    choice = menu(_('Choose a city to manage:'), options)
    return CityWorkersDisplay.new(@driver, choice, @scr) if choice
  end


  # save and exit
  def input_S
    @game.save!
    @scr.exit
    exit 0
  end

  
  # abandon game
  def input_Q
    if ask_yn(_('Do you want to abandond the game?'))
      return :exit
    end
    nil
  end


  # build new city
  def input_b
    if @driver.focused and @driver.focused.can_build_city?
      name = ask_s(_('What is the name of the new city?'))
      if name
        city = @driver.focused.build_city(name)
        return CityWorkersDisplay.new(@driver, city, @scr)
      end
    end
    nil
  end


private ##################################


  def draw_map

    x = 18

    # draw box
    @scr.box x, 0, @scr.w-x-1, @scr.h-3
    t = _('World Map')
    @scr.puts ((@scr.w-x-1)/2 - t.length/2) + x, 0, "<title>#{t}"

    # draw tiles
    (1..(@scr.h-1)).each do |y|
      @scr.x = x+1
      @scr.y = y
      (1..(@scr.w-x-2)).each do |x|
        tx = x - @rx - 1
        ty = y - @ry - 1
        @scr.print "[tile #{tx} #{ty}]" if @game[tx,ty]
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
