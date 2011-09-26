class LandUnit < Unit

  attr_accessor :job

  def build_city(name)
    city = City.new(@game, @nation, name, @x, @y)
    nation.cities << city
    city
  end

protected

  def move_ok?(fx, fy)
    tile = @game[fx,fy]
    return false if not generic_move_ok? fx, fy
    return false if [Ocean, Sea].include? tile.terrain

    return true
  end

end
