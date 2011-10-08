class LandUnit < Unit

  attr_accessor :job, :skill

  def can_build_city?
    true # TODO
  end

  def build_city(name)
    city = City.new(@game, @nation, name, @x, @y)
    nation.cities << city
    city
  end

  def abandon_job!
    if @working_on.is_a? Building
      @working_on.workers.delete(self)
    elsif @working_on.is_a? Tile
      @working_on.worker = nil
    end
    @working_on = nil
  end

  def is_worker?
    @working_on != nil
  end

protected

  def move_ok?(fx, fy)
    tile = @game[fx,fy]
    return false if not generic_move_ok? fx, fy
    return false if [Ocean, Sea].include? tile.terrain

    return true
  end

end
