require 'sdl'
require 'set'


class TileGame

  attr_reader :screen, :sprite, :images
  attr_accessor :on_keypress
  attr_writer :driver

  def initialize(tilesize, screensize, empty_tile)
    @tw, @th = tilesize
    @empty_tile = empty_tile
    sw, sh = screensize
    SDL.init(SDL::INIT_VIDEO)
    @screen = SDL::Screen.open(@tw * sw, @th * sh, 0, 
                               SDL::SWSURFACE | SDL::ANYFORMAT | SDL::RESIZABLE)
    @screen.fill_rect(0, 0, @screen.w, @screen.h, 0xffffff)
    @layers = []
    @images = {}
    @image_cache = {}
    @tileset = {}
    @sprite = {}
  end


  def load_image(symbol, image_path, x=0, y=0, w=0, h=0)
    if image_path.class == String
      if @image_cache[image_path]
        image = @image_cache[image_path]
      else
        image = SDL::Surface.load(image_path)
        @image_cache[image_path] = image
      end
    elsif image_path.class == SDL::Surface
      image = image_path
    else
      raise 'Invalid class.'
    end
    new_image = SDL::Surface.new(SDL::SWSURFACE, 
                                 w==0 ? image.w : w, 
                                 h==0 ? image.h : h, @screen.format)
    SDL::Surface.blit(image, x, y, new_image.w, new_image.h, new_image, 0, 0)
    @images[symbol] = new_image
  end

  
  def done_loading_images!
    @image_cache.each { |k,v| v.destroy }
    @image_cache = {}
  end


  def []=(x,y,z, symbol)
    if not @layers.include? z
      raise 'Layer must be a number.' if not z.is_a? Integer
      @layers << z
      @layers.sort!
    end
    @tileset[[x,y,z]] = symbol
  end


  def draw
    @layers.each do |z|
      0.upto(@screen.w / @tw) do |x|
        0.upto(@screen.h / @th) do |y|
          symbol = @tileset[[x,y,z]]
          if symbol and symbol != @empty_tile and @images[symbol]
            SDL::Surface.blit(@images[symbol], 0, 0, 0, 0, @screen, x * @tw, y * @th)
          end
        end
      end
    end
    @sprite.each { |k,v| redraw_sprite(v) }
  end


  def update
    @screen.flip
  end


  def next_event
    SDL::Event.wait # TODO - blink
  end

  
  def add_sprite(symbol)
    @sprite[symbol] = Sprite.new(self)
  end


  def redraw_sprite(sprite, old_x=nil, old_y=nil, update=false)
    if sprite.tile and @images[sprite.tile]
      if old_x
        SDL::Surface.blit(sprite.backimage, 0, 0, 0, 0, @screen, old_x, old_y)
        sprite.recreate_backimage
      end
      SDL::Surface.blit(@images[sprite.tile], 0, 0, 0, 0, @screen, sprite.x, sprite.y)
    end
    if update
      rect_old = [old_x, old_y, @images[sprite.tile].w, @images[sprite.tile].h]
      rect_new = [sprite.x, sprite.y, 
                @images[sprite.tile].w, @images[sprite.tile].h]
      @screen.update_rects(rect_old, rect_new)
    end
  end



private

  class Sprite

    attr_reader :tile, :x, :y, :backimage

    def initialize(tg)
      @tg = tg
      @tile = nil
      @x, @y = 0, 0
    end

    def tile=(t)
      @tile = t
      @tg.redraw_sprite(self)
      recreate_backimage
    end

    def recreate_backimage
      @backimage.destroy if @backimage and not @backimage.destroyed?
      @backimage = SDL::Surface.new(SDL::SWSURFACE, @tg.images[@tile].w,
                                    @tg.images[@tile].h, @tg.screen.format)
      SDL::Surface.blit(@tg.screen, @x, @y, @backimage.w, @backimage.h,
                        @backimage, 0, 0)
    end

    def move(x, y)
      old_x, old_y = @x, @y
      @x, @y = x, y
      @tg.redraw_sprite(self, old_x, old_y, true)
    end

  end

end


=begin
# test
tg = TileGame.new([8,8], [40,30], ' ')
class << tg
  def key_press(key)
    if key.sym < 255
      case key.sym.chr
      when ' '
        @sprite['X'].move(5, 5)
        update
      when 'q'
        @running = false
      end
    end
  end
end
x, y = 0, 0
255.times do |i| 
  tg.load_image(i.chr, "terminal.png", x, y, 8, 8)
  y += 8
  x, y = (x+8), 0 if y >= 128
end
s = tg.add_sprite('X')
s.tile = '@'
tg.done_loading_images!
tg[1,1,0] = 'A'
tg.draw
tg.update
tg.run
=end
