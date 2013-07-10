$: << 'cociv'
require 'util'
require 'static'
require 'production'
require 'cargo'
require 'unit'
require 'landunit'
require 'seaunit'
require 'workerunit'
require 'building'
require 'warehouse'
require 'cityplayer'
require 'cityforeign'
require 'nation'
require 'tile'
require 'cociv/worldbuild'

require 'pp'

#
# The game itself.
#
class Game

  # Map size
  attr_reader :map_w, :map_h
  
  # List of nations playing.
  attr_reader :nations
  
  # The nation controlled by the human.
  attr_reader :player
  
  # The current year (negative values means B.C.)
  attr_reader :year

  # 
  # Load the game from the disk.
  #
  def Game.load
    $log.info "Loading game from #{ENV['HOME']}/.cociv/savefile..."
    return Marshal::load(File.open("#{ENV['HOME']}/.cociv/savefile", 'rb'))
  end


  # 
  # Create a new game, where the map has the size w and h.
  #
  def initialize(w, h)
    $log.debug 'Initializing a new game.'
    create_world(w, h) # this method is in cociv/worldbuild.rb
    @year = -2000
    @player = Nation.new(self, 'Israel', :light_blue)
    @nations = [@player]

    start_round!
  end


  # 
  # Return the tile in the position.
  #
  def [](x, y)
    return nil if x < 0 or y < 0 or x > @map_w-1 or y > @map_h - 1
    return @tiles[x + (y * @map_w)]
  end


  # 
  # Do everything that needs to be done before a new round is started.
  #
  def start_round!
    @nations.each { |n| n.start_round! }
  end


  # 
  # Advance a new round.
  #
  def advance_round!
    cities_famine = @player.cities.select { |c| c.warehouse[Food] + c.production[Food].effective < c.food_consumption }
    if not cities_famine.empty?
      if not $ui.ask_yn _('My king! The winter months are comming and we might not have enough food in %s! Do you want to continue?') % cities_famine.map{ |c| c.name }.join2(', ', ' and ')
        return false
      end
    end

    $log.debug "Year #{@year} closed."
    $log.debug '-------------------------------------'
    
    @year += 1
    $log.debug "New year #{@year} started."
    
    return true
  end

  def inspect
    return "G:#{@year}"
  end

  #
  # Save a game onto the disk.
  #
  def save!
    $log.info "Saving game to #{ENV['HOME']}/.cociv/savefile."
    begin 
      $log.debug "Creating directory #{ENV['HOME']}/.cociv."
      Dir.mkdir "#{ENV['HOME']}/.cociv"
    rescue Errno::EEXIST; end
    open("#{ENV['HOME']}/.cociv/savefile", 'wb') do |f|
      f.print Marshal::dump(self)
    end
    $log.info 'Game saved.'
  end

  # 
  # Check if a nation need to be eliminated from the game.
  #
  def check_for_nation_elimination!
    @nations.each do |nation|
      if nation.units.empty?
        nation.elimination = :no_more_units
        @nations.delete nation
        $log.debug "Nation #{nation.name} was wiped out!"
      end
    end
  end

end
