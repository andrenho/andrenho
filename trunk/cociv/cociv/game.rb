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
require 'city'
require 'nation'
require 'tile'

require 'pp'

class Game

  attr_reader :map_w, :map_h, :nations, :player, :year

  def Game.load
    return Marshal::load(File.open("#{ENV['HOME']}/.cociv/savefile"))
  end

  def initialize(w, h)
    initialize_map(w, h)
    @nations = [ Nation.new(self, 'Israel', :light_blue) ]
    @player = @nations[0]
    @year = -2000

    @nations.each { |n| n.init_round }
  end

  def [](x, y)
    @tiles[x + (y * @map_w)]
  end

  def advance_round!
    @nations.each { |n| n.init_round }
    @year += 1
  end

  def inspect
    return "G:#{@year}"
  end

  def save!
    begin 
      Dir.mkdir "#{ENV['HOME']}/.cociv"
    rescue Errno::EEXIST; end
    open("#{ENV['HOME']}/.cociv/savefile", 'w') do |f|
      f.print Marshal::dump(self)
    end
  end

protected

  def initialize_map(w, h)
    @map_w, @map_h = w, h
    @tiles = []
    (w*h).times { |i| @tiles[i] = Tile.new(self, i % w, i / w) }
    #3.upto(4) { |x| 3.upto(4) { |y| self[x,y].terrain = Ocean } }
  end

end
