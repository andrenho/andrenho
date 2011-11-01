$: << 'cociv'
require 'util'
require 'static'
require 'production'
require 'cargo'
require 'unit'
require 'landunit'
require 'seaunit'
require 'building'
require 'warehouse'
require 'cityplayer'
require 'cityforeign'
require 'nation'
require 'tile'
require 'cociv/worldbuild'

require 'pp'

class Game

  attr_reader :map_w, :map_h, :nations, :player, :year

  def Game.load
    $log.info "Loading game from #{ENV['HOME']}/.cociv/savefile..."
    return Marshal::load(File.open("#{ENV['HOME']}/.cociv/savefile", 'rb'))
  end

  def initialize(w, h)
    $log.debug 'Initializing a new game.'
    create_world(w, h) # this method is in cociv/worldbuild.rb
    @nations = [ Nation.new(self, 'Israel', :light_blue) ]
    @player = @nations[0]
    @year = -2000

    @nations.each { |n| n.init_round }
  end

  def [](x, y)
    return nil if x < 0 or y < 0 or x > @map_w-1 or y > @map_h - 1
    return @tiles[x + (y * @map_w)]
  end

  def advance_round!
    $log.debug "Year #{@year} closed."
    $log.debug '-------------------------------------'
    
    @year += 1
    $log.debug "New year #{@year} started."
    
    @nations.each { |n| n.init_round }
  end

  def inspect
    return "G:#{@year}"
  end

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

end
