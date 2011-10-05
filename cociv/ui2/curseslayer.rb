require 'curses'
require 'basiclayer'

class CursesLayer < BasicLayer

  include Curses

  def initialize
    super
    ENV['ESCDELAY'] = '0'
    init_screen
    curs_set 1
    raw
    cbreak
    noecho
    stdscr.keypad = 1

    # used for color pairs
    @n_pair = 0
    @color_pairs = [nil]
    
    if has_colors?
      start_color
      use_default_colors
    end
  end

  def w
    cols
  end


  def h
    lines
  end

  def clear
    Curses.clear
  end

  def goto(x,y)
    setpos y, x
  end

  def printc(char)
    addch char
  end

  def refresh
    Curses.refresh
  end

  def init_color_curses(name, fg_color, bg_color, attrs=0)
    n = @color_pairs.index [fg_color, bg_color]
    if not n
      n = @color_pairs.length
      init_pair(n, fg_color, bg_color)
      @color_pairs << [fg_color, bg_color]
    end
    @color[name] = [n, attrs]
  end

  def color=(name)
    name = 'default' if not name
    if name == 'default'
      attrset(color_pair(0))
    else
      raise "Color #{name} does not exists." if not @color.has_key? name
      color = @color[name]
      attrset(color_pair(color[0]) | color[1])
    end
  end

  def show_cursor=(t)
    curs_set t ? 1 : 0
  end

  def getch
    Curses.getch
  end

  def gets
    getstr
  end

  def exit
    close_screen
  end

end
