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
    $ui = Communication.new(@scr)
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
      game_over! @driver.game.player.elimination if @driver.game.player.elimination
    end
  end

  def close
    @scr.exit if @scr
  end

protected

  def game_over!(motive)
    close
    if motive == :no_more_units
      puts _('Game over: nation has no more units available.')
    end
    exit 0
  end

end
