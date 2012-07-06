require 'oo'
require 'city'
require 'building'

city = City.new():init()
farm = Farm:new():init(4, 4)
city:add_building(farm, 1, 1)
