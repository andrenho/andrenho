class Player

  attr_reader :location, :sublocation, :credits, :truck


  def initialize(inital_city)
    @location = inital_city
    @sublocation = :market
    @credits = 2000
    @truck = Pickup.new
  end


  def buy(good, amt)
    purchaseable = (@credits / @location.buy_price(good)).to_i
    amt = purchaseable if amt > purchaseable
    amt = @location.goods[good] if amt > @location.goods[good]
    amt = @truck.add(good, amt)
    @location.goods[good] -= amt
    @credits -= (@location.buy_price(good) * amt)
  end

  
  def sell(good, amt)
    amt = @truck.remove(good, amt)
    @location.goods[good] += amt
    @credits += (@location.sell_price(good) * amt)
  end


end
