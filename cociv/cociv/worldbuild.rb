$: << '.'
require 'util/plasma_fractal'

class Game
protected
  
  def create_world(w, h)
    # create fractal
    sz = (2 ** Math.sqrt([w, h].max).ceil) + 1
    p sz
    fractal = PlasmaFractal.new(:size => sz, :height_seed => 100)
    fractal.generate!
    fractal.normalize!

    # print fractal data
=begin
    fractal.data.each do |row|
      row.each do |v|
        print v.to_i.to_s.rjust(4)
      end
      puts
    end
=end

    # create tiles
    @map_w, @map_h = w, h
    @tiles = []
    (w*h).times { |i| @tiles[i] = Tile.new(self, i % w, i / w) }

    # sea
    w.times do |x|
      h.times do |y|
        self[x,y].terrain = Ocean if fractal.data[x][y] < -2
      end
    end
  end

end


=begin
fractal.generate!
fractal.data.each do |row|
  row.each do |v|
    print v.to_i.to_s.rjust(4)
  end
  puts
end

  def initialize_map(w, h)
    @map_w, @map_h = w, h
    @tiles = []
    (w*h).times { |i| @tiles[i] = Tile.new(self, i % w, i / w) }
    #3.upto(4) { |x| 3.upto(4) { |y| self[x,y].terrain = Ocean } }
  end

=end
