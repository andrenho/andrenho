# A city. This is a abstract class that'll be inherited by CityPlayer and CityForeign.
class City

  attr_reader :game, :nation

  # City name
  attr_reader :name
	  
  # City coordinates
  attr_reader :x, :y
  
  # List of prices of goods in the city
  attr_reader :price

  class Price
    attr_accessor :buy, :sell
    def initialize; @buy, @sell = 0, 0; end
  end

  #
  # Create a new city.
  #
  def initialize(game, nation, name, x, y)
    @game, @nation, @name, @x, @y = game, nation, name, x, y
    raise 'City outside bounds.' if x < 1 or y < 1 or x > @game.map_w-2 or y > @game.map_h-2
    @game[x,y].city = self
    (x-1).upto(x+1) do |xx| 
      (y-1).upto(y+1) do |yy| 
        @game[xx,yy].belongs_to = self
      end
    end

    # prices
    @price = {}
    Good.all.each { |g| @price[g] = Price.new }

    $log.debug "New city #{name} created."
  end

end
