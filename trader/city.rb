class Connection
  attr_reader :city, :distance
  def initalize(city, distance); @city, @distance = city, distance; end
end


class City

  attr_reader :connections, :goods, :name


  def initialize(name)
    @name = name
    @connections = []
    @buildings = [:market]
    @goods = create_stocks
  end
  

  def add_connection(city, distance)
    @connections << Connection.new(city, distance)
    city.connections << Connection.new(self, distance)
    self
  end


  def buy_price(good)
    return 20
  end


  def sell_price(good)
    return 15
  end


private


  def create_stocks
    g = {}
    g[:iron] = 75
    return g
  end


end
