require 'display'

class MapDisplay < Display

  
  def initialize(driver, scr)
    super(driver, scr)
    @rx, @ry = 0, 0    # relative positions
  end


  def key_list
    {
      'b' => '(Unit) Build new city',
      'Q' => 'Abandon game',
    }
  end

  
  def redraw
    super
    clear

    # draw box
    @scr.box 0, 0, @scr.w-1, @scr.h-3

    # draw tiles
    (1..(@scr.h-1)).each do |y|
      @scr.x = 1
      @scr.y = y
      (1..(@scr.w-1)).each do |x|
        tx = x - @rx - 1
        ty = y - @ry - 1
        @scr.print "[tile #{tx} #{ty}]" if @game[tx,ty]
      end
    end

    show_last_message

    # set focus
    if @driver.focused
      x, y = @driver.focused.x, @driver.focused.y
      @scr.x = x - @rx + 1
      @scr.y = y - @rx + 1
      @scr.show_cursor = true
    end
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
      @driver.focused.build_city(name) if name
    end
    nil
  end

end
