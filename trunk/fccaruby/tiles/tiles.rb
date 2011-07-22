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
            draw_tundra_unit(x.to_i, y)
          when 2
            draw_plains_unit(x.to_i, y)
          when 3
            draw_prairie_unit(x.to_i ,y)
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
    return (((8 - ((xx + yy) / 2.0)) / 8.0) ** 5)
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

end




def test
  game = Game.new(10,10)
  t = Tiles.new(game)
  t.create_world
  t.world.save_bmp('teste.bmp')
end
test



















