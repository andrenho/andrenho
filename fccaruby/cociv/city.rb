class City

  class Price
    attr_accessor :buy, :sell
    def initialize; @buy, @sell = 0, 0; end
  end

  attr_reader :game, :nation, :name, :x, :y, :price, :warehouse

  def initialize(game, nation, name, x, y)
    @game, @nation, @name, @x, @y = game, nation, name, x, y
    @game[x,y].city = self
    @warehouse = Warehouse.new(100)
    @price = {}
    Good.all.each { |g| @price[g] = Price.new }
  end

end
