class Nation

  attr_reader :units, :selected

  def initialize(game, name)
    @game = game
    @name = name
    @units = []
    create_unit!(Colonist, 2, 2)
    create_unit!(Peasant, 2, 1)
    @selected = @units[0]
  end

  def create_unit!(military, x, y)
    @units << LandUnit.new(@game, self, military, x, y) # TODO
  end

  def autoplay!
    raise 'Not implemented.'
  end

  def init_round
    @units.each { |u| u.init_round }
    @selected = @units.select { |u| u.has_moves_left? }[0]
  end

  def end_round
    @units.each { |u| u.end_round }
  end

  def round_over?
    @units.each { |u| return false if u.has_moves_left? }
    return true
  end

  def select_next!
    avail_units = @units.select { |u| u.has_moves_left? or u == @selected }
    if avail_units.length == 0
      @selected = nil
      return
    end
    started = false
    avail_units.cycle 2 do |u|
      if not started
        started = true if u == @selected
      else
        @selected = u if u != @selected
        break
      end
    end
  end

end
