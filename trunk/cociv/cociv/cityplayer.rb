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


  def food_consumption
    return residents.length * 2
  end

  
  # Calculate production of the city. The value is returned as a hash, where
  # the goods are the keys and the values are Production classes.
  def production

    # initialize
    pr = {}
    Good.all.each { |g| pr[g] = Production.new }
    
    # theorical production - tiles
    DIRECTIONS_C.each_value do |tile|
      x = @x+tile[0]
      y = @y+tile[1]
      @game[x,y].production.each do |v|
        good, amt = v
        pr[good].theorical += amt
      end
    end

    # theorical production - buildings
    @buildings.each do |building|
      good, amt = building.production
      if good and amt > 0
        pr[good].theorical += amt
      end
    end

    # effective production - fabricated goods
    Good.all.select{ |g| not g.raw }.each do |good|
      raw_available = [9999]
      good.raw_material.each do |raw|
        raw_available << pr[raw].theorical + @warehouse[raw]
      end
      pr[good].effective = [pr[good].theorical, raw_available.min].min
    end

    # effective production - raw goods
    Good.all.select{ |g| g.raw }.each do |good|
      amt = 0
      Good.all.select{ |g| not g.raw }.each do |f_good|
        amt += f_good.raw_material.select{ |r| r == good }.length * pr[f_good].effective
      end
      pr[good].effective = pr[good].theorical - amt
    end

    pr[Food].effective -= self.food_consumption

    return pr
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
    $log.debug "Producing goods for the city #{@name}..."
    self.production.each_pair do |good, pr|
      # kill unit from hunger
      if good == Food
        if pr.effective + @warehouse[Food] < 0
          victim = residents.sample
          @nation.kill! victim
          $ui.messages << _('A %s has died of hunger in %s.') % [victim.description, @name]
          next
        end
      end

      # store/take from warehouse
      if pr.effective > 0
        @warehouse.store(good, pr.effective)
      elsif pr.effective < 0
        @warehouse.load(good, pr.effective.abs)
      end
    end
  end

end

