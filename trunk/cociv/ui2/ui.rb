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
        game_over! @driver.game.player.elimination if @driver.game.player.elimination
      end
    end
  end

  def close
    @scr.exit if @scr
  end

protected

  def game_over!(motive)
    close
    puts 'Game over.'
    exit 0
  end

end
