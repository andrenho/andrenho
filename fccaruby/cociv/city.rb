class City

  attr_reader :game, :nation

  # City name
  attr_reader :name
	  
  # City coordinates
  attr_reader :x, :y
  
  # List of prices of goods in the city
  attr_reader :price, :warehouse, :buildings

  # List of units working on the land
  attr_reader :land_workers

  Messages = {
    :new_city => _('What is the name of the new city?'),
    :move_to => _('Where do you want to move the %s to? (\'-\' to leave city)'),
  }

  class Price
    attr_accessor :buy, :sell
    def initialize; @buy, @sell = 0, 0; end
  end

  def initialize(game, nation, name, x, y)
    @game, @nation, @name, @x, @y = game, nation, name, x, y
    @game[x,y].city = self
    @warehouse = Warehouse.new(100)
    @price = {}
    @land_workers = [nil] * 9
    Good.all.each { |g| @price[g] = Price.new }

    # create buildings
    @buildings = []
    InitialBuildings.each do |building_type|
      @buildings << Building.new(self, building_type)
    end
  end

  def add_land_worker(unit, pos)
    if not @land_workers[pos]
      unit.worker = true
      @land_workers[pos] = unit
    end
  end

  def remove_land_worker(pos)
    @land_workers[pos].worker = false if @land_workers[pos]
    @land_workers[pos] = nil
  end

end
