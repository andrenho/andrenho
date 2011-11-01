require 'city'

class CityPlayer < City

  # BuildingType under construction.
  attr_accessor :under_construction

  # Hammers available for the construction of buildings.
  attr_reader :hammers
  
  # Array of buildings in the city.
  attr_reader :buildings

  def initialize(game, nation, name, x, y)
    super(game, nation, name, x, y)

    # create buildings
    @buildings = []
    InitialBuildings.each do |building_type|
      b = building_type.create_building(self)
      @buildings << b
      @warehouse = b if building_type == Storage
    end  

    # in construction
    @hammers = 0
    @under_construction = Warehouse_1    
  end

  
  # Calculate production of the city. The value is returned as a hash, where
  # the goods are the keys and the values are Production classes.
  def production
    prod = {}
    Good.all.each { |good| prod[good] = Production.new }
    # tiles
    (x-1).upto(x+1) do |xx|
      (y-1).upto(y+1) do |yy|
        next if xx == 0 and yy == 0
        @game[xx,yy].production.each do |p|
          if p != []
            prod[p[0]].theorical += p[1]
            prod[p[0]].effective += p[1]
            prod[p[0]].surplus += p[1]
          end
        end
      end
    end
    # building
    @buildings.each do |building|
      if not building.workers.empty?
        good, amount = building.production
        if amount
          prod[good].theorical += amount 
          # calculate how much effectively possible
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

  # Returns a list of building types (BuildingType) that can be built on
  # this city.
  def buildable
    b = []
    bts_here = @buildings.map { |b| b.type }
    BuildingType.all.each do |bt|
      if not bts_here.include? bt and bts_here.include? bt.prerequisite \
      and residents.length >= bt.min_colony
        b << bt
      end
    end
    return b
  end


  # Returns a list of residents on this city.
  def residents
    u = []
    @buildings.each { |building| u << building.workers }
    (-1..1).each do |xx|
      (-1..1).each do |yy|
        next if xx == 0 and yy == 0
        u << @game[@x+xx,@y+yy].worker
      end
    end
    return u.flatten.compact
  end

  # Initialize a new round
  def init_round!
    @warehouse.throw_away_overload!
    produce!
  end


protected

  # Produce all goods for one round.
  def produce!
    # TODO - spill overload of goods
    $log.debug "Producing goods for the city #{@name}..."
    self.production.each_pair do |good, pr|
      if pr.surplus > 0
        $log.debug "#{pr.surplus} of #{good.name} produced."
        @warehouse.store(good, pr.surplus)
      end
    end
  end

end

