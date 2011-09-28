class City

  Messages = {
    :new_city => _('What is the name of the new city?'),
    :move_to => _('Where do you want to move the %s to? (\'-\' to leave city)'),
  }

  attr_reader :game, :nation

  # City name
  attr_reader :name
	  
  # City coordinates
  attr_reader :x, :y
  
  # List of prices of goods in the city
  attr_reader :price, :warehouse, :buildings

  class Price
    attr_accessor :buy, :sell
    def initialize; @buy, @sell = 0, 0; end
  end

  # create a new city
  def initialize(game, nation, name, x, y)
    @game, @nation, @name, @x, @y = game, nation, name, x, y
    raise 'City outside bounds.' if x < 1 or y < 1 or x > @game.map_w-2 or y > @game.map_h-2
    @game[x,y].city = self
    (x-1).upto(x+1) do |xx| 
      (y-1).upto(y+1) do |yy| 
        @game[xx,yy].belongs_to = self
      end
    end
    @warehouse = Warehouse.new(100)
    @price = {}
    Good.all.each { |g| @price[g] = Price.new }

    # create buildings
    @buildings = []
    InitialBuildings.each do |building_type|
      @buildings << Building.new(self, building_type)
    end
  end

  # calculate production of the city
  def production
    prod = {}
    (x-1).upto(x+1) do |xx|
      (y-1).upto(y+1) do |yy| 
        prod[@game[xx,yy]] = @game[xx,yy].production
      end
    end
    # TODO - add building production
  end

end
