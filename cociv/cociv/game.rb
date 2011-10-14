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
require 'cociv/worldbuild'

require 'pp'

class Game

  attr_reader :map_w, :map_h, :nations, :player, :year

  def Game.load
    return Marshal::load(File.open("#{ENV['HOME']}/.cociv/savefile", 'rb'))
  end

  def initialize(w, h)
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
    open("#{ENV['HOME']}/.cociv/savefile", 'wb') do |f|
      f.print Marshal::dump(self)
    end
  end

end
