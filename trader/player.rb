class Player

  attr_reader :location, :sublocation

  def initialize(inital_city)
    @location = inital_city
    @sublocation = :market
  end

end
