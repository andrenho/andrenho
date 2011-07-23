$: << '..'
$: << '../fcca'
require 'i18n'
require 'fcca/game'
require 'sdl'


class Tiles

  Ground = 0x441010

  attr_reader :world

  def initialize(game)
    SDL.init(SDL::INIT_VIDEO)
    @game = game
  end  

  def create_world
    @world = SDL::Surface.new(SDL::SWSURFACE, @game.map_w*48+100, @game.map_h*48+100, 32, 0, 0, 0, 0)
    @world.fill_rect(0, 0, world.w, world.h, 0xffffff)
    draw_tile(0, 0)
    draw_tile(1, 0)
    draw_tile(2, 0)
    draw_tile(3, 0)
    draw_tile(4, 0)
    draw_tile(5, 0)
    draw_tile(7, 0)
    draw_tile(0, 1)
    draw_tile(1, 1)
    draw_tile(2, 1)
    draw_tile(3, 1)
    draw_tile(4, 1)
    #@game.map_h.times do |y|
    #  @game.map_w.times do |x|
    #    draw_tile x, y
    #  end
    #end
  end

protected

  def draw_tile(tx,ty)
    @world.lock
    px = 30 + (tx * 48)
    py = 70 + (ty * 48)
    (py-8).upto(py+47+8) do |y|
      (px-8).upto(px+47+8) do |x|
        r = out_of_tile(x-px, y-py)
        if rand < r
          case tx
          when 0
            draw_sand_unit(x.to_i, y)
          when 1
            draw_marsh_unit(x.to_i ,y)
          when 2
            draw_tundra_unit(x.to_i, y)
          when 3
            draw_plains_unit(x.to_i, y)
          when 4
            draw_steppe_unit(x.to_i ,y)
          when 5
            draw_prairie_unit(x.to_i, y)
          when 7
            draw_arctic_unit(x.to_i, y)
          end
        end
        if ty == 1
          case tx
          when 0
            draw_desert_tree(x.to_i, y)
          when 2
            draw_pines(x.to_i, y)
          when 3
            draw_mixed_trees(x.to_i, y)
          when 4
            draw_woodland_trees(x.to_i, y)
          end
        end
      end
    end
    @world.unlock
  end

  def out_of_tile(x, y)
    xx = if x < 0
           x.abs 
         elsif x > 48 
           x-48
         else
           0
         end
    yy = if y < 0
           y.abs 
         elsif y > 48
           y-48
         else
           0
         end
    return (((8 - ((xx + yy) / 2.0)) / 8.0) ** 3)
  end

  def draw_prairie_unit(x,y)
    if rand < 0.7
      @world[x,y] = 0x745624
      @world[x,y-1] = 0xb97f22
      if rand < 0.4
        @world[x-1,y-2] = 0xf6cc38
      end
    else
      @world[x,y] = Ground
    end
  end

  def draw_tundra_unit(x,y)
    if rand < 0.6
      @world[x,y] = rand < 0.5 ? 0xdddddd : 0xbbbbbb
    else
      @world[x,y] = 0x229922
      @world[x-(rand*2),y-1] = 0x44bb44
    end
  end

  def draw_sand_unit(x,y)
    if rand < 0.1
      @world[x,y] = 0xf6ac18
    else
      @world[x,y] = 0xffdc48
    end
  end

  def draw_plains_unit(x,y)
    @world[x,y] = 0x118811
    if rand < 0.4
      @world[x-(rand*2),y-1] = 0x33aa33
    end
  end

  def draw_marsh_unit(x,y)
    @world[x,y] = 0x115555
    if rand < 0.1
      g = rand < 0.5 ? 0x117711 : 0x228822
      @world[x,y-1] = g
      @world[x-1,y-1] = g if rand < 0.2
      @world[x-2,y-1] = g
      @world[x-1,y] = g
    end
  end

  def draw_steppe_unit(x,y)
    @world[x,y] = 0x605040
    if rand < 0.6
      @world[x,y] = 0x224400
      @world[x,y-1] = 0x779933
      @world[x-(rand*2),y-2] = 0x99bb33 if rand < 0.7
    end
  end

  def draw_arctic_unit(x,y)
    @world[x,y] = 0xc0c0c0
    @world[x,y] = 0xa0a0d0 if rand < 0.2
  end

  def draw_desert_tree(x,y)
    c = rand < 0.5 ? 0x004000 : 0x006000
    if rand < 0.005
      (0..5).each do |yy|
        @world[x-2,y-yy] = c
        @world[x-3,y-yy] = c
      end
      if rand < 0.5
        @world[x-4,y-2] = c
        @world[x-5,y-2] = c
        @world[x-4,y-3] = c
        @world[x-5,y-3] = c
      else
        @world[x,y-3] = c
        @world[x-1,y-3] = c
        @world[x,y-4] = c
        @world[x-1,y-4] = c
      end
    end
  end

  def draw_pines(x,y)
    def t; rand > 0.5 ? 0x004000 : 0x105010; end
    if rand < 0.03
      (2..3).each { |i| @world[x-i,y] = 0x643030 }
      (2..3).each { |i| @world[x-i,y-1] = 0x643030 }
      (0..5).each { |i| @world[x-i,y-2] = t }
      (0..5).each { |i| @world[x-i,y-3] = t }
      (1..4).each { |i| @world[x-i,y-4] = t }
      (1..4).each { |i| @world[x-i,y-5] = t }
      (2..3).each { |i| @world[x-i,y-6] = t }
      (2..3).each { |i| @world[x-i,y-7] = t }
    end
  end

  def draw_mixed_trees(x,y)
    def t(tc)
      if tc
        rand > 0.5 ? 0x005000 : 0x206020
      else
        rand > 0.5 ? 0x500000 : 0x602020
      end
    end
    tc = rand > 0.5
    if rand < 0.05
      (2..3).each { |i| @world[x-i,y] = 0x643030 }
      (2..3).each { |i| @world[x-i,y-1] = 0x643030 }
      (1..4).each { |i| @world[x-i,y-2] = t(tc) }
      (1..4).each { |i| @world[x-i,y-3] = t(tc) }
      (0..5).each { |i| @world[x-i,y-4] = t(tc) }
      (0..5).each { |i| @world[x-i,y-5] = t(tc) }
      (1..4).each { |i| @world[x-i,y-6] = t(tc) }
      (1..4).each { |i| @world[x-i,y-7] = t(tc) }
    end
  end

  def draw_woodland_trees(x,y)
    def t; rand > 0.5 ? 0x005000 : 0x206020; end
    if rand < 0.03
      (2..3).each { |i| @world[x-i,y] = 0x643030 }
      (2..3).each { |i| @world[x-i,y-1] = 0x643030 }
      (2..3).each { |i| @world[x-i,y-2] = 0x643030 }
      (2..3).each { |i| @world[x-i,y-3] = 0x643030 }
      (1..4).each { |i| @world[x-i,y-4] = t }
      (0..5).each { |i| @world[x-i,y-5] = t }
      (0..5).each { |i| @world[x-i,y-6] = t }
      (1..4).each { |i| @world[x-i,y-7] = t }
    end
  end

end




def test
  game = Game.new(10,10)
  t = Tiles.new(game)
  t.create_world
  t.world.save_bmp('teste.bmp')
end
test



















