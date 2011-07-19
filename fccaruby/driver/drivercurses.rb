require 'driver/driver'

class DriverCurses < Driver

  @@chars = {
    Ocean => '~',
    Prairie => ' ',
    Peasant => 'p',
    Colonist => 'X',
    :city => 'C',
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
    xy = Dirs[key]
    8.times do
      @tg.sprite[unit].move(@tg.sprite[unit].x+xy[0], @tg.sprite[unit].y+xy[1])
      sleep 0.01
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
