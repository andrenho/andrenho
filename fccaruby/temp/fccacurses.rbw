$: << '.'
$: << 'tilegame'
$: << 'driver'
$: << 'fcca'
require 'interface/interface'
require 'fcca/game'
require 'driver/drivercurses'

driver = DriverCurses.new
driver.run!
