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
  attr_reader :price
  
  attr_reader :warehouse, :buildings

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
    Good.all.each { |good| prod[good] = Production.new }
    # tiles
    (x-1).upto(x+1) do |xx|
      (y-1).upto(y+1) do |yy|
        next if xx == 0 and yy == 0
        p = @game[xx,yy].production
        if p != []
          prod[p[0]].theorical += p[1]
          prod[p[0]].effective += p[1]
          prod[p[0]].surplus += p[1]
        end
      end
    end
    # building
    @buildings.each do |building|
      if not building.workers.empty?
        good, amount = building.production
        if amount
          prod[good].theorical += amount 
          # calculate how much effectly possible
          effective = amount
          building.type.good.raw_material.each do |raw|
            effective = prod[raw].effective if prod[raw].effective < effective
          end
          building.type.good.raw_material.each do |raw|
            # use up raw good
            prod[raw].surplus -= effective
            prod[raw].lacking = prod[raw].effective - prod[good].effective
          end
          # produce
          prod[good].effective = effective
          prod[good].surplus = effective
          prod[good].lacking = prod[good].theorical - prod[good].effective
        end
      end
    end

    return prod
  end

end
