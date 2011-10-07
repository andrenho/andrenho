require 'mkmf'
have_library('ncurses', 'initscr') or have_library('curses', 'initscr')
have_header('curses.h')
create_makefile('curses_acs')
