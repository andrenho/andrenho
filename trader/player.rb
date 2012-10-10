class Player

  attr_reader :location, :sublocation, :credits, :truck


  def initialize(inital_city)
    @location = inital_city
    @sublocation = :market
    @credits = 2000
    @truck = Pickup.new
  end


end
