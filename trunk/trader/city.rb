class Connection
  attr_reader :city, :distance
  def initalize(city, distance); @city, @distance = city, distance; end
end


class City

  attr_reader :connections

  def initialize
    @connections = []
    @buildings = [:market]
  end
  
  def add_connection(city, distance)
    @connections << Connection.new(city, distance)
    city.connections << Connection.new(self, distance)
  end

end
