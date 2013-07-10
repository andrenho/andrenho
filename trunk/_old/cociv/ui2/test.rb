$: << '.'
require 'curseslayer'
require 'gamelayer'

include Curses

$scr = GameLayer.new(nil, CursesLayer.new)
$scr.init_color_curses('green', COLOR_GREEN, -1, A_BOLD)
$scr.puts 'Hellooo'
$scr.puts 'a<green>Wor<default>ld!'
$scr.puts '[unit 0]'
$scr.refresh
$scr.getch
$scr.exit
