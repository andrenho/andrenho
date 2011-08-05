require 'ffi-ncurses'
include FFI::NCurses

class Curses

  def init
    # initialize curses
    initscr
    start_color
    curs_set 0
    raw
    cbreak
    noecho
    clear
    keypad(stdscr, 1)
  end

  def exit
    endwin
  end

end


#
# main
#
begin
  curses = Curses.new
  curses.init

  getch
ensure
  curses.exit
end
