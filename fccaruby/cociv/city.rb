class City

  attr_reader :game, :nation, :name, :x, :y, :price, :warehouse, :buildings

  Messages = {
    :new_city => _('What is the name of the new city?'),
    :move_to => _('Where do you want to move the %s to?'),
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
    Good.all.each { |g| @price[g] = Price.new }

    # create buildings
    @buildings = []
    InitialBuildings.each do |building_type|
      @buildings << Building.new(building_type)
    end
  end

end
