require 'static'
require 'unit'
require 'nation'
require 'tile'
require 'map'

class Game

  attr_reader :map, :nations

  def initialize(w, h)
    @map = Map.new(self, w, h)
    @nations = [Nation.new(self, 'Test')]
  end

end
