require 'logger'

$: << '.'
$: << 'cociv'
require 'game'

# The driver controls the game. It initializes the game and control it's flow,
# like the change of focus between the unis, and giving each nation the control
# of the game.
class Driver

  @@count = 1

  attr_reader :game

  # The currently focused unit.
  attr_reader :focused

  # True if game in wizard (debug) mode.
  attr_reader :wizard

  attr_reader :number

  # Initialize the driver.
  def initialize(wizard=false)
    @number = @@count
    @number += 1
    # initialize logger
    $log = Logger.new(STDERR)
    #$log = Logger.new(File.open("/home/andre/.cociv/log", 'a'))
    if wizard 
      $log.level = Logger::DEBUG
    else
      $log.level = Logger::INFO
    end
    $log.datetime_format = '%H:%M:%S'
    $log.debug 'Logger initialized.'

    # initialize game
    @game = Game.new(60,21)
  end

  def join(player)
    #    @nations = [ Nation.new(self, 'Israel', :light_blue) ]   
  end

  def run!
  end

  def player_nation_active?
    return @game.nations.include? @game.player
  end

  def run_round!(display)
    @game.start_round!
    @game.nations.each do |nation|

      @focused = nil

      # nation round loop
      loop do
        select_next!

        begin
          # listen
          display.redraw
          command, *parameters = display.input
          redo if command == nil

          # move
          if command == :move
            if @focused
              move_unit(parameters[0]) 
            else
              redo
            end
          end
        end while command == :move and (@focused and @focused.has_moves_left?)

        # execute other commands
        if command == :rest
          if nation.round_over?
            break
          else
            @focused.end_round if @focused
          end
        elsif command == :wait
          next
        elsif command == :abandon
          return false
        elsif command == :build_city
          city = @focused.build_city(parameters[0])
          display.manage_city(city)
          redo
        end

        # round over?
        break if nation.round_over?

      end
    end
    @game.advance_round!
    return true
  end

protected

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
      @focused = nil
      return
    end

    if not @focused
      @focused = avail_units[0]
      return
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
