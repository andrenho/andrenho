require 'static'
require 'unit'
require 'landunit'
require 'seaunit'
require 'selector'
require 'nation'
require 'tile'
require 'map'

class Game

  attr_reader :map, :nations, :player, :year
  attr_accessor :focused

  def initialize(w, h)
    @map = Map.new(self, w, h)
    @nations = [Nation.new(self, 'Test')]
    @player = @nations[0]
    @year = -2000

    @nations.each { |n| n.init_round }
  end

  def advance_round!
    @nations.each { |n| n.init_round }
    @year += 1
  end

  def inspect
    return "G:#{@year}"
  end

end
