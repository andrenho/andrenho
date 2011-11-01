require 'curses'
require 'acs/curses_acs'
require 'basiclayer'

class CursesLayer < BasicLayer

  include Curses

  def initialize
    super
    begin
      Curses.ESCDELAY = 1
    rescue NotImplementedError
      ENV['ESCDELAY'] = '1'
    end
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

    Curses.define_acs
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
    #if char == '*'
      #Curses.addch_gen Curses::ACS_DEGREE
      #Curses.addch_gen Curses::ACS_BULLET
      #Curses.addch_gen Curses::ACS_UARROW
      #Curses.addch_gen Curses::ACS_LANTERN
      #Curses.addch_gen Curses::ACS_PI
    #  addch '*'
    #else
      addch char
    #end
  end

  def box(x,y,w,h,filled=false,color='default')
    self.color = color
    setpos y, x
    Curses.addch_gen Curses::ACS_ULCORNER
    setpos y, x+w
    Curses.addch_gen Curses::ACS_URCORNER
    setpos y+h, x
    Curses.addch_gen Curses::ACS_LLCORNER
    setpos y+h, x+w
    Curses.addch_gen Curses::ACS_LRCORNER
    ((x+1)..(x+w-1)).each do |xx| 
      setpos y, xx
      Curses.addch_gen Curses::ACS_HLINE
      setpos y+h, xx
      Curses.addch_gen Curses::ACS_HLINE
    end
    ((y+1)..(y+h-1)).each do |yy| 
      setpos yy, x
      Curses.addch_gen Curses::ACS_VLINE
      setpos yy, x+w
      Curses.addch_gen Curses::ACS_VLINE
    end
    if filled
      ((y+1)..(y+h-1)).each do |yy|
        setpos yy, x+1
        addstr ' ' * (w-1)
      end
    end
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

  def reverse=(t)
    if t
      attron A_REVERSE
    else
      attroff A_REVERSE
    end
  end

  def echo=(t)
    if t
      echo
    else
      noecho
    end
  end

  def getch
    Curses.getch
  end

  def gets
    self.show_cursor = 1
    echo
    response = ''
    while true
      r = getch
      if r == 27
        response = nil
        break
        # TODO - backspace
      elsif r == 10 or r == 13
        break
      elsif r == 8 or r == 127
        if response.length > 0
          response.chop!
          setpos stdscr.cury, stdscr.curx-3
          addstr '   '
          setpos stdscr.cury, stdscr.curx-3
        else
          setpos stdscr.cury, stdscr.curx-2
          addstr '  '
          setpos stdscr.cury, stdscr.curx-2
        end
        next
      end
      response += r
    end
      
    noecho
    self.show_cursor = 0
    return response
  end

  def exit
    close_screen
  end

end
