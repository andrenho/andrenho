$: << '.'
require 'util/plasma_fractal'

class Game
protected
  
  def create_world(w, h)
    # create fractal
    sz = (2 ** Math.sqrt([w, h].max).ceil) + 1
    fractal = PlasmaFractal.new(:size => sz, :height_seed => 100)
    fractal.generate!
    fractal.normalize! w,h

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
        self[x,y].terrain = Ocean if fractal.data[x][y] < 0
      end
    end

    # hills
    mean = fractal.data.flatten.sort[(0.92*w*h).to_i]
    w.times do |x|
      h.times do |y|
        self[x,y].terrain = Hills if fractal.data[x][y] > mean
      end
    end

    # mountains
    mean = fractal.data.flatten.sort[(0.98*w*h).to_i]
    w.times do |x|
      h.times do |y|
        self[x,y].terrain = Mountain if fractal.data[x][y] > mean
      end
    end

    # rivers
    river_pct = 0.0
    begin
      begin
        create_river(rand(w), rand(h), w, h, fractal.data)
      rescue SystemStackError
      end
      rt = 0.0
      w.times { |x| h.times { |y| rt += 1 if self[x,y].river } }
      rt = rt / (w*h)
    end while rt < 0.05 # rivers occupy 5% of dry land

    # calculate extras
    w.times do |x| 
      h.times do |y| 
        self[x,y].extra.altitude = fractal.data[x][y]
        self[x,y].calculate_extras!
      end
    end

    # calculate terrains
    w.times do |x| 
      h.times do |y| 
        self[x,y].autoset_terrain!
      end
    end
  end


  def create_river(x, y, w, h, data)
    return if self[x,y].terrain == Ocean
    self[x,y].river = true
    return if x == 0 or y == 0 or x == (w-1) or y == (h-1)
    min, min_pos = 999, []
#    [[-1,0],[1,0],[0,-1],[0,1]].each do |xy|
#      xx, yy = xy[0]+x, xy[1]+y
    ((x-1)..(x+1)).each do |xx|
      ((y-1)..(y+1)).each do |yy|
        if min > data[xx][yy] and self[xx,yy].river_tiles.length < 2
          min = data[xx][yy]
          min_pos = [xx,yy]
        end
      end
    end
    if min != 999
      create_river(min_pos[0], min_pos[1], w, h, data)
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
