$: << 'ui2'
require 'curseslayer'
require 'gamelayer'
require 'mapdisplay'

include Curses

class UI

  def init
    @driver = Driver.new
    @game = @driver.game

    @scr = GameLayer.new(@driver, CursesLayer.new)
    init_color(@scr)
  end

  def run!
    display = MapDisplay.new(@driver, @scr)
    while display != :exit
      @driver.run_round do
        display.redraw
        n = display.input
        display = n if n
      end
    end
  end

  def close
    @scr.exit
  end

end
