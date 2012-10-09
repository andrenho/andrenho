class Player

  attr_reader :location, :sublocation, :credits


  def initialize(inital_city)
    @location = inital_city
    @sublocation = :market
    @credits = 2000
  end


end
