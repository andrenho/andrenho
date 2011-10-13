$: << 'ui2'
require 'curseslayer'
require 'gamelayer'
require 'mapdisplay'

include Curses

class UI

  def init(wizard)
    @driver = Driver.new(wizard)
    @game = @driver.game

    @scr = GameLayer.new(@driver, CursesLayer.new)
    init_color(@scr)
  end

  def run!
    display = MapDisplay.new(@driver, @scr)
    while true
      @driver.run_round do
        display.redraw
        n = display.input
        display = n if n
        return if display == :exit
      end
    end
  end

  def close
    @scr.exit
  end

end
