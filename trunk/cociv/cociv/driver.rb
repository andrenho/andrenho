require 'logger'

$: << '.'
$: << 'cociv'
require 'game'

# The driver controls the game. It initializes the game and control it's flow,
# like the change of focus between the unis, and giving each nation the control
# of the game.
class Driver

  attr_reader :game

  # The currently focused unit.
  attr_reader :focused

  # True if game in wizard (debug) mode.
  attr_reader :wizard

  # Initialize the driver.
  def initialize(wizard=false)
    # initialize logger
    $log = Logger.new(STDERR)
    #$log = Logger.new(File.open("/home/andre/.cociv/log", 'a'))
    $log.level = Logger::DEBUG
    $log.datetime_format = '%H:%M:%S'
    $log.debug 'Logger initialized.'

    # initialize game
    @wizard = wizard
    $log.debug 'Wizard mode initialized.' if wizard
    begin
      @game = Game.load
    rescue
      $log.info 'Savefile not found.'
      @game = Game.new(60,21)
    end
    @focused = @game.nations[0].units[0]
  end

  # Runs one round. This is usually called from the UI. It yields in each move,
  # so that the UI can redraw and input before a new round.
  def run_round
    @focused = @game.player.units.select { |u| u.has_moves_left? }[0]

    @game.nations.each do |nation|
      $log.debug "Nation #{nation.name} playing."
      if nation == @game.player # human player
        yield if nation.round_over?
        yield while not nation.round_over?
      else
        nation.autoplay!
      end
      @game.advance_round!
    end
  end

  # A generic method to move a unit. It'll move the selected unit and select
  # the next if the moves are over.
  def move_unit(dir)
    return if not @focused
    @focused.move(dir)
    select_next! if not @focused.has_moves_left?
  end

  # Select the next unit.
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
