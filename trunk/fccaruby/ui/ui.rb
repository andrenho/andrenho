require 'curses'
include Curses

require 'ui/ui_config'
require 'ui/map'
require 'ui/communication'

class UI

  include Map
  include Communication

  #
  # Initialize curses and all variables
  #
  def init
    @display = :map
    @running = true

    # init curses
    init_screen
    curs_set 1
    raw
    cbreak
    noecho
    stdscr.keypad = 1
    
    # init colors
    if has_colors?
      start_color
      i = 1
      $color.each_pair do |k, v|
        init_pair(i, v[0], v[1])
        v[3] = i
        i += 1
      end
    end

    @driver = Driver.new
    @game = @driver.game
  end


  # 
  # main game loop
  #
  def run!
    while true
      @driver.run_round do
        case @display
        when :map
          map_update
          map_event
        end
      end
    end
  end


  # 
  # exit curses mode
  #
  def close
    close_screen
  end

protected

  # 
  # print a given string in the screen
  # 
  def s(str, y=-1, x=-1, attr=nil, dir=:left)
    x -= str.length if dir == :right
    attrset color_pair($color[attr][3]) | $color[attr][2] if $color[attr]
    setpos y, x
    addstr str
  end

end
