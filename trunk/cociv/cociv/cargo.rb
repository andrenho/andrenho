module Cargo

  Messages = {
    :loaded => _('%d t of %s loaded')
  }

  class Slot
    attr_accessor :good
    attr_reader :amount
    def initialize; @amount=0; end
    def amount=(n)
      raise if n > 100
      @amount = n
    end
  end

  attr_reader :slots

  def init_cargo(n)
    @max_cargo = n
    @slots = []
    n.times do |i|
      @slots[i] = Slot.new
    end
  end

  def load(good, amount=100)
    city = @game[@x,@y].city
    # check for errors
    assert { city }
    if not has_space? good, amount
      raise CocivMessage.new('Not enough space on the #{self.military.name}.')
    end
    if city.nation != @nation
      if (amount * city.price[good].buy) > @nation.gold
        raise CocivMessage.new('Not enough money.')
      end
      # pay up
      @nation.gold -= (amount * city.price[good].buy)
    end
    # unload from warehouse
    city.warehouse.load good, amount
    # load to unit
    @slots.each do |slot| 
      if not slot.good or (slot.good == good and (100-slot.amount) >= amount)
        slot.good = good
        slot.amount += amount
        return true
      end
    end
    raise 'Assertion error: no free slots found.'
  end

  def unload(good, amount=100)
  end

protected

  def has_space?(good, amount)
    @slots.each do |slot|
      return true if not slot.good
      return true if slot.good == good and (100-slot.amount) >= amount
    end
    return false
  end

end

class NotEnoughFunds < Exception; end
class NoSpace < Exception; end
