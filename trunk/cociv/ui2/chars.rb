$chars = {

  # terrains
  Ocean   => [ ':', 'ocean' ],
  Prairie => [ '.', 'prairie' ],

  # militaries
  Peasant        => 'p',
  Colonist       => 'c',
  Caravan        => '@',
  Warrior        => 'R',
  Nomad          => 'n',
  Chariot        => 'C',
  Pikeman        => 'P',
  Mtd_pikeman    => 'M',
  Armored_warrior=> 'A',
  Cataphract     => 'H',
  Catapult       => 'T',

  Clan_member    => 'y',
  Clan_armed     => 'Y',
  Clan_mounted   => 'z',
  Clan_mtd_armed => 'Z',

  Elite_soldier  => 'U',
  Elite_chariot  => 'V',
  Faraoh_soldier => 'W',
  Faraoh_chariot => 'X',

  Penteconter    => '1',
  Merchantman    => '2',
  Monoreme       => '3',
  Bireme         => '4',
  Trireme        => '5',
  Galley         => '6',
  Pirate_ship    => '0',
}

NETHACK_KEYS = {
  'h' => 4,
  'j' => 2,
  'k' => 8,
  'l' => 6,
  'b' => 1,
  'n' => 3,
  'y' => 7,
  'u' => 9,
}

CONTROL_NETHACK_KEYS = {
  Curses::KEY_BACKSPACE => 4,
  Curses::KEY_CTRL_J => 2,
  Curses::KEY_CTRL_K => 8,
  Curses::KEY_CTRL_L => 6,
}

def init_color(scr)
  scr.init_color_curses('help',    COLOR_WHITE, COLOR_BLUE, A_BOLD)
  scr.init_color_curses('title',   COLOR_WHITE, -1, A_REVERSE)
  scr.init_color_curses('message', COLOR_WHITE, -1, A_BOLD)
  scr.init_color_curses('key',     COLOR_MAGENTA, -1, A_BOLD)
  scr.init_color_curses('surplus', COLOR_GREEN, -1, A_BOLD)
  scr.init_color_curses('lacking', COLOR_RED, -1, A_BOLD)
  scr.init_color_curses('gold',    COLOR_YELLOW, -1, A_BOLD)
  scr.init_color_curses('info',    COLOR_CYAN, -1, A_BOLD)
  scr.init_color_curses('value',   COLOR_GREEN, -1, A_BOLD)

  scr.init_color_curses('israel',  COLOR_CYAN, -1, A_BOLD)

  scr.init_color_curses('prairie', COLOR_GREEN, -1, A_DIM)
end
