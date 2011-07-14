$: << '.'
require 'game'

game = Game.new(10, 10)

class << game
  def print
    @map.h.times do |y|
      @map.w.times do |x|
        @map[x,y].print
      end
      puts
    end
  end
end

class Tile
  def print
    case @terrain
    when Grassland; _ = ' '
    when Ocean;     _ = '~'
    end
    _ = 'X' if units.length > 0
    $stdout.print _
  end
end

game.print

