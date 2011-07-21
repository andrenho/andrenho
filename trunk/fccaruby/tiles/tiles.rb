$: << '..'
$: << '../fcca'
require 'i18n'
require 'fcca/game'
require 'sdl'


class Tiles

  attr_reader :world

  def initialize(game)
    SDL.init(SDL::INIT_VIDEO)
    @game = game
  end  

  def create_world
    @world = SDL::Surface.new(SDL::SWSURFACE, @game.map_w*48+100, @game.map_h*48+100, 32, 0, 0, 0, 0)
    @world.fill_rect(0, 0, world.w, world.h, 0xffffff)
    draw_tile(0, 0)
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
    px.upto(px+47) do |x|
      py.upto(py+47) do |y|
        x += (1.0/12)
          draw_prairie_unit(x.to_i ,y)
      end
    end
    @world.unlock
  end

  def draw_prairie_unit(x,y)
    @world[x,y] = 0x00550E
    @world[x,y] = 0x00C20E if Random.rand > 0.5
  end

end




def test
  game = Game.new(10,10)
  t = Tiles.new(game)
  t.create_world
  t.world.save_bmp('teste.bmp')
end
test



















