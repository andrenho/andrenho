#
# Colors
#
$color = {
  :info       => [ COLOR_CYAN,    COLOR_BLACK, A_BOLD   ],
  :title      => [ COLOR_WHITE,   COLOR_BLACK, A_NORMAL | A_REVERSE ],
  :text       => [ COLOR_WHITE,   COLOR_BLACK, A_NORMAL ],
  :lacking    => [ COLOR_RED,     COLOR_BLACK, A_BOLD   ],
  :surplus    => [ COLOR_GREEN,   COLOR_BLACK, A_BOLD   ],
  :key        => [ COLOR_MAGENTA, COLOR_BLACK, A_BOLD   ],
  :comm       => [ COLOR_WHITE,   COLOR_BLACK, A_NORMAL ],
  :status_txt => [ COLOR_WHITE,   COLOR_BLACK, A_BOLD   ],
  :status_val => [ COLOR_GREEN,   COLOR_BLACK, A_BOLD   ],
  :discrete   => [ COLOR_BLACK,   COLOR_BLACK, A_BOLD   ],

  :ocean      => [ COLOR_BLUE,    COLOR_BLACK, A_BOLD   ],
  :prairie    => [ COLOR_GREEN,   COLOR_BLACK, A_NORMAL ],
  :israel     => [ COLOR_CYAN,    COLOR_BLACK, A_BOLD   ],
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

  # other
  :city  => [ 'O' ],
}

$nations = {
  :light_blue => :israel
}


