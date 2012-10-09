class Connection
  attr_reader :city, :distance
  def initalize(city, distance); @city, @distance = city, distance; end
end


class City

  attr_reader :connections, :goods


  def initialize
    @connections = []
    @buildings = [:market]
    @goods = create_stocks
  end
  

  def add_connection(city, distance)
    @connections << Connection.new(city, distance)
    city.connections << Connection.new(self, distance)
    self
  end


private


  def create_stocks
    g = {}
    g[:iron] = 50
    return g
  end


end
