class Truck

  attr_reader :cargo

  def initialize
    @cargo = { :iron => 10 } # TODO
  end

  def slots
    return number_of_slots
  end

  def slots_free
    return slots - (@cargo.values.inject(:+) or 0)
  end

  def slots_occupied
    return slots - slots_free
  end

end



class Pickup < Truck

protected

  def number_of_slots
    return 100
  end

end
