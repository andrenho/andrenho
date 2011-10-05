$: << 'ui2'
require 'curseslayer'
require 'gamelayer'

include Curses

class UI

  def init
    @driver = Driver.new
    @game = @driver.game

    @scr = GameLayer.new(@game, CursesLayer.new)
  end

  def run!
    @scr.puts 'Hello'
    @scr.refresh
    @scr.getch
  end

  def close
    @scr.exit
  end

end
