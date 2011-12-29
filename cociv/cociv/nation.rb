class Nation

  # List of units that belong to this nation.
  attr_reader :units

  # Nation name.
  attr_reader :name

  # List of cities of this nation.
  attr_reader :cities

  # Amount of gold that the nation has.
  attr_accessor :gold

  attr_reader :color
  attr_accessor :elimination

  #
  # Create a new nation.
  #
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

    $log.debug "Nation #{@name} initialized."
    create_unit!(Peasant, x, y).skills << Farmer
#    create_unit!(Caravan, x, y)
  end

  # 
  # Create a new unit on the nation.
  #
  def create_unit!(military, x, y)
    u = WorkerUnit.new(@game, self, military, x, y) # TODO
    @units << u
    u
  end


  # 
  # Play a round automaticly (for AI).
  #
  def autoplay!
    raise 'Not implemented.'
  end

  #
  # Do what needs to be done in the beginning of the round.
  #
  def start_round!
    @cities.each { |c| c.init_round! }
    @units.each  { |u| u.init_round! }
  end

  # 
  # Ends a round.
  #
  def end_round!
    @units.each  { |u| u.end_round }
  end

  # 
  # Check if the round is over.
  #
  def round_over?
    @units.each { |u| return false if u.has_moves_left? }
    return true
  end

  # 
  # Kill a unit.
  #
  def kill!(unit)
    assert { @units.include? unit }
    unit.prepare_to_die!
    @units.delete unit
    $log.debug "The unit #{unit.description} has been killed!"
  end

end
