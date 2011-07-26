require 'sdl'

class Interface

  
  # initialize graphic interface
  def initialize
    @screen = SDL::Screen.open(800, 600, 8, SDL::HWPALETTE)
    init_colors
    @screen.fill_rect(0, 0, @screen.w, @screen.h, @@color[:blue])
    draw_square(10, 10, 100, 100)
    @screen.flip
  end


  # create a new game
  def init_game
    @game = Game.new(10, 10)
    return @game
  end


protected


  # list of colors
  @@clr = {
    :blue => [0, 0, 0xff],
  }
  @@color = {}


  # initialize the color palette
  def init_colors
    c = Array.new(256) { |i| [0, 0, 0] }

    # grayscale
    b = 0
    (0..15).each { |i| c[i] = [b, b, b]; b += 16 }

    # predefined colors
    i = 16
    @@clr.each { |k,v| c[i] = v; @@color[k] = i; i +=1 }

    c[254] = [255, 255, 0] # transparent color
    c[255] = [255, 255, 255] # white
    @screen.set_colors(c, 0)
    @screen.set_color_key(SDL::SRCCOLORKEY | SDL::RLEACCEL, 254)
  end


  # create a etched square
  def draw_square(x, y, w, h, *args)
    corners = [[x,y],[x,y+h],[x+w,y],[x+w,y+h]]
    x.upto(w+x) do |x|
      y.upto(y+h) do |y|
        unless corners.include? [x,y]
          @screen[x,y] = rand < 0.5 ? 12 : 13
        end
      end
    end
  end

end
