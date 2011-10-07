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

def init_color(scr)
  scr.init_color_curses('help', COLOR_WHITE, COLOR_BLUE, A_BOLD)
  scr.init_color_curses('message', COLOR_WHITE, -1, A_BOLD)
  scr.init_color_curses('israel', COLOR_CYAN, -1)
  scr.init_color_curses('prairie', COLOR_GREEN, -1, A_DIM)
end
