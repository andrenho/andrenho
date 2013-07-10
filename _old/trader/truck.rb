class Truck

  def initialize
    @cargo = { :iron => 12 } # TODO
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

  def cargo(good=nil)
    if not good
      return @cargo.clone
    else
      return @cargo[good] if @cargo.include? good
      return 0
    end
  end

  def add(good, amt)
    return 0 if slots_free == 0
    amt = slots_free if amt > slots_free
    @cargo[good] = 0 if not @cargo.include? good
    @cargo[good] += amt
    return amt
  end

  def remove(good, amt)
    return 0 if not @cargo.include? good
    amt = @cargo[good] if amt > @cargo[good]
    @cargo[good] -= amt
    @cargo.delete good if @cargo[good] == 0
    return amt
  end

end



class Pickup < Truck

protected

  def number_of_slots
    return 100
  end

end
