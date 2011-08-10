$: << '.'
require 'cociv/driver'
require 'ui/main'

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
