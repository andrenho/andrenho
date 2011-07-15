require 'driver/driver'

class DriverCurses < Driver

  @@chars = {
    Ocean => '~',
    Grassland => ' ',
    Colonist => 'X',
  }

  def tile_size; [8,8]; end

  def initialize_tiles
    t = 'tilegame/terminal.png'
    @@chars.each do |k,v|
      x, y = find_char(v)
      @tg.load_image(k, t, x, y, 8, 8)
    end
  end

  def move(unit, key)
    8.times do |i|
      @tg.sprite[unit].move(@tg.sprite[unit].x+i, @tg.sprite[unit].y+i)
    end
  end
    



private
  
  def find_char(c)
    i = c.ord
    x = i / 16
    y = i % 16
    return [x*8, y*8]
  end

end
