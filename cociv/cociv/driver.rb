$: << '.'
$: << 'cociv'
require 'game'

class Driver

  attr_reader :game, :focused

  def initialize
    begin
      @game = Game.load
    rescue
      @game = Game.new(20, 20)
    end
    @focused = @game.nations[0].units[0]
  end

  def run_round
    @focused = @game.player.units.select { |u| u.has_moves_left? }[0]

    @game.nations.each do |nation|
      if nation == @game.player # human player
        yield while not nation.round_over?
      else
        nation.autoplay!
      end
      @game.advance_round!
    end
  end

  def move_unit(dir)
    return if not @focused
    @focused.move(dir)
    select_next! if not @focused.has_moves_left?
  end

  def select_next!
    avail_units = @game.player.units.select { |u| u.has_moves_left? or u == @focused }
    if avail_units.length == 0
      return nil
    end
    started = false
    avail_units.cycle 2 do |u|
      if not started
        started = true if u == @focused
      elsif u != @focused
        @focused = u
        return
      end
    end
  end

end
