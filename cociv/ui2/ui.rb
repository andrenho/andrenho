$: << 'ui2'
require 'curseslayer'
require 'gamelayer'
require 'mapdisplay'

include Curses

class UI

  def init
    @driver = Driver.new
    @game = @driver.game

    @scr = GameLayer.new(@game, CursesLayer.new)
    init_color(@scr)
  end

  def run!
    display = MapDisplay.new(@driver, @scr)
    while display != :exit
      display.redraw
      n = display.input
      display = n if n
    end
  end

  def close
    @scr.exit
  end

end
