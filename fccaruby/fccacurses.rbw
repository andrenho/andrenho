$: << '.'
$: << 'tilegame'
$: << 'driver'
$: << 'fcca'
require 'tilegame/tilegame'
require 'fcca/game'
require 'driver/drivercurses'

driver = DriverCurses.new
driver.run!
