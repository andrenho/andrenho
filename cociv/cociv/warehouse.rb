class NotEnoughGoods < Exception; end

class Warehouse < Building

  attr_accessor :max_size

  def initialize(city, building_type)
    super(city, building_type)
    @max_size = building_type.storage
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
      $log.debug "#{n} of #{good.name} taken from the warehouse."
      return n
    else
      raise NotEnoughGoods.new if amount > @goods[good]
      @goods[good] -= amount
      $log.debug "#{amount} of #{good.name} taken from the warehouse."
      return amount
    end
  end

  def store(good, amount)
    @goods[good] += amount
    $log.debug "#{amount} of #{good.name} stored in the warehouse."
  end

  def overload
    g = {}
    Good.all.each do |good|
      g[good] = (@goods[good] - @max_size) if @goods[good] > @max_size
    end
    return g
  end

  # Throw away when it doesn't fit in the warehouse.
  def throw_away_overload!
    away = []
    overload.each_pair do |good,amt|
      @goods[good] = @max_size
      away << [good.name, amt]
    end
    if not away.empty?
      s = away.map{ |k| _('%d t of %s') % [k[1], k[0]] }.join(', ')
      $ui.messages << _('Te warehouse in %s was full, and %s had to be thrown away.') % [city.name, s]
    end
  end

end
