require 'truck'
require 'player'
require 'city'

class World

  attr_reader :player, :cities


  def initialize
    @cities = [City.new('New Hope'), City.new('Alabaster')]
    @cities[0].add_connection(@cities[1], 25)
    @player = Player.new(@cities[0])
  end


end
