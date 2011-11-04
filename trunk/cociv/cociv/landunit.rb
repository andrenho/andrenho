class LandUnit < Unit

  attr_accessor :job, :skill

  def can_build_city?
    true # TODO
  end

  def build_city(name)
    $log.debug "Building a new city called #{name}."
    city = CityPlayer.new(@game, @nation, name, @x, @y)
    nation.cities << city
    city
  end

  def abandon_job!
    if @working_on.is_a? Building
      @working_on.workers.delete(self)
    elsif @working_on.is_a? Tile
      @working_on.worker = nil
    end
    $log.debug 'Unit abandoned job.' if @working_on
    @working_on = nil
  end

  def worker?
    @working_on != nil
  end

  def end_round
    super
    if self.worker?
      @experience[@job] += 1
      if not @skills.include? @job and @experience[@job] > 100 and rand(50) == 0
        @skills << @job
        if @working_on.is_a? Building
          city = @working_on.city
        elsif @working_on.is_a? Tile
          city = @working_on.belongs_to
        end
        $ui.messages << _('In %s, a peasant has become skilled as a %s.') % ['city', @job.name]
      end
    end
  end

protected

  def move_ok?(fx, fy, log=false)
    tile = @game[fx,fy]
    return false if not generic_move_ok? fx, fy, log
    if [Ocean].include? tile.terrain
      $log.debug 'Movement rejected because land units can\'t move over water.' if log
      return false 
    end

    return true
  end

end
