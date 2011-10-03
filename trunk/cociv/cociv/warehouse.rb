class NotEnoughGoods < Exception; end

class Warehouse

  attr_accessor :max_size

  def initialize(max_size)
    @max_size = max_size
    @goods = {}
    Good.all.each do |good|
      @goods[good] = 0
    end
  end

  def [](good)
    return @goods[good]
  end

  def load(good, amount=nil)
    if not amount
      n = @goods[good]
      @goods[good] = 0
      return n
    else
      raise NotEnoughGoods.new if amount > @goods[good]
      @goods[good] -= amount
      return amount
    end
  end

  def store(good, amount)
    @goods[good] += amount
  end

  def overload
    g = {}
    Good.all.each do |good|
      g[good] = @goods[good] if @goods[good] > @max_size
    end
    return g
  end

end
