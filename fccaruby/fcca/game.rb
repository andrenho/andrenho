require 'static'
require 'unit'
require 'nation'
require 'tile'
require 'map'

class Game

  attr_reader :map, :nations
  attr_accessor :focused

  def initialize(w, h)
    @map = Map.new(self, w, h)
    @nations = [Nation.new(self, 'Test')]
    @focused = @nations[0].units[0]
  end

end
