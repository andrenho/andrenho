require 'curses'
include Curses

$: << '.'
require 'driver'

#
# Colors
#
$color = {
  :info       => [ COLOR_CYAN,  COLOR_BLACK, A_BOLD|A_BLINK ],
  :status_txt => [ COLOR_WHITE, COLOR_BLACK, A_BOLD   ],
  :status_val => [ COLOR_GREEN, COLOR_BLACK, A_BOLD   ],
  :ocean      => [ COLOR_BLUE,  COLOR_BLACK, A_BOLD   ],
  :prairie    => [ COLOR_GREEN, COLOR_BLACK, A_NORMAL ],
  :israel     => [ COLOR_CYAN,  COLOR_BLACK, A_BOLD   ],
}

$chars = {
  # terrains
  Ocean   => [ ':', :ocean ],
  Prairie => [ '.', :prairie ],

  # militaries
  Peasant        => [ 'p' ],
  Colonist       => [ 'c' ],
  Caravan        => [ '@' ],
  Warrior        => [ 'R' ],
  Nomad          => [ 'n' ],
  Chariot        => [ 'C' ],
  Pikeman        => [ 'P' ],
  Mtd_pikeman    => [ 'M' ],
  Armored_warrior=> [ 'A' ],
  Cataphract     => [ 'H' ],
  Catapult       => [ 'T' ],

  Clan_member    => [ 'y' ],
  Clan_armed     => [ 'Y' ],
  Clan_mounted   => [ 'z' ],
  Clan_mtd_armed => [ 'Z' ],

  Elite_soldier  => [ 'U' ],
  Elite_chariot  => [ 'V' ],
  Faraoh_soldier => [ 'W' ],
  Faraoh_chariot => [ 'X' ],

  Penteconter    => [ '1' ],
  Merchantman    => [ '2' ],
  Monoreme       => [ '3' ],
  Bireme         => [ '4' ],
  Trireme        => [ '5' ],
  Galley         => [ '6' ],
  Pirate_ship    => [ '0' ],
}

$nations = {
  :light_blue => :israel
}

#
# Curses
#
def init_curses
  # initialize curses
  init_screen
  curs_set 1
  raw
  cbreak
  noecho
  stdscr.keypad = 1
end

def init_colors
  start_color
  i = 1
  $color.each_pair do |k, v|
    init_pair(i, v[0], v[1])
    v[3] = i
    i += 1
  end
end

def end_curses
  close_screen
end

def s(str, y=-1, x=-1, attr=nil, dir=:left)
  x -= str.length if dir == :right
  attrset color_pair($color[attr][3]) | $color[attr][2] if $color[attr]
  setpos y, x
  addstr str
end


#
# Map 
#
def map_update
  clear
  y = 1
  s $game.player.name, y, 0, :info
  y += 1
  s 'GOLD', y, 0, :status_txt
  s "#{$game.player.gold}", y, 15, :status_val, :right
  y += 1
  s 'YEAR', y, 0, :status_txt
  s "#{$game.year.abs} BC", y, 15, :status_val, :right
  y += 2
  if $driver.focused
    u = $driver.focused
    s u.tile.terrain.name, y, 0, :info
    y += 2
    s u.military.name, y, 0, :info
    y += 1
    s 'MOVES', y, 0, :status_txt
    s u.moves_left.to_s, y, 15, :status_val, :right
  end
  
  map_draw
end

def map_draw
  fx, fy = nil, nil
  (0..($game.map_w-1)).each do |x|
    (0..($game.map_h-1)).each do |y|
      u = $game[x,y].units
      sx, sy = x+16, y+1
      if not u.empty?
        unit = u[0]
        s $chars[unit.military][0], sy, sx, $nations[unit.nation.color]
        fx, fy = sx, sy if u.include? $driver.focused
      else
        c = $chars[$game[x,y].terrain]
        s c[0], sy, sx, c[1] if c
      end
    end
  end
  if fx # focused unit appears on screen
    curs_set 1
    setpos fy, fx
  else
    curs_set 0
  end
  refresh
end

def map_event
  ch = getch
  case ch
  when '1', '2', '3', '4', '6', '7', '8', '9'
    $driver.move_unit(ch.to_i)
  when KEY_UP
    $driver.move_unit(8)
  when KEY_DOWN
    $driver.move_unit(2)
  when KEY_LEFT
    $driver.move_unit(4)
  when KEY_RIGHT
    $driver.move_unit(6)
  when 'w'
    $driver.select_next!
  when ' '
    $game.advance_round!
  when 'q'
    exit
  else
    p keyname(ch)
  end
end


#
# main
#
begin
  $display = :map
  $running = true
  init_curses
  init_colors if has_colors?
  $driver = Driver.new
  $game = $driver.game

  while true
    $driver.run_round do
      case $display
      when :map
        map_update
        map_event
      end
    end
  end

ensure
  end_curses
end
