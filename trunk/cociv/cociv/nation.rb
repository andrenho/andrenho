class Nation

  attr_reader :units, :color, :name, :cities
  attr_accessor :gold

  # Create a new nation.
  def initialize(game, name, color=nil)
    @game = game
    @name = name
    @units = []
    @cities = []
    @gold = 0
    @color = color

    # doesn't know any tile
    (0..(@game.map_w-1)).each do |x|
      (0..(@game.map_h-1)).each do |y|
        @game[x,y].known[self] = false
      end
    end

    # find a tile and create unit
    begin
      x, y = rand(@game.map_w-10) + 5, rand(@game.map_h-10) + 5
    end while [Ocean, Mountain, Hills].include? @game[x,y].terrain

    $log.debug "Nation #{nation.name} initialized."
    create_unit!(Peasant, x, y)
  end

  def create_unit!(military, x, y)
    @units << LandUnit.new(@game, self, military, x, y) # TODO
  end

  def autoplay!
    raise 'Not implemented.'
  end

  def init_round
    @cities.each { |c| c.produce! }
    @units.each { |u| u.init_round }
  end

  def round_over?
    @units.each { |u| return false if u.has_moves_left? }
    return true
  end

end
